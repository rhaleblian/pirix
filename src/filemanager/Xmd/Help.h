/* $XConsortium: Help.h /main/5 1995/07/15 20:43:32 drk $ */
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

/* Ensure that the file be included only once. */
#ifndef _XmdHelp_h
#define _XmdHelp_h


/* Include appropriate files. */
#include <Xm/Xm.h> /* widget public header file for XmManager */


/* Allow for C++ compilation. */
#ifdef __cplusplus
extern "C" {
#endif

/* Define the widget class and widget record. */
externalref WidgetClass xmdHelpWidgetClass;

typedef struct _XmdHelpClassRec * XmdHelpWidgetClass;
typedef struct _XmdHelpRec      * XmdHelpWidget;

/* Define an IsSubclass macro. */
#ifndef XmdIsHelp
#define XmdIsHelp(w) XtIsSubclass(w, XmdHelpWidgetClass)
#endif

#define XmdNhelpFile		"helpFile"
#define XmdCHelpFile		"HelpFile"
#define XmdNhelpPath		"helpPath"
#define XmdCHelpPath		"HelpPath"
#define XmdNboldFontName	"boldFontName"
#define XmdNemphasisFontName	"emphasisFontName"
#define XmdNdefaultFontName	"defaultFontName"
#define XmdNheadingFontName	"headingFontName"
#define XmdNtitleFontName	"titleFontName"

/* Specify the API for this widget. */
extern Widget XmdCreateHelp(
			Widget parent,
			char   *name,
			ArgList arglist,
			Cardinal argcount);
extern Widget XmdCreateHelpDialog(
			Widget parent,
			char   *name,
			ArgList arglist,
			Cardinal argcount);
/* XtCallbackProc for use with help callbacks, don't forget to
   include the help widget in the call */
extern void XmdGotoHelpItem(Widget w, int item, Widget help);

/* Allow for C++ compilation. */
#ifdef __cplusplus
} /* Close scope of 'extern "C"' declaration which encloses file. */
#endif


/* Ensure that the file be included only once. */
#endif /* _XmdHelp_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */

