/* $XConsortium: Print.h /main/5 1995/07/15 20:43:54 drk $ */
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
#ifndef _XmdPrint_h
#define _XmdPrint_h


/* Include appropriate files. */
#include <Xm/Xm.h> /* widget public header file for XmManager */

/* Allow for C++ compilation. */
#ifdef __cplusplus
extern "C" {
#endif

/* Define the widget class and widget record. */
externalref WidgetClass xmdPrintWidgetClass;

typedef struct _XmdPrintClassRec * XmdPrintWidgetClass;
typedef struct _XmdPrintRec      * XmdPrintWidget;

/* Define an IsSubclass macro. */
#ifndef XmdIsPrint
#define XmdIsPrint(w) XtIsSubclass(w, XmdPrintWidgetClass)
#endif

#define XmdNprinterList		"printerList"
#define XmdCPrinterList		"PrinterList"
#define XmdNprintAll		"printAll"
#define XmdCPrintAll		"PrintAll"
#define XmdNtwoSided		"twoSided"
#define XmdCTwoSided		"TwoSided"
#define XmdNreverseOrder	"reverseOrder"
#define XmdCReverseOrder	"ReverseOrder"
#define XmdNfromPage		"fromPage"
#define XmdCFromPage		"FromPage"
#define XmdNtoPage		"toPage"
#define XmdCToPage		"ToPage"
#define XmdNnumberOfCopies	"numberOfCopies"
#define XmdCNumberOfCopies	"NumberOfCopies"
#define XmdNprintCallback	"printCallback"

/* Print callback */
typedef struct _XmdPrintCallbackStruct {
  int		reason; 	/* Always XmCR_OK */
  XEvent	*event;		/* Always NULL */
  Boolean	two_sided;	/* True if should print double sided */
  Boolean	reverse_order;	/* True if should reverse order */
  Boolean	to_printer;	/* True if output should go to printer */
  int		first;		/* First page to print.  If first==last==0 */
  int		last;		/* then print all pages */
  int		copies;		/* how many copies to print */
  char*		printer;	/* Name of printer or path of file */
} XmdPrintCallbackStruct;

/* Specify the API for this widget. */
extern Widget XmdCreatePrint(
			Widget parent,
			char   *name,
			ArgList arglist,
			Cardinal argcount);
extern Widget XmdCreatePrintDialog(
			Widget parent,
			char   *name,
			ArgList arglist,
			Cardinal argcount);
extern void XmdPrintDocument(char* pathname,
			     XmdPrintCallbackStruct* cb);

/* Allow for C++ compilation. */
#ifdef __cplusplus
} /* Close scope of 'extern "C"' declaration which encloses file. */
#endif


/* Ensure that the file be included only once. */
#endif /* _XmdPrint_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */

