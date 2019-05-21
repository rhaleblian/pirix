/* $TOG: Help.c /main/7 1997/03/31 13:22:37 dbl $ */
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

/* uncomment for ExmTab button - you'll need to change the Imakefiles
   for many of the demos however. */
/* #define USE_TAB 1 */ 

/* This define controls whether XmCSText or XmLabel is used as */
/* the text_display area. */
#define USE_LABEL 1

#include <stdio.h>
#include <Xm/XmP.h>
#include <Xm/PrimitiveP.h>
#include <Xm/Notebook.h>
#include <Xm/PushB.h>
#include <Xm/PushBG.h>
#include <Xm/SeparatoG.h>
#ifdef USE_LABEL
#include <Xm/Label.h>
#include <Xm/ScrolledW.h>
#else
#include <Xm/CSText.h>
#endif /* USE_LABEL */
#include <Xm/MessageB.h>
#include <Xm/TraitP.h>
#include <Xm/TakesDefT.h>
#ifdef USE_TAB
#include <Exm/TabB.h>
#endif /* USE_TAB */
#include "HelpP.h"

#define DEFAULTHP "./%N%S"
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#define DEFAULT_FONT_NAME "*helvetica-medium-r-*-12-*"
#define BOLD_FONT_NAME "*helvetica-bold-r-*-12-*"
#define EMPHASIS_FONT_NAME "*helvetica-medium-o-*-12-*"
#define HEADING_FONT_NAME "*helvetica-bold-r-*-14-*"
#define TITLE_FONT_NAME "*helvetica-bold-o-*-14-*"

/* Declare static functions. */
static void Initialize(
                        Widget request_w,
                        Widget new_w,
                        ArgList args,
                        Cardinal *num_args );
static void Destroy( 
                        Widget wid) ;
static void Layout(
		   Widget, Widget );
static void Resize (
                        Widget w );
static void SetValuesAlmost( 
                        Widget cw,
                        Widget nw,
                        XtWidgetGeometry *request,
                        XtWidgetGeometry *reply) ;
static XtGeometryResult QueryGeometry (
                        Widget w,
                        XtWidgetGeometry *request,
                        XtWidgetGeometry *reply);
static XtGeometryResult GeometryManager (
                        Widget w,
                        XtWidgetGeometry *request,
                        XtWidgetGeometry *reply);
static void CalcSize (Widget wid,
		      Widget instigator,
		      Dimension *width,
		      Dimension *height);
static void ChangeManaged (
                        Widget w);
static Boolean SetValues (
                        Widget old_w,
                        Widget request_w,
                        Widget new_w,
                        ArgList args,
                        Cardinal *num_args );
static Boolean ParentProcess(Widget wid,
			     XmParentProcessData event) ;
static void ReadHelpFile(Widget w);
static XmIncludeStatus parse_proc(XtPointer      *in_out,
	   XtPointer       text_end,
	   XmTextType      type,
	   XmStringTag     tag,
	   XmParseMapping  entry,
	   int		   pattern_length,
	   XmString       *str_include,
	   XtPointer       call_data);
static XmIncludeStatus esc_parse_proc(XtPointer      *in_out,
	   XtPointer       text_end,
	   XmTextType      type,
	   XmStringTag     tag,
	   XmParseMapping  entry,
	   int		   pattern_length,
	   XmString       *str_include,
	   XtPointer       call_data);
static XmString parse_text(String value);
static void page_change(Widget, XtPointer, 
			XmNotebookCallbackStruct *);
static void unmanage_cb(Widget, Widget, XtPointer);

/* No translations and no actions. */

/* Define the resources for the XmdHelp widget. */ 
static XtResource resources[] =
{
  { XmdNhelpFile, XmdCHelpFile, XmRString, sizeof(String),
      XtOffsetOf( XmdHelpRec, help.help_file),
      XmRImmediate, (XtPointer) NULL },
  { XmdNhelpPath, XmdCHelpPath,	XmRString, sizeof(String),
      XtOffsetOf( XmdHelpRec, help.help_path),
      XmRImmediate, (XtPointer) NULL },
  { XmNspacing, XmCSpacing, XmRDimension, sizeof(Dimension),
      XtOffsetOf( XmdHelpRec, help.spacing),
      XmRImmediate, (XtPointer) 10 },
  { XmNrenderTable, XmCRenderTable, XmRRenderTable, sizeof(XmRenderTable),
      XtOffsetOf( XmdHelpRec, help.rendertable),
      XmRImmediate, (XtPointer) NULL },
};

/* Define the widget class record.  See Chapter 4 of the 
   "OSF/Motif Widget Writer's Guide" for details. */ 
externaldef(Xmdhelpclassrec) XmdHelpClassRec xmdHelpClassRec = 
{ 
  { /* Here is the Core class record. */ 
    /* superclass */                 (WidgetClass) &xmManagerClassRec,
    /* class_name */                 "XmdHelp",
    /* widget_size */                sizeof(XmdHelpRec),
    /* class_initialize */           NULL,
    /* class_part_initialize */      NULL,
    /* class_inited */               FALSE,
    /* initialize */                 Initialize,
    /* initialize_hook */            NULL,
    /* realize */                    XtInheritRealize,
    /* actions */                    NULL,
    /* num_actions */                0,
    /* resources */                  resources,
    /* num_resources */              XtNumber(resources),
    /* xrm_class */                  NULLQUARK,
    /* compress_motion */            TRUE,
    /* compress_exposure */          XtExposeCompressMaximal,
    /* compress_enterleave */        TRUE,
    /* visible_interest */           FALSE,
    /* destroy */                    Destroy,
    /* resize */                     Resize,
    /* expose */                     XtInheritExpose,
    /* set_values */                 SetValues,
    /* set_values_hook */            NULL,
    /* set_values_almost */          XtInheritSetValuesAlmost,
    /* get_values_hook */            NULL,
    /* accept_focus */               NULL,
    /* version */                    XtVersion,
    /* callback_private */           NULL,
    /* tm_table */                   XtInheritTranslations,
    /* query_geometry */             QueryGeometry,
    /* display_accelerator */        NULL,
    /* extension */                  NULL,
  },    
  { /* Here is the Composite class record. */ 
    /* geometry_manager */           GeometryManager,
    /* change_managed */             ChangeManaged,
    /* insert_child */               XtInheritInsertChild,
    /* delete_child */               XtInheritDeleteChild,
    /* extension */                  NULL,
  },    
  { /* Here is the Constaint class record. */ 
    /* constraint_resources */       NULL,
    /* constraint_num_resources */   0,
    /* constraint_size */            sizeof(XmdHelpConstraintRec), 
    /* constraint_initialize */      NULL,
    /* constraint_destroy */         NULL,
    /* constraint_set_values */      NULL,
    /* extension */                  NULL,
  },    
  { /* Here is the XmManager class record. */ 
    /* translations */               XtInheritTranslations,
    /* syn_resources */              NULL,
    /* num_syn_resources */          0,
    /* syn_constraint_resources */   NULL,
    /* num_syn_constraint_resources */ 0,
    /* parent_process */             ParentProcess,
    /* extension */                  NULL,
  },    
  { /* Here is the XmdHelp class record. */ 
      (XtPointer) NULL, 		    /* extension */ 
  }    
};    

/* Establish the widget class name as an externally accessible symbol.
   Use the "externaldef" macro rather than the "extern" keyword. */
externaldef(Xmdhelpwidgetclass) WidgetClass xmdHelpWidgetClass =
    (WidgetClass) &xmdHelpClassRec;

/**************************************************************************
 *
 *  Initialize:
 *      Called when this widget is first instantiated.
 *
 ***************************************************************************/
static void 
Initialize(Widget request_w,
	   Widget new_w,
	   ArgList p_args,
	   Cardinal *num_args)
{
  XmdHelpWidget rw = (XmdHelpWidget) request_w;
  XmdHelpWidget nw = (XmdHelpWidget) new_w;
  Arg args[20];
  int n, i;
  XmRendition rend[10];
  XmRenderTable csRT;
  XmTab tabs[5];
  XmTabList csTabs;
  XmTakesDefaultTrait trait_default;
#if USE_LABEL
  Widget display_parent;
#endif /* USE_LABEL */

  /* Initialize internal fields */
  nw -> help.num_titles = 0;
  nw -> help.allocated_titles = 0;
  nw -> help.titles = NULL;
  nw -> help.help_text = NULL;

  /* Create a default RenderTable if none specified */
  if (nw -> help.rendertable == (XmRenderTable) NULL) {
    for(n = 0; n < 5; n++)
      tabs[n] = XmTabCreate(1.0, XmINCHES, XmRELATIVE, 
			    XmALIGNMENT_BEGINNING, NULL);
    csTabs = XmTabListInsertTabs(NULL, tabs, 5, 0);
    for(n = 0; n < 5; n++) XmTabFree(tabs[n]);

    n = 0; i = 0;
    XtSetArg(args[n], XmNfontName, DEFAULT_FONT_NAME); n++;
    XtSetArg(args[n], XmNfontType, XmFONT_IS_FONT); n++;
    XtSetArg(args[n], XmNtabList, csTabs); n++;
    rend[i] = XmRenditionCreate(new_w, XmFONTLIST_DEFAULT_TAG, args, n); i++;
    n = 0;
    XtSetArg(args[n], XmNfontName, BOLD_FONT_NAME); n++;
    XtSetArg(args[n], XmNfontType, XmFONT_IS_FONT); n++;
    rend[i] = XmRenditionCreate(new_w, "bold", args, n); i++;
    n = 0;
    XtSetArg(args[n], XmNfontName, HEADING_FONT_NAME); n++;
    XtSetArg(args[n], XmNfontType, XmFONT_IS_FONT); n++;
    rend[i] = XmRenditionCreate(new_w, "heading", args, n); i++;
    n = 0;
    XtSetArg(args[n], XmNfontName, EMPHASIS_FONT_NAME); n++;
    XtSetArg(args[n], XmNfontType, XmFONT_IS_FONT); n++;
    rend[i] = XmRenditionCreate(new_w, "emphasis", args, n); i++;
    n = 0;
    XtSetArg(args[n], XmNfontName, TITLE_FONT_NAME); n++;
    XtSetArg(args[n], XmNfontType, XmFONT_IS_FONT); n++;
    rend[i] = XmRenditionCreate(new_w, "title", args, n); i++; 
    n = 0;
    XtSetArg(args[n], XmNfontName, BOLD_FONT_NAME); n++;
    XtSetArg(args[n], XmNfontType, XmFONT_IS_FONT); n++;
    rend[i] = XmRenditionCreate(new_w, "subtitle", args, n); i++; 
    csRT = XmRenderTableAddRenditions(NULL, rend, i, XmMERGE_OLD);;
    nw -> help.rendertable = csRT;
    for(n = 0; n < i; n++)
      XmRenditionFree(rend[n]);
  } else {
    nw -> help.rendertable = 
      XmRenderTableCopy(nw -> help.rendertable, NULL, 0);
    csRT = nw -> help.rendertable;
  }

  /* Create internal widgets */
  n = 0;
  XtSetArg(args[n], XmNcurrentPageNumber, 1); n++;
  nw -> help.notebook = XmCreateNotebook(new_w, "Notebook", args, n);
  XtAddCallback(nw -> help.notebook, XmNpageChangedCallback, 
		(XtCallbackProc) page_change, (XtPointer) nw);

#ifdef USE_LABEL
  n = 0;
  XtSetArg(args[n], XmNscrollingPolicy, XmAUTOMATIC); n++;
  XtSetArg(args[n], XmNwidth, 500); n++;
  XtSetArg(args[n], XmNheight, 240); n++;
  XtSetArg(args[n], XmNpageNumber, 1); n++;
  XtSetArg(args[n], XmNresizable, FALSE); n++;
  XtSetArg(args[n], XmNnotebookChildType, XmPAGE); n++;
  display_parent = 
    XmCreateScrolledWindow(nw -> help.notebook, "Text_SW", args, n);
#endif /* USE_LABEL */

  n = 0;
  /* XtSetArg(args[n], XmNrenderTable, csRT); n++; */
  XtSetArg(args[n], XmNfontList, csRT); n++;
#ifdef USE_LABEL
  XtSetArg(args[n], XmNscrolledWindowChildType, XmWORK_AREA); n++;
  XtSetArg(args[n], XmNalignment, XmALIGNMENT_BEGINNING); n++;
  nw -> help.text_display = 
    XmCreateLabel(display_parent, "Text", args, n);
#else
  XtSetArg(args[n], XmNrows, 14); n++;
  XtSetArg(args[n], XmNcolumns, 60); n++;
  XtSetArg(args[n], XmNeditMode, XmMULTI_LINE_EDIT); n++;
  XtSetArg(args[n], XmNpageNumber, 1); n++;
  XtSetArg(args[n], XmNnotebookChildType, XmPAGE); n++;
  XtSetArg(args[n], XmNeditable, False); n++;
  nw -> help.text_display = 
    XmCreateScrolledCSText(nw -> help.notebook, "Text", args, n);
#endif /* USE_LABEL */

  n = 0;
  XtSetArg(args[n], XmNmarginWidth, 15); n++;
  XtSetArg(args[n], XmNmarginHeight, 10); n++;
  nw -> help.dismiss = XmCreatePushButton(new_w, "Dismiss", args, n);
  XtAddCallback(nw -> help.dismiss, XmNactivateCallback, 
		(XtCallbackProc) unmanage_cb, (XtPointer) new_w);
  /* this is also the default button */
  trait_default = (XmTakesDefaultTrait) 
    XmeTraitGet((XtPointer) XtClass(nw -> help.dismiss), XmQTtakesDefault) ;
  if (trait_default) 
    trait_default->showAsDefault(nw -> help.dismiss, XmDEFAULT_ON);

  nw -> help.allocated_titles = 0;

  /* Help path,  handle default value here */
  if (nw -> help.help_path != NULL)
    nw -> help.help_path = XtNewString(nw -> help.help_path);

  /* Help file */
  if (nw -> help.help_file != NULL)
    nw -> help.help_file = XtNewString(nw -> help.help_file);

  /* Read in file */
  ReadHelpFile(new_w);

  /* Initialize Notebook contents */
  page_change(nw -> help.notebook, new_w, NULL);

  /* Now manage children */
  XtManageChild(nw -> help.notebook);
#ifdef USE_LABEL
  XtManageChild(display_parent);
#endif /* USE_LABEL */
  XtManageChild(nw -> help.text_display);
  XtManageChild(nw -> help.dismiss);
}

/****************************************************************************
 *
 *  Destroy:
 *      Called when the widget is destroyed.
 *
 ****************************************************************************/
static void 
Destroy(
        Widget wid )
{   
  XmdHelpWidget help = (XmdHelpWidget) wid;
  int i;

  /* Cleanup internal allocations */
  for(i = 0; i < help -> help.num_titles; i++) {
    XtFree((char*) help -> help.titles[i]);
    XtFree((char*) help -> help.help_text[i]);
  }

  XtFree((char*) help -> help.titles);
  XtFree((char*) help -> help.help_text);
  XmRenderTableFree(help -> help.rendertable);
}

/*****************************************************************************
 *
 *  SetValues:
 *      Called by the Intrinsics whenever any of the resource values change.
 *
 ****************************************************************************/
static Boolean 
SetValues (
        Widget old_w,
        Widget request_w,
        Widget new_w,
        ArgList args,
        Cardinal *num_args 
          )
{
  XmdHelpWidget cw = (XmdHelpWidget)old_w;
  XmdHelpWidget rw = (XmdHelpWidget)request_w;
  XmdHelpWidget nw = (XmdHelpWidget)new_w;

  if (nw -> help.rendertable != cw -> help.rendertable) {
    /* Free the old */
    XmRenderTableFree(cw -> help.rendertable);
    /* Copy the new */
    nw -> help.rendertable = 
      XmRenderTableCopy(nw -> help.rendertable, NULL, 0);
    XtVaSetValues(nw -> help.text_display, 
		  XmNrenderTable, nw -> help.rendertable,
		  NULL, NULL);
  }

  /* Deal with new helpPath */
  if (nw -> help.help_path != cw -> help.help_path) {
   XtFree(cw -> help.help_path);

   if (nw -> help.help_path != NULL)
     nw -> help.help_path = XtNewString(nw -> help.help_path);
 }

 /* Deal with new helpFile */
 if (nw -> help.help_file != cw -> help.help_file) {
   XtFree(cw -> help.help_file);

   nw -> help.help_file = XtNewString(nw -> help.help_file);

   /* Read new helpfile here */
   ReadHelpFile(new_w);
 }

 return(False);
}	    

/****************************************************************************
 *
 *  Resize:
 *
 ****************************************************************************/
static void  
Resize (
        Widget w
       )
{
  Layout(w, NULL); 
}

/*************************************************************************
 *
 *  SetValuesAlmost:
 *       Called by the Intrinsics when an XtMakeGeometryRequest call
 *       returns either XmGeometryAlmost or XtGeometryNo.  
 *
 ***************************************************************************/
static void 
SetValuesAlmost(
        Widget cw,		/* unused */
        Widget nw,
        XtWidgetGeometry *request,
        XtWidgetGeometry *reply )
{  
  /* The parent said XtGeometryNo to the geometry request. 
     Therefore, we need to relayout because this request
     was due to a change in internal geometry resource of the ExmGrid */
    if (!reply->request_mode) {
      Layout(nw, NULL);
    }

    *request = *reply;
}

/***************************************************************************
 *
 *  Layout:
 *     Does all the placement of children.
 *     Instigator tells whether or not to resize all children.
 *
 *************************************************************************/
