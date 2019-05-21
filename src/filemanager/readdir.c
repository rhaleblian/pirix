/* $TOG: readdir.c /main/7 1997/03/31 13:53:34 dbl $ */
/*
 * Motif
 *
 * Copyright (c) 1987-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these librararies and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 * 
 */
/*
 * HISTORY
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <Xm/Xm.h>           /* Motif Toolkit */
#include <Mrm/MrmPublic.h>   /* Mrm */
#include <Xm/Container.h>
#include <Xm/IconG.h>
#include "filemanager.h"

Pixmap fileIcon, dirIcon, fileMask, dirMask, execIcon, execMask,
       noneIcon, noneMask;
Pixmap s_fileIcon, s_dirIcon, s_fileMask, s_dirMask, 
  s_execIcon, s_execMask, s_noneIcon, s_noneMask;

#define NDIRLEVELS 9
int ndirLabel = NDIRLEVELS;
Widget *dirLabel;
char* paths[NDIRLEVELS];
Boolean showHidden = False;

char *currentdir = NULL;

int  validFI = 0; 
int  maxFI = 0;
FileInfoRec *FI = NULL;

int  maxIcons = 0;
int  validIcons = 0;
WidgetList IconGadgets = NULL;

static void doOptionMenu();

static void getIcons(int ind, Pixmap *icon, Pixmap *mask, 
		     Pixmap *sicon, Pixmap *smask);
static int GetNewEntry(int, char*, struct dirent*);
static FileInfoRec *GetInfoFromWidget(Widget);
typedef int (*qsProc)(const void *, const void *);

static int 
qsCompare(void *xx, void *yy)
{
  FileInfoRec *x = (FileInfoRec *) xx;
  FileInfoRec *y = (FileInfoRec *) yy;
  return(strcmp(x -> name, y -> name));
}

static void SortChildren()
{
  int i;

  if (validFI == 0) return;

  qsort(FI, validFI, sizeof(FileInfoRec), (qsProc) qsCompare);

  /* Reorder the list of gadgets */
  for(i = 0; i < validFI; i++) 
    IconGadgets[i] = FI[i].icon;
}


/* Determine real full pathname */
/* This code is UNIX pathname dependent */
char* 
expandPath(char *dirname) 
{
  char buf[1024];
  Boolean parentdir = False;
  Boolean curdir = False;
  Boolean isroot = False;
  char *dir;
  int length;

  if (strcmp(dirname, "/") == 0) isroot = True;
  if (strncmp(dirname, "..", 2) == 0) parentdir = True;
  if (! parentdir && strncmp(dirname, ".", 1) == 0) curdir = True;

  if (! isroot && 
      (curdir || parentdir)) {
    char *n;
    char *partial;

    /* Move currentdir info into a buffer for manipulation */
    if (currentdir == NULL) {
      getcwd(buf, 1024);
    } else {
      strcpy(buf, currentdir);
    }

    dir = buf;
    length = strlen(dir);
    if (length > 2 && dir[length] == '/') dir[length] = 0;

    if (parentdir) {
      n = strrchr(dir, '/');
      if (n != NULL) n = strrchr(dir, '/');
      if (n != NULL) *n = 0; /* truncate */
    }

    /* Look for ../ or ./ at the beginning of the string */
    partial = strchr(dirname, '/');
    if (partial != NULL) {
      strcat(dir, "/");
      strcat(dir, partial);
    } 

    /* If we are empty here,  then we started with ../ */
    if (dir[0] == 0) strcpy(dir, "/");

    return(XtNewString(dir));
  } else {
    return(XtNewString(dirname));
  }
}

void 
readdirCB(Widget widget, char* dirname, XmAnyCallbackStruct *callback_data)
{
  read_directory(NULL, dirname);
}

