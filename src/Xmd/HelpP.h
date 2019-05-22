/* $XConsortium: HelpP.h /main/4 1995/07/15 20:43:36 drk $ */
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
#ifndef _XmdHelpP_h
#define _XmdHelpP_h


/* Include appropriate files. */
#include "Help.h" 
#include <Xm/ManagerP.h>

/* Allow for C++ compilation. */
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  XtPointer		extension;
} XmdHelpClassPart;

/* Define the full class record. */
typedef struct _XmdHelpClassRec
{
	CoreClassPart		core_class;
	CompositeClassPart	composite_class;
	ConstraintClassPart	constraint_class;
	XmManagerClassPart	manager_class;
	XmdHelpClassPart	help_class;
} XmdHelpClassRec;

externalref XmdHelpClassRec xmdHelpClassRec;

/* Define the widget instance part. */
typedef struct
{
	char*			help_path;
	char*			help_file;
	XmRenderTable		rendertable;
	Dimension		spacing;
  	/* Internal instance fields */
 	Cardinal		num_titles;
	Cardinal		allocated_titles;
  	XmStringTable		titles;
	XmStringTable		help_text;
	/* Internal widgets (but in child list) */
	Widget			notebook;
	Widget			text_display;
	Widget			dismiss;
} XmdHelpPart;

/* Define the full instance record. */
typedef struct _XmdHelpRec
{
	CorePart		core;
	CompositePart		composite;
	ConstraintPart		constraint;
	XmManagerPart		manager;
	XmdHelpPart		help;
} XmdHelpRec;

/* Define the subclassing level index to be used with ResolvePartOffset */
#define XmdHelpIndex (XmManagerIndex + 1)

/* Define the constraint part structure. */
typedef struct _XmdHelpConstraintPart
{
  int		dummy;
} XmdHelpConstraintPart, * XmdHelpConstraint;

/* Define the full constraint structure. */
typedef struct _XmdHelpConstraintRec
{
	XmManagerConstraintPart	manager;
	XmdHelpConstraintPart	help;
} XmdHelpConstraintRec, * XmdHelpConstraintPtr;

/* Allow for C++ compilation. */
#ifdef __cplusplus
} /* Close scope of 'extern "C"' declaration which encloses file. */
#endif


/* Ensure that the file be included only once. */
#endif /* _XmdHelpP_h */