static void 
Layout(
        Widget wid,
        Widget instigator
       )
{
  XmdHelpWidget help = (XmdHelpWidget) wid;
  Widget child;
  int i;
  int x;
  int y;
  int spacing = help -> help.spacing;

  x = y = spacing;

  /* There are only a few children.  They are laid out in a simple
     left to right fashion */
  for (i = 0; i < help -> composite.num_children; i++) {
    child = help -> composite.children[i];

    if (XtIsManaged(child)) {
      if (instigator != child) {
	XmeConfigureObject(child, x, y, 
			   XtWidth(child), XtHeight(child),
			   XtBorderWidth(child));
	x += XtWidth(child) + spacing;
      }
    }
  }
}

/*************************************************************************
 *
 *  QueryGeometry:
 *       Called by a parent when the parent needs to find out the
 *       preferred size.
 *
 ***************************************************************************/
static XtGeometryResult 
QueryGeometry (
        Widget w,
        XtWidgetGeometry *request,
        XtWidgetGeometry *reply 
              )
{
  XmdHelpWidget help = (XmdHelpWidget) w;

  /* If the parent calls XtQueryGeometry before the widget has been 
     realized, use the current size as the preferred size. */ 
  /* Deal with user initial size setting */
    if (!XtIsRealized(w))  {  /* Widget is not yet realized. */
	reply->width = XtWidth(w) ;    /* might be 0 */
	reply->height = XtHeight(w) ;  /* might be 0 */
    } else {	    /* Widget is realized. */
	/* always computes natural size afterwards */
	reply->width = 0;
	reply->height = 0; 
    }

  CalcSize (w, NULL, &reply->width, &reply->height);

  /* This function handles CWidth and CHeight */
  return XmeReplyToQueryGeometry(w, request, reply) ;
}

/****************************************************************************
 *
 *  GeometryManager:
 *       Called by Intrinsics in response to a geometry change request from 
 *       one of the children
 *
 ***************************************************************************/
static XtGeometryResult 
GeometryManager (
        Widget w,  /* instigator */
        XtWidgetGeometry *request,
        XtWidgetGeometry *reply
                )
{
  XtWidgetGeometry parentRequest;
  XtGeometryResult result;
  Dimension curWidth, curHeight, curBW;
  Dimension new_width, new_height;

  /* Deny any requests for a new position. */
  if ((request->request_mode & CWX) || (request->request_mode & CWY))
    return XtGeometryNo ;

  /* Save the original child resources. */
  curWidth = w->core.width;
  curHeight = w->core.height;
  curBW = w->core.border_width;

  CalcSize(XtParent(w), w, &new_width, &new_height);

  /* Ask the Help's parent if new calculated size is acceptable. */
  parentRequest.request_mode = CWWidth | CWHeight;
  parentRequest.width = new_width;
  parentRequest.height = new_height;
  if (request->request_mode & XtCWQueryOnly)
    parentRequest.request_mode |= XtCWQueryOnly;
  result = XtMakeGeometryRequest ((Widget)XtParent(w), &parentRequest, NULL);

  /*  Turn XtGeometryAlmost into XtGeometryNo. */ 
  if (result == XtGeometryAlmost) 
    result = XtGeometryNo;

  if (result == XtGeometryNo || 
      request->request_mode & XtCWQueryOnly) { 
    /* Restore original geometry. */
    w->core.width = curWidth;
    w->core.height = curHeight;
    w->core.border_width = curBW;
  } else {    
    /* result == XtGeometryYes and this wasn't just a query */
    Layout (XtParent(w), w); /* Layout with this child as the instigator,
			       so that we don't resize this child. */
  }

  return(result);
}

/**************************************************************************
 *
 *  ChangeManaged:
 *      Called by the Intrinsics whenever either of the following happens:
 *           * a managed child becomes unmanaged.
 *           * an unmanaged child becomes managed.
 *
 *************************************************************************/
static void 
ChangeManaged(
        Widget w
             )
{
  XmdHelpWidget help = (XmdHelpWidget) w;
  Dimension helpWidth, helpHeight;
  int i;
	
  /* If you get an initial (C) size from the user or application, keep it.  
     Otherwise, just force width and height to 0 so that CalcSize will
     overwrite the appropriate fields. */ 
  if (!XtIsRealized(w))  {
    /* The first time, only attempts to change non specified sizes */
    helpWidth = XtWidth(w) ;	/* might be 0 */
    helpHeight = XtHeight(w) ;	/* might be 0 */
  } else {
    helpWidth = 0 ;
    helpHeight = 0 ;
  }

  CalcSize(w, NULL, &helpWidth, &helpHeight);

  /* Ask parent of Help if Help's new size is acceptable.  Keep asking until
     parent returns either XtGeometryYes or XtGeometryNo. */
  while (XtMakeResizeRequest (w, helpWidth, helpHeight,
			      &helpWidth, &helpHeight) == XtGeometryAlmost);
  Layout (w, NULL);
    
  /* Update keyboard traversal */
  XmeNavigChangeManaged (w);
}