void 
outlineCB(Widget widget, char* subdirname, 
	  XmContainerOutlineCallbackStruct *callback_data)
{
  if (callback_data -> new_outline_state == True) {
    Widget parent = callback_data -> item;
    char *path;
    int ind;
    FileInfoRec *f = GetInfoFromWidget(parent);

    if (! f -> dirRead) {
      /* Create full pathname.  More complex as we must go find the
	 all the parent's names first */
      Widget grandparent;
      char *names[32]; /* They had better not go more than 32 levels
			  deep in the view ! */
      char buf[256];
      int level;

      f->dirRead = True;
      level = 0;
      /* First go get all the strings */
      XtVaGetValues(parent, XmNentryParent, &grandparent, NULL, NULL);
      names[level++] = f -> name;
      for(; grandparent != (Widget) NULL; level++) {
	FileInfoRec *f = GetInfoFromWidget(grandparent);
	if (f) names[level] = f -> name;
	/* Get the next parent */
	XtVaGetValues(grandparent, XmNentryParent, &grandparent, NULL, NULL);
      }

      /* Now assemble the names into a string */
      strcpy(buf, "");
      for(level = level - 1; level >= 0; level--) {
	strcat(buf, "/"); /* Unix dependent */
	strcat(buf, names[level]);
      }
      path = fullpath(buf);
      if (path != NULL) {
	read_directory(parent, path);
	XtFree(path);
      }
    }
  }
}

void
read_directory(Widget parent, char* dirname)
{
  DIR *thisdir;
  struct dirent *info;
  int i;
  char *tempdir = NULL;

  if (parent == NULL) {
    XtFree(currentdir);
    currentdir = expandPath(dirname);
    thisdir = opendir(currentdir);
  } else {
    tempdir = expandPath(dirname);
    thisdir = opendir(tempdir);
  }

  if (thisdir == NULL) return;

  if (parent == NULL) {
    struct stat buf;

    /* Unmanage all iconGadgets */
    XtUnmanageChildren(IconGadgets,validFI);

    /* Free old namestrings */
    for(i = 0; i < validFI; i++) XtFree(FI[i].name);
    validFI = 0; /* Reset */

    /* Update last read time for current directory */
    stat(currentdir, &buf);
    ltm = buf.st_ctime;    
  }

  while((info = readdir(thisdir))) {
    Boolean is_dot, is_dotdot;

    is_dot = strcmp(info -> d_name, ".") == 0;
    is_dotdot = strcmp(info -> d_name, "..") == 0;

    /* We always process non-dot name files.  But if they start
       with a dot,  we process them only if showHidden is true,
       or they are one of dot or dot-dot */
    if ((is_dot && parent == (Widget) NULL) ||
	showHidden || is_dotdot || (! (info -> d_name[0] == '.'))) {
      validFI = process_single_entry(parent, tempdir, validFI, info);
      validFI++;
    }
  }

  /* Sort children and relayout container */
  SortChildren();
  XmContainerReorder(fileviewer, IconGadgets, validFI);

  /* Manage all valid iconGadgets */
  XtManageChildren(IconGadgets,validFI);

  XmContainerRelayout(fileviewer);

  if (parent == NULL) {
    doOptionMenu();
  }

  /* Restrict geometry of Container */
  fixViewerSize(XtParent(fileviewer), NULL, NULL);

  closedir(thisdir);

  XtFree(tempdir);
}

int 
process_single_entry(Widget parent, char* dir, int ind,
		     struct dirent *info)
{
  Pixmap icon, mask;
  Pixmap s_icon, s_mask;
  char buf[64];
  int status;
  int i;
  float size;
  XmString details[10];
  XmString stemp;
  int num_details;
  mode_t mode;
  struct passwd *user;

  if (parent)
    status = GetNewEntry(ind, dir, info);
  else
    status = GetNewEntry(ind, currentdir, info);
  
  icon = mask = s_icon = s_mask = XmUNSPECIFIED_PIXMAP;

  if (status != -1)
    getIcons(ind, &icon, &mask, &s_icon, &s_mask);
  else
    getIcons(-1, &icon, &mask, &s_icon, &s_mask);
  
  num_details = 0;
  /* Owner */
  if (status != -1)
    user = getpwuid(FI[ind].statbuf.st_uid);
  else
    user = NULL;
  
  if (user != NULL)
    details[num_details++] = XmStringCreateLocalized(user->pw_name);
  else {
    sprintf(buf, "%d", FI[ind].statbuf.st_uid);
    details[num_details++] = XmStringCreateLocalized(buf);
  }
  
