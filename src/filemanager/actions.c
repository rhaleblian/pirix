/* $XConsortium: actions.c /main/5 1995/07/15 20:45:12 drk $ */
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
#include <errno.h>
#include <pwd.h>
#include <Xm/Xm.h>           /* Motif Toolkit */
#include <Mrm/MrmPublic.h>   /* Mrm */
#include <Xm/Container.h>
#include <Xm/SelectioB.h>
#include <Xm/TextF.h>
#include "filemanager.h"

void 
gotoCB(Widget widget, XtPointer i1, XtPointer cb)
{
  Widget text;
  char *str;

  text = XtNameToWidget(widget, "*Text");

  str = XmTextFieldGetString(text);

  readdirCB(widget, str, NULL);

  XtFree(str);
}

void 
manageCB(Widget widget, Widget w_to_manage, XtPointer callback_data)
{
  if (w_to_manage != (Widget) NULL)
    XtManageChild(w_to_manage);
}

void 
viewCB(Widget widget, char   *type, XtPointer callback_data)
{
  XtEnum size, spatial;

  if (strcmp(type, "large") == 0) {
    size = XmLARGE_ICON;
    spatial = XmSPATIAL;
  } else if (strcmp(type, "small") == 0) {
    size = XmSMALL_ICON;
    spatial = XmSPATIAL;
  } else if (strcmp(type, "detail") == 0) {
    size = XmSMALL_ICON;
    spatial = XmDETAIL;
  }

  XtVaSetValues(fileviewer,
		XmNlayoutType, spatial,
		XmNentryViewType, size,
		0, 0);

  fixViewerSize(XtParent(fileviewer), NULL, NULL);

  XmContainerRelayout(fileviewer);
}

void 
quitCB(Widget widget, char *tag, XmAnyCallbackStruct *callback_data)
{
  exit(0);
}

char* 
fullpath(char *filename)
{
  char buf[1024];
  char *rstr;

  /* This is for UNIX,  write something else for a non-UNIX OS */
  if (strcmp(currentdir, "/") == 0)
    sprintf(buf, "/%s", filename);
  else if (filename[0] == '/')
    sprintf(buf, "%s%s", currentdir, filename);
  else
    sprintf(buf, "%s/%s", currentdir, filename);

  rstr = XtNewString(buf);

  return(rstr);
}


void 
showHiddenCB(Widget widget, XtPointer ignore,
	     XmToggleButtonCallbackStruct *callback_data)
{
  showHidden = callback_data -> set;

  read_directory((Widget) NULL, ".");
}

void 
newFolder(Widget widget, XtPointer ignore, XtPointer ignore2)
{
  char buf[256];
  int i = 0;
  int status;
  Boolean done = False;
  struct stat statbuf;

  while(! done) {
    sprintf(buf, "%s/unnamed%d", currentdir, i);
    status = stat(buf, &statbuf);
    if (status != 0) {
      if (errno == ENOENT)
	done = True;
      else
	return; /* Bad error */
    }
    if (i >= 100) return;
    i++;
  }

  mkdir(buf, 0755);

}
     
void 
deleteItem(Widget widget, XtPointer ignore, XtPointer ignore2)
{
  WidgetList selected;
  Cardinal count;
  int i;

  /* First get list of selected items. */
  XtVaGetValues(fileviewer, 
		XmNselectedObjects, &selected,
		XmNselectedObjectCount, &count,
		NULL, NULL);

  if (count <= 0) return;
 
  for(i = 0; i < count; i++) {
    char buf[256];
    sprintf(buf, deleteCommand, getPathFromIcon(selected[i]));
    system(buf);
  }

  XtVaSetValues(fileviewer, XmNselectedObjectCount, 0, NULL, NULL);
}