/******************************************************************************
 *
 *  CalcSize:
 *     Called by QueryGeometry, SetValues, GeometryManager, and ChangeManaged.
 *     Calculate the ideal size of the Help widget. 
 *     Only affects the returned size if it is 0.
 *
 ****************************************************************************/
static void 
CalcSize (
        Widget wid,
        Widget instigator,
        Dimension *helpWidth,
        Dimension *helpHeight
         )
{
  XmdHelpWidget hw = (XmdHelpWidget) wid ;
  int i;
  int spacing = hw -> help.spacing;
  int width = 0;
  int height = 1;
  int x, y;

  x = y = spacing;
	
  /* There are only a few children.  They are laid out in a simple
     left to right fashion */
  for (i = 0; i < hw -> composite.num_children; i++) {
    int total_height;
    Dimension cw, ch, cb;
    XtWidgetGeometry reply;
    Widget child;
    
    child = hw -> composite.children[i];
    if (!XtIsManaged(child)) continue ;
	    
    /* Get child's preferred geometry if not the instigator. */
    if (child != instigator) {
      XtQueryGeometry (child, NULL, &reply);
      cw = (reply.request_mode & CWWidth) ? reply.width :
	child->core.width;
      ch = (reply.request_mode & CWHeight) ? reply.height :
	child->core.height;
    } else {
      cw = child->core.width;
      ch = child->core.height;
    }
    cb = child->core.border_width;

    total_height = 2 * (spacing + cb) + ch;
    height = MAX(height, total_height);
    width += spacing + cw;
  }

  width += spacing;

  if (!*helpWidth) *helpWidth = width;

  if (!*helpHeight) *helpHeight = height;
}

static Boolean 
ParentProcess(Widget wid, XmParentProcessData event )
{
  XmdHelpWidget hw = (XmdHelpWidget) wid;
  Widget dbutton = hw -> help.dismiss;
  XmPrimitiveClassRec *primitive_class;

  if(event->any.process_type == XmINPUT_ACTION) {
    primitive_class = (XmPrimitiveWidgetClass) XtClass(dbutton);
    if (primitive_class->primitive_class.arm_and_activate &&
	XtIsSensitive(dbutton))
      { 
	(*(primitive_class->primitive_class.arm_and_activate))
	  (dbutton, event->input_action.event,
	   event->input_action.params, event->input_action.num_params) ;
      } 
    
  return True;
  }

  return False;
}

/*****************************************************************************
 * ReadHelpFile
 *
 * This reads in the new helpfile using the values of help_file and 
 * help_path
 * 
 * help_path is a path in the syntax of a XtResolvePathname path
 *****************************************************************************/