  /* Permissions */
  if (status != -1)
    mode = FI[ind].statbuf.st_mode;
  else
    mode = 0;
  sprintf(buf, "%c%c%c,%c%c%c,%c%c%c", 
	  (S_IRUSR & mode) ? 'r' : '-',
	  (S_IWUSR & mode) ? 'w' : '-',
	  (S_IXUSR & mode) ? 'x' : '-',
	  (S_IRGRP & mode) ? 'r' : '-',
	  (S_IWGRP & mode) ? 'w' : '-',
	  (S_IXGRP & mode) ? 'x' : '-',
	  (S_IROTH & mode) ? 'r' : '-',
	  (S_IWOTH & mode) ? 'w' : '-',
	  (S_IXOTH & mode) ? 'x' : '-');
  details[num_details++] = XmStringCreateLocalized(buf); 
  /* Size */
  if (status != -1)
    size = FI[ind].statbuf.st_size;
  else
    size = 0;

  if (size < 1000.0)
    sprintf(buf, "%-d", (int) size);
  else if (size < 1.0e6)
    sprintf(buf, "%-.2fK", size/1.0e3);
  else
    sprintf(buf, "%-.2fM", size/1.0e6);
  details[num_details++] = XmStringCreateLocalized(buf); 

  stemp = XmStringCreateLocalized(info -> d_name);
  XtVaSetValues(IconGadgets[ind], 
		XmNlabelString, stemp, 
		XmNlargeIconPixmap, icon, 
		XmNlargeIconMask, mask,
		XmNsmallIconPixmap, s_icon, 
		XmNsmallIconMask, s_mask,
		XmNdetail, details,
		XmNentryParent, parent,
		XmNoutlineState, XmCOLLAPSED,
		XmNdetailCount, num_details,
		NULL, NULL);
  FI[ind].icon = IconGadgets[ind];

  XmStringFree(stemp);
  
  if (S_ISDIR(FI[ind].statbuf.st_mode) &&
      strcmp(info -> d_name, ".") != 0 &&
      strcmp(info -> d_name, "..") != 0) {
    ind++;
    FI[ind].dirRead = False;
    /* Create "." child */
    GetNewEntry(ind, currentdir, info);
    stemp = XmStringCreateLocalized(".");
    XtVaSetValues(IconGadgets[ind], 
		  XmNlabelString, stemp, 
		  XmNlargeIconPixmap, icon, 
		  XmNlargeIconMask, mask,
		  XmNsmallIconPixmap, s_icon, 
		  XmNsmallIconMask, s_mask,
		  XmNdetail, details,
		  XmNdetailCount, num_details,
		  XmNentryParent, IconGadgets[ind-1],
		  NULL, NULL);
    FI[ind].icon = IconGadgets[ind];
    XmStringFree(stemp);
  }

  for(i = 0; i < num_details; i++)
    XmStringFree(details[i]);

  return(ind);
}     


static int
GetNewEntry(int vFI, char* dir, struct dirent *info)
{
  char buf[256];
  int status;

  if (vFI >= maxFI) {
    int newsize;
    if (maxFI == 0) {
      newsize = 64;
      FI = (FileInfoRec *) XtMalloc(newsize * sizeof(FileInfoRec));
    } else {
      newsize = maxFI * 2;
      FI = (FileInfoRec *) XtRealloc((XtPointer) FI,
				     newsize * sizeof(FileInfoRec));
    }
    maxFI = newsize;
  }

  FI[vFI].name = XtNewString(info -> d_name);
  /* More UNIX specific code */
  strcpy(buf, dir);
  strcat(buf, "/");
  strcat(buf, info -> d_name);
  status = stat(buf, &FI[vFI].statbuf);

  if (vFI >= maxIcons) {
    int newsize;
    if (maxIcons == 0) {
      newsize = 64;
      IconGadgets = (Widget *) XtMalloc(sizeof(Widget) * newsize);
    } else {
      newsize = maxIcons * 2;
      IconGadgets = (Widget *) XtRealloc((XtPointer) IconGadgets, 
					 sizeof(Widget) * newsize);
    }
    maxIcons = newsize;
  }
  
  if (vFI >= validIcons) {
    IconGadgets[vFI] = XmCreateIconGadget(fileviewer, "IG", NULL, 0);
    validIcons++;
  }

  return status;
}

static char*
find_suffix(char *filename)
{
  int i = strlen(filename);

  while(i > 0 && filename[i] != '.') i--;

  if (filename[i] == '.')
    return(&filename[i + 1]);
  else 
    return(filename);
}

