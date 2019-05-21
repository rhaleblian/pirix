/* $XConsortium: convert.c /main/5 1995/07/15 20:45:16 drk $ */
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

#include <Xm/Xm.h>
#include <Xm/Container.h>
#include <Xm/Transfer.h>
#include "filemanager.h"

void 
targetConvertCallback(Widget wid, XtPointer ignore,
		      XmConvertCallbackStruct *cs)
{
  Atom XA_TARGETS = XInternAtom(XtDisplay(wid), XmSTARGETS, False);
  Atom XA_FILE = XInternAtom(XtDisplay(wid), XmSFILE, False);
  Atom XA_FILENAME = XInternAtom(XtDisplay(wid), XmSFILE_NAME, False);
  Atom XA_MOTIF_EXPORTS = 
    XInternAtom(XtDisplay(wid), XmS_MOTIF_EXPORT_TARGETS, False);
  Atom XA_MOTIF_REQUIRED = 
    XInternAtom(XtDisplay(wid), XmS_MOTIF_CLIPBOARD_TARGETS, False);
  Atom XA_MOTIF_DROP =
    XInternAtom(XtDisplay(wid), XmS_MOTIF_DROP, False);

  if (cs -> selection == XA_MOTIF_DROP &&
      (cs -> target == XA_TARGETS ||
       cs -> target == XA_MOTIF_EXPORTS ||
       cs -> target == XA_MOTIF_REQUIRED)) {
    Atom *targs;
    targs = (Atom *) XtMalloc(sizeof(Atom) * 2);
    targs[0] = XA_FILE;
    targs[1] = XA_FILENAME;
    cs -> value = (XtPointer) targs;
    cs -> length = 2;
    cs -> type = XA_ATOM;
    cs -> format = 32;
    cs -> status = XmCONVERT_MERGE;
  } else if (cs -> target == XA_FILE ||
	     cs -> target == XA_FILENAME) {
    if (cs -> location_data == NULL) {
      WidgetList selected;
      Cardinal count;
      int i;

      /* First get list of selected items. */
      XtVaGetValues(fileviewer, 
		    XmNselectedObjects, &selected,
		    XmNselectedObjectCount, &count,
		    NULL, NULL);

      if (count > 0) {
	char *rval = NULL;
	int curpos = 0;

	for(i = 0; i < count; i++) {
	  char *path;
	  int pathlen;

	  path = getPathFromIcon(selected[i]);
	  pathlen = strlen(path) + 1;
	  rval = XtRealloc(rval, curpos + pathlen);
	  /* This will include the terminating NULL byte.  Important,
	     do not remove this NULL byte,  it acts as a separator */
	  strncpy(rval, path, pathlen);
	  curpos += pathlen;
	}
	cs -> format = 8;
	cs -> length = curpos - 1;
	cs -> type = XA_STRING;
	cs -> status = XmCONVERT_DONE;
      } else {
	cs -> status = XmCONVERT_REFUSE;
      }
    } else {
      char *path;

      path = getPathFromIcon(cs -> location_data);

      cs -> value = path;
      if (path != NULL)
	cs -> length = strlen(path);
      else
	cs -> length = 0;
      cs -> format = 8;
      cs -> type = XA_STRING;
      cs -> status = XmCONVERT_DONE;
    }
  } 
}

void 
targetDestinationCallback(Widget w, XtPointer ignore,
			  XmDestinationCallbackStruct *cs)
{
  /* Later */
}
