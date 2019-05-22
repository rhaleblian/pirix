/* $XConsortium: PrintP.h /main/4 1995/07/15 20:43:58 drk $ */
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
#ifndef _XmdPrintP_h
#define _XmdPrintP_h

/* Include appropriate files. */
#include "Print.h" 
#include <Xm/FormP.h>

/* Allow for C++ compilation. */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  XtPointer		extension;
} XmdPrintClassPart;

/* Define the full class record. */
typedef struct _XmdPrintClassRec
{
	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ConstraintClassPart	constraint_class;
	XmManagerClassPart	manager_class;
	XmBulletinBoardClassPart  bulletin_board_class;
	XmFormClassPart     	form_class;
	XmdPrintClassPart	print_class;
} XmdPrintClassRec;

externalref XmdPrintClassRec xmdPrintClassRec;

/* Define the widget instance part. */
typedef struct
{
	char*			printer_list;
	Boolean			two_sided;
	Boolean			reverse_order;
	Boolean			print_all;
	int			from_page;
	int			to_page;
	int			number_of_copies;
	XtCallbackList		print_callback;
  	/* Internal instance fields */
 	Cardinal		num_printers;
	char**			printers;
	Boolean*		is_printer;
	Boolean			adding_printer;
	/* Internal widgets which require access */
	Widget			copies_tf;
	Widget			two_sided_toggle;
	Widget			reverse_order_toggle;
	Widget			from_all_rc;
	Widget			from_tf;
	Widget			to_tf;
	Widget			from_toggle;
	Widget			all_toggle;
	Widget			destination_om;
	Widget			destination_pd;
	Widget			new_printer_dialog;
	Cardinal		num_om_items;
	WidgetList		om_items;
} XmdPrintPart;

/* Define the full instance record. */
typedef struct _XmdPrintRec
{
	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmBulletinBoardPart 	bulletin_board;
	XmFormPart     		form;
	XmdPrintPart		print;
} XmdPrintRec;

/* Define the constraint part structure. */
typedef struct _XmdPrintConstraintPart
{
  int		dummy;
} XmdPrintConstraintPart, * XmdPrintConstraint;

/* Define the full constraint structure. */
typedef struct _XmdPrintConstraintRec
{
	XmManagerConstraintPart	manager;
	/* No bulletin board constraint part */
	XmFormConstraintPart    form;
	XmdPrintConstraintPart	print;
} XmdPrintConstraintRec, * XmdPrintConstraintPtr;

/* Allow for C++ compilation. */
#ifdef __cplusplus
} /* Close scope of 'extern "C"' declaration which encloses file. */
#endif


/* Ensure that the file be included only once. */
#endif /* _XmdPrintP_h */