static void readIcon(str, icon, mask, fg, bg)
     char *str;
     Pixmap *icon;
     Pixmap *mask;
     Pixel fg, bg;
{
  if (str != NULL) {
    char msk[256];

    if (strcmp(find_suffix(str), "xpm") == 0) {
      int len = strlen(str);
      strncpy(msk, str, len - 4);
      msk[len - 4] = 0;
      strcat(msk, "_m.xpm");
    } else {
      strcpy(msk, str);
      strcat(msk, "_m");
    }

    *icon = XmGetPixmap(XtScreen(toplevel), str, fg, bg);
    *mask = XmGetPixmapByDepth(XtScreen(toplevel), msk,
                               WhitePixelOfScreen(XtScreen(toplevel)),
                               BlackPixelOfScreen(XtScreen(toplevel)), 1);
  }
}

static void 
getIcons(int ind, Pixmap *icon, Pixmap *mask, Pixmap *sicon, Pixmap *smask)
{
  Boolean	isdir;
  Boolean	isexec;
  Boolean	canRead;
  FileInfoRec *info = &FI[ind];
  mode_t	mode;
  XrmQuark	path[10];
  XrmQuark	classes[10];
  XrmDatabase	db = XtScreenDatabase(XtScreenOfObject(toplevel));
  XrmValue	value;
  XrmRepresentation type;
  Pixel		fg, bg;
  char		*str;
  char		*default_type = NULL;

  XtVaGetValues(fileviewer, XmNforeground, &bg, XmNbackground, &fg,
		NULL, NULL);

  /* First try the resource database,  then use the fallbacks below */
  classes[0] = app_class_quark;
  classes[1] = XrmStringToQuark("Types");
  classes[2] = XrmStringToQuark("Any");
  classes[3] = XrmStringToQuark("Icon");
  classes[4] = NULLQUARK;
  path[4] = NULLQUARK;

  path[0] = app_quark;
  path[1] = XrmStringToQuark("types");

  if (ind < 0) {
    default_type = "default_none";
  } else {
    path[2] = XrmStringToQuark(find_suffix(info -> name)); 
    path[3] = XrmStringToQuark("largeIcon");
    XrmQGetResource(db, path, classes, &type, &value);
    str = (char*) value.addr;
    readIcon(str, icon, mask, fg, bg);

    path[3] = XrmStringToQuark("smallIcon");
    XrmQGetResource(db, path, classes, &type, &value);
    str = (char*) value.addr;
    readIcon(str, sicon, smask, fg, bg);

    if (*icon != XmUNSPECIFIED_PIXMAP && 
	*sicon != XmUNSPECIFIED_PIXMAP) return;
  }

  isdir = S_ISDIR(info -> statbuf.st_mode);
  mode = info -> statbuf.st_mode;
  isexec = (mode & S_IXUSR) | (mode & S_IXGRP) | (mode & S_IXOTH);

  /* Defaults */
  if (default_type != NULL) {
    path[2] = XrmStringToQuark(default_type);
  } else if (isdir) {
    path[2] = XrmStringToQuark("default_dir");
  } else if (isexec) {
    path[2] = XrmStringToQuark("default_exec");
  } else {
    path[2] = XrmStringToQuark("default_file");
  }

  if (*icon == XmUNSPECIFIED_PIXMAP) {
    path[3] = XrmStringToQuark("largeIcon");
    XrmQGetResource(db, path, classes, &type, &value);
    str = (char*) value.addr;
    readIcon(str, icon, mask, fg, bg);
  }

  if (*sicon == XmUNSPECIFIED_PIXMAP) {
    path[3] = XrmStringToQuark("smallIcon");
    XrmQGetResource(db, path, classes, &type, &value);
    str = (char*) value.addr;
    readIcon(str, sicon, smask, fg, bg);
  }
}


/* Setup Option Menu */
/* Break off components and stuff into the pushbuttons */
/* This code is entirely UNIX pathname dependent */