static void 
ReadHelpFile(Widget w)
{
  XmdHelpWidget help = (XmdHelpWidget)w;
  char *full_pathname;
  char *filename;
  FILE *input;
  char line[256];
  int i;
  Widget tab;
  Arg args[10];
  int n;
  Boolean subtitle;

  if (help -> help.help_file == NULL)
    filename = "default";
  else
    filename = help -> help.help_file;

  full_pathname = XtResolvePathname(XtDisplay(w), "help", filename, ".help",
				    help -> help.help_path,
				    NULL, 0, NULL);

  /* If not found using the help_path supplied (or XFILESEARCHPATH
     if help_path is NULL),  then try using a builtin search path
     which includes the current directory */
  if (full_pathname == NULL)
    full_pathname = XtResolvePathname(XtDisplay(w), "help", filename, ".help",
				      DEFAULTHP, NULL, 0, NULL);

  if (full_pathname == NULL) { /* Failure */
    sprintf(line, "Couldn't find file %s in the path given.\n", filename);
    XmeWarning(w, line);
    return;
  }

  /* Cleanup internal allocations (if any) */
  for(i = 0; i < help -> help.num_titles; i++) {
    XtFree((char*) help -> help.titles[i]);
    XtFree((char*) help -> help.help_text[i]);
  }

  help -> help.num_titles = 0;

  /* Otherwise read it in */

  /* The file consists of markers.  <title>Section-header</title>
     will delimit sections and will always start at the beginning
     of the line to help us "notice" them.  We'll read in from one
     of these to the beginning of the next,  concatenating lines.
     Then we parse it using the XmString parser */
  input = fopen(full_pathname, "r");
  if (input == NULL) return;

  fgets(line, 256, input);

  /* Read until we find a title */
  while(! feof(input) && 
	(subtitle = strncmp(line,"<title>",7) != 0) &&
	strncmp(line,"<subtitle>", 10) != 0)
    fgets(line, 256, input);

  while(! feof(input)) {
    XmString tmp;
    int len;

    if (feof(input)) break;

    /* Up allocation if needed */
    if (help -> help.num_titles >= help -> help.allocated_titles) {
      help -> help.allocated_titles += 10;
      help -> help.titles =
	(XmStringTable) XtRealloc((char*) help -> help.titles,
				  sizeof(XmString) * 
				  help -> help.allocated_titles);
      help -> help.help_text =
	(XmStringTable) XtRealloc((char*) help -> help.help_text,
				  sizeof(XmString) * 
				  help -> help.allocated_titles);
    }

    /* Remove the trailing newline */
    len = strlen(line);
    if (line[len-1] == '\n') line[len-1] = 0;

    /* Parse the title line */
    help -> help.titles[help -> help.num_titles] = parse_text(line);
    /* Make the tab */
    n = 0;
    XtSetArg(args[n], XmNpageNumber, help -> help.num_titles + 1); n++;
    if (! subtitle) {
      XtSetArg(args[n], XmNnotebookChildType, XmMAJOR_TAB); n++;
    } else {
      XtSetArg(args[n], XmNnotebookChildType, XmMINOR_TAB); n++;
    }
#ifdef USE_TAB
    XtSetArg(args[n], ExmNcompoundString, 
	     help -> help.titles[help -> help.num_titles]); n++;
    tab = ExmCreateTabButton(help -> help.notebook, "tab", args, n);
#else
    XtSetArg(args[n], XmNlabelString, 
	     help -> help.titles[help -> help.num_titles]); n++;
    tab = XmCreatePushButton(help -> help.notebook, "tab", args, n);
#endif /* USE_TAB */
    XtManageChild(tab);
    
    
    /* Now start parsing the rest,  until we find another line
       which has <title> at the begin */
    subtitle = False;
    tmp = XmStringCreateLocalized("");
    fgets(line, 256, input);
    while(! feof(input) &&
	  (subtitle = strncmp(line,"<title>", 7) != 0) &&
	  strncmp(line,"<subtitle>", 10) != 0) {
      tmp = XmStringConcatAndFree(tmp, parse_text(line));
      fgets(line, 256, input);
    }
    help -> help.help_text[help -> help.num_titles++] = tmp;
  }

  fclose(input);

  /* Setup notebook */
  XtVaSetValues(help -> help.notebook,
		XmNlastPageNumber, help -> help.num_titles,
		XmNcurrentPageNumber, 1,
		NULL, NULL);
}


static XmIncludeStatus 
parse_proc(XtPointer      *in_out,
	   XtPointer       text_end,
	   XmTextType      type,
	   XmStringTag     tag,
	   XmParseMapping  entry,
	   int		   pattern_length,
	   XmString       *str_include,
	   XtPointer       call_data)
{
  char *rendition_name;
  Boolean start = True;
  char *ptr;
  int len;

  /* The remaining characters are either rendition or /rendition to
     indicate the start or end of a rendition */

  ptr = (char*) *in_out;
  ptr++;

  if (*ptr == '/') {
    start = False;
    ptr++;
  }

  /* Get rendition name.  The name ends at the > delimiter */
  rendition_name = ptr;
  ptr = strchr(ptr, '>');
  if (ptr == NULL) {
    str_include = NULL;
    return XmINSERT;
  }

  /* Null terminate tag */
  *ptr = 0;
  ptr++;
  rendition_name = XtNewString(rendition_name);
  len = strlen(rendition_name);

  *in_out = (XtPointer) ptr;
  if (start)
    *str_include =
      XmStringComponentCreate(XmSTRING_COMPONENT_RENDITION_BEGIN, len, 
			      rendition_name);
  else
    *str_include =
      XmStringComponentCreate(XmSTRING_COMPONENT_RENDITION_END, len, 
			      rendition_name);
  XtFree(rendition_name);
  return XmINSERT;
}

static XmIncludeStatus 
esc_parse_proc(XtPointer      *in_out,
	       XtPointer       text_end,
	       XmTextType      type,
	       XmStringTag     tag,
	       XmParseMapping  entry,
	       int	       pattern_length,
	       XmString       *str_include,
	       XtPointer       call_data)
{
  char *ptr;
  char temp[2];

  ptr = (char*) *in_out;
  ptr++;

  /* Move to the next character and create an XmString for it */
  temp[0] = *ptr++;
  temp[1] = 0;
  *str_include = XmStringCreateLocalized(temp);

  *in_out = (XtPointer) ptr;

  return XmINSERT;
}

