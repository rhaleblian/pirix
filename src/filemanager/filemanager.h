/* $XConsortium: filemanager.h /main/5 1995/07/15 20:45:20 drk $ */
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

#ifndef _filemanager_h
#define _filemanager_h

#include <dirent.h>
#include <sys/stat.h>

typedef struct _FileInfo {
  char *name;
  struct stat statbuf;
  Widget icon;      
  Boolean dirRead;
} FileInfoRec;

extern Widget fileviewer, dirOM, toplevel, mainW, gotoDialog;
extern char *currentdir;
extern Widget *dirLabel, displayLabel;
extern int ndirLabel;
extern char *paths[];
extern FileInfoRec *FI;
extern WidgetList IconGadgets;
extern int validFI;
extern Boolean showHidden;
extern time_t ltm;
extern char *deleteCommand;
extern XrmQuark app_class_quark;
extern XrmQuark app_quark;

extern Widget CreateInterface(char*, Widget);
extern char* fullpath(char*);
extern void readdirCB(Widget, char*, XmAnyCallbackStruct *);
extern void outlineCB(Widget, char*, XmContainerOutlineCallbackStruct *);
extern void manageCB(Widget, Widget, XtPointer);
extern void viewCB(Widget, char*, XtPointer);
extern void gotoCB(Widget widget, XtPointer i1, XtPointer cb);
extern void selectCB(Widget w, XtPointer ignore, XtPointer cb);
extern void quitCB(Widget, char*, XmAnyCallbackStruct*);
extern void newFolder(Widget widget, XtPointer ignore, XtPointer ignore2);
extern void deleteItem(Widget widget, XtPointer ignore, XtPointer ignore2);
extern void targetDestinationCallback(Widget, XtPointer,
				      XmDestinationCallbackStruct*);
extern void targetConvertCallback(Widget, XtPointer,
				  XmConvertCallbackStruct*);
extern char *getPathFromIcon(Widget);
extern void fixViewerSize(Widget w, XtPointer i1, XtPointer i2);
extern void showHiddenCB(Widget widget, XtPointer ignore,
			 XmToggleButtonCallbackStruct *callback_data);
extern void read_directory(Widget, char*);
extern int process_single_entry(Widget, char*, int, struct dirent*);

#endif /* _filemanager_h */