static void doOptionMenu()
{
  int i;
  XmString stemp;
  char *c = currentdir;
  Widget memWidget;

  XtUnmanageChildren(dirLabel, ndirLabel);

  for (i = 0; i < ndirLabel; i++) {
    XtFree(paths[i]);
    paths[i] = NULL;
  }

  i = 0;

  if (*c == '/') c++; /* Pointing at dir sep */
  while(i < ndirLabel &&
	*c != 0) {
    char buf[128];
    int n;
    int rind;
    int span;

    /* Copy dir name */
    for(n = 0; n < 128 && c[n] != '/' && c[n] != 0; n++)
      buf[n] = c[n];
    buf[n] = 0;
    c = &c[n];
    
    rind = ndirLabel - i - 1;
    if (rind < 0) break;

    /* Copy full path */
    span = c - currentdir + 1;
    paths[i] = XtMalloc(span + 1);
    strncpy(paths[i], currentdir, span);
    paths[i][span] = 0; /* Null terminate */
    stemp = XmStringCreateLocalized(buf);
    XtVaSetValues(dirLabel[rind], 
		  XmNlabelString, stemp, 
		  NULL, NULL);
    XmStringFree(stemp);
    XtManageChild(dirLabel[rind]);
    XtRemoveAllCallbacks(dirLabel[rind], XmNactivateCallback);
    XtAddCallback(dirLabel[rind], XmNactivateCallback, 
		  (XtCallbackProc) readdirCB, paths[i]);
    i++;
    while (*c == '/' && *c != 0)
      c++; /* Pointing at dir sep */
  }
  if (ndirLabel - i >= 0 && i != 0)
    memWidget = dirLabel[ndirLabel - i];
  else if (i == 0)
    memWidget = XtNameToWidget(mainW, "*lroot");
  else
    memWidget = dirLabel[0];
  XtVaSetValues(dirOM, XmNmenuHistory, memWidget, NULL, NULL);

  /* Reset label */
  stemp = XmStringCreateLocalized(currentdir);
  XtVaSetValues(displayLabel, XmNlabelString, stemp, NULL, NULL);
}

void 
selectCB(Widget w, XtPointer ignore, XtPointer cb)
{
  XmContainerSelectCallbackStruct *cbstruct = 
    (XmContainerSelectCallbackStruct *) cb;
  char *temp;
  Boolean found = False;
  Widget target = cbstruct -> selected_items[0];
  mode_t mode;
  FileInfoRec *f;

  if (cbstruct -> selected_item_count != 1) return;

  f = GetInfoFromWidget(target);

  if (! f) return;

  mode = f -> statbuf.st_mode;
  
  if (S_ISDIR(mode)) {
    /* For directories,  navigate downward */
    if (strcmp(f -> name, "..") == 0 ||
	strcmp(f -> name, ".") == 0)
      temp = expandPath(f -> name);
    else
      temp = fullpath(f -> name);
    readdirCB(w, temp, NULL);
    XtFree(temp);
  } else {
    XrmDatabase db = XtScreenDatabase(XtScreen(toplevel));
    XrmQuark	classes[10];
    XrmQuark	path[10];
    XrmRepresentation type;
    XrmValue	value;
    char	*str;

    /* First try the resource database,  then use the fallbacks below */
    classes[0] = app_class_quark;
    classes[1] = XrmStringToQuark("Types");
    classes[2] = XrmStringToQuark("Any");
    classes[3] = XrmStringToQuark("Action");
    classes[4] = NULLQUARK;

    path[0] = app_quark;
    path[1] = XrmStringToQuark("types");
    path[2] = XrmStringToQuark(find_suffix(f -> name)); 
    path[3] = XrmStringToQuark("action");
    path[4] = NULLQUARK;

    XrmQGetResource(db, path, classes, &type, &value);
    str = (char*) value.addr;
    if (str == NULL) {
      if ((mode & S_IXUSR) | (mode & S_IXGRP) | (mode & S_IXOTH)) {
	path[2] = XrmStringToQuark("default_exec");
      } else {
	path[2] = XrmStringToQuark("default_file");
      }
      XrmQGetResource(db, path, classes, &type, &value);
      str = (char*) value.addr;
    }
    if (str != NULL) {
      char *pathname = fullpath(f -> name);
      char buf[256];
      sprintf(buf, str, pathname);
      strcat(buf, " &");
      system(buf);
      XtFree(pathname);
    }
  }
}

char *
getPathFromIcon(Widget w)
{
  FileInfoRec *f = GetInfoFromWidget(w);

  if (f)
    return(fullpath(f -> name));
  else
    return(NULL);
}

static FileInfoRec *
GetInfoFromWidget(Widget w)
{
  Boolean found = False;
  int ind;

  for(ind = 0; ind < validFI; ind++) {
    if (IconGadgets[ind] == w) {
      found = True;
      break;
    }
  }

  if (found)
    return(&FI[ind]);
  else
    return(NULL);
}