static XmString 
parse_text(String value)
{
  static XmParseTable table = NULL;
  XmString result;
  int table_size = 4;

  /* Allocate a parse table if necessary. */
  if (!table)
    {
      Arg args[10];
      Cardinal nargs;
      XmString tmp;
      int index = 0;

      table = (XmParseTable) XtCalloc(table_size, sizeof(XmParseMapping));

      tmp = XmStringComponentCreate(XmSTRING_COMPONENT_TAB, 0, NULL);
      nargs = 0;
      XtSetArg(args[nargs], XmNincludeStatus, XmINSERT), nargs++;
      XtSetArg(args[nargs], XmNsubstitute, tmp), 	 nargs++;
      XtSetArg(args[nargs], XmNpattern, "\t"), 		 nargs++;
      table[index++] = XmParseMappingCreate(args, nargs);
      XmStringFree(tmp);

      tmp = XmStringSeparatorCreate();
      nargs = 0;
      XtSetArg(args[nargs], XmNincludeStatus, XmINSERT), nargs++;
      XtSetArg(args[nargs], XmNsubstitute, tmp),	 nargs++;
      XtSetArg(args[nargs], XmNpattern, "\n"),		 nargs++;
      table[index++] = XmParseMappingCreate(args, nargs);

      nargs = 0;
      XtSetArg(args[nargs], XmNincludeStatus, XmINVOKE), nargs++;
      XtSetArg(args[nargs], XmNpattern, "\\"),		 nargs++;
      XtSetArg(args[nargs], XmNinvokeParseProc, esc_parse_proc), nargs++;
      table[index++] = XmParseMappingCreate(args, nargs);

      nargs = 0;
      XtSetArg(args[nargs], XmNpattern, "<"), 	 	     nargs++;
      XtSetArg(args[nargs], XmNincludeStatus, XmINVOKE),     nargs++;
      XtSetArg(args[nargs], XmNinvokeParseProc, parse_proc), nargs++;
      table[index++] = XmParseMappingCreate(args, nargs);
      XmStringFree(tmp);

    }

  /* Parse the text into an XmString. */
  result = XmStringParseText(value, NULL, NULL, XmCHARSET_TEXT, 
			     table, table_size, NULL);
  return(result);
}

static void 
page_change(Widget w, XtPointer help_w, XmNotebookCallbackStruct *cb)
{
  XmdHelpWidget help = (XmdHelpWidget) help_w;
  int index = cb == NULL ? 0 : cb -> page_number - 1;

  if (index < 0) index = 0;

  if (index >= help -> help.num_titles) return;

  XtVaSetValues(help -> help.text_display,
#ifdef USE_LABEL
		XmNlabelString,	help -> help.help_text[index],
#else
		XmNcstextValue,	help -> help.help_text[index],
#endif /* USE_LABEL */
		NULL, NULL);

  XtVaSetValues(
#ifdef USE_LABEL
		XtParent(XtParent(help -> help.text_display)),
#else
		XtParent(help -> help.text_display),
#endif /* USE_LABEL */
		XmNpageNumber, index + 1,
		NULL, NULL);
}

static void 
unmanage_cb(Widget button, Widget hw, XtPointer ignore)
{
  XtUnmanageChild(hw);
}

/* 
 * External functions
 */

/******************************************************************************
 *
 *  XmdCreateHelp:
 *      Called by an application. 
 *
 *****************************************************************************/
Widget 
XmdCreateHelp (
        Widget parent,
        char *name,
        ArgList arglist, 
        Cardinal argcount
              )
{
  /* This is a convenience function to instantiate an XmdHelp widget. */
  return (XtCreateWidget (name, xmdHelpWidgetClass, parent, 
			  arglist, argcount));
}

/******************************************************************************
 *
 *  XmdCreateHelpDialog
 *      Called by an application to create an XmdHelp managed by a
 *      DialogShell. 
 *
 *****************************************************************************/
Widget 
XmdCreateHelpDialog (
        Widget parent,
        char *name,
        ArgList arglist, 
        Cardinal argcount
              )
{
  return(XmeCreateClassDialog(xmdHelpWidgetClass, 
			      parent, name, arglist, argcount));
}

void 
XmdGotoHelpItem(Widget w, int item, Widget help)
{
  Widget notebook = XtNameToWidget(help, "*Notebook");
  XmdHelpWidget hw = (XmdHelpWidget) help;

  if (item < 0 || item >= hw -> help.num_titles) return;

  XtVaSetValues(notebook, XmNcurrentPageNumber, item + 1, NULL, NULL);
}
