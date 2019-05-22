/* $XConsortium: Print.c /main/5 1995/07/15 20:43:49 drk $ */
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
#include <stdio.h>
#include <Xm/XmP.h>
#include <Xm/ToggleB.h>
#include <Xm/ToggleBG.h>
#include <Xm/TextF.h>
#include <Xm/LabelG.h>
#include <Xm/PushBG.h>
#include <Xm/SeparatoG.h>
#include <Xm/RowColumn.h>
#include <Xm/MessageB.h>
#include <Xm/SelectioB.h>
#include "PrintP.h"
#include <stdlib.h>
#include <ctype.h>

#define MAX(x,y) ((x) > (y) ? (x) : (y))

/* Declare static functions. */
static void Initialize(
                        Widget request_w,
                        Widget new_w,
                        ArgList args,
                        Cardinal *num_args );
static void Destroy( 
                        Widget wid) ;
static Boolean SetValues (
                        Widget old_w,
                        Widget request_w,
                        Widget new_w,
                        ArgList args,
                        Cardinal *num_args );
static void process_printer_list(Widget);
static void from_all_change_cb(Widget toggle, XtPointer parent,
			       XmToggleButtonCallbackStruct *cb);
static void numeric_only_cb(Widget textf, XtPointer, 
			    XmTextVerifyCallbackStruct *cb);
static void do_print_cb(Widget, Widget, XtPointer);
static void do_help_cb(Widget, Widget, XtPointer);
static void unmanage_cb(Widget, Widget, XtPointer);
static void post_add_printer(Widget, Widget, 
			     XmPushButtonCallbackStruct *cb);
static void post_add_pathname(Widget, Widget, 
			      XmPushButtonCallbackStruct *cb);
static void add_printer_cb(Widget, XtPointer,
			   XmSelectionBoxCallbackStruct *cb);
static void cancel_printer_cb(Widget, XtPointer,
			      XmSelectionBoxCallbackStruct *cb);

/* No translations and no actions. */

/* Define the resources for the XmdPrint widget. */ 
static XtResource resources[] =
{
  { XmdNprinterList, XmdCPrinterList, XmRString, sizeof(String),
      XtOffsetOf( XmdPrintRec, print.printer_list ),
      XmRImmediate, (XtPointer) NULL },
  { XmdNtwoSided, XmdCTwoSided, XmRBoolean, sizeof(Boolean),
      XtOffsetOf( XmdPrintRec, print.two_sided ),
      XmRImmediate, (XtPointer) False },
  { XmdNreverseOrder, XmdCReverseOrder, XmRBoolean, sizeof(Boolean),
      XtOffsetOf( XmdPrintRec, print.reverse_order ),
      XmRImmediate, (XtPointer) False },
  { XmdNfromPage, XmdCFromPage, XmRInt, sizeof(int),
      XtOffsetOf( XmdPrintRec, print.from_page ),
      XmRImmediate, (XtPointer) 0 },
  { XmdNtoPage, XmdCToPage, XmRInt, sizeof(int),
      XtOffsetOf( XmdPrintRec, print.to_page ),
      XmRImmediate, (XtPointer) 0 },
  { XmdNprintAll, XmdCPrintAll, XmRBoolean, sizeof(Boolean),
      XtOffsetOf( XmdPrintRec, print.print_all ),
      XmRImmediate, (XtPointer) True },
  { XmdNnumberOfCopies, XmdCNumberOfCopies, XmRInt, sizeof(int),
      XtOffsetOf( XmdPrintRec, print.number_of_copies ),
      XmRImmediate, (XtPointer) 1 },
  { XmdNprintCallback, XmCCallback, XmRCallback, 
      sizeof(XtCallbackList),
      XtOffsetOf( XmdPrintRec, print.print_callback ),
      XmRPointer, (XtPointer) NULL }
};

/* Define the widget class record.  See Chapter 4 of the 
   "OSF/Motif Widget Writer's Guide" for details. */ 
externaldef(Xmdprintclassrec) XmdPrintClassRec xmdPrintClassRec = 
{ 
  { /* Here is the Core class record. */ 
    /* superclass */                 (WidgetClass) &xmFormClassRec,
    /* class_name */                 "XmdPrint",
    /* widget_size */                sizeof(XmdPrintRec),
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
    /* resize */                     XtInheritResize,
    /* expose */                     XtInheritExpose,
    /* set_values */                 SetValues,
    /* set_values_hook */            NULL,
    /* set_values_almost */          XtInheritSetValuesAlmost,
    /* get_values_hook */            NULL,
    /* accept_focus */               NULL,
    /* version */                    XtVersion,
    /* callback_private */           NULL,
    /* tm_table */                   XtInheritTranslations,
    /* query_geometry */             XtInheritQueryGeometry,
    /* display_accelerator */        NULL,
    /* extension */                  NULL,
  },    
  { /* Here is the Composite class record. */ 
    /* geometry_manager */           XtInheritGeometryManager,
    /* change_managed */             XtInheritChangeManaged,
    /* insert_child */               XtInheritInsertChild,
    /* delete_child */               XtInheritDeleteChild,
    /* extension */                  NULL,
  },    
  { /* Here is the Constaint class record. */ 
    /* constraint_resources */       NULL,
    /* constraint_num_resources */   0,
    /* constraint_size */            sizeof(XmdPrintConstraintRec), 
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
    /* parent_process */             XmInheritParentProcess,
    /* extension */                  NULL,
  },    
  {                        /* bulletin_board_class fields */
    FALSE,                                /* always_install_accelerators */
    (XmGeoCreateProc)NULL,                /* geo_matrix_create  */
    XmInheritFocusMovedProc,              /* focus_moved_proc   */
    NULL,                                 /* extension          */
  },
  {                        /* form_class fields  */
    (XtPointer) NULL,                     /* extension          */
  },
  { /* Here is the XmdPrint class record. */ 
      (XtPointer) NULL, 		    /* extension */ 
  }    
};    

/* Establish the widget class name as an externally accessible symbol.
   Use the "externaldef" macro rather than the "extern" keyword. */
externaldef(Xmdprintwidgetclass) WidgetClass xmdPrintWidgetClass =
    (WidgetClass) &xmdPrintClassRec;

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
  XmdPrintWidget rw = (XmdPrintWidget) request_w;
  XmdPrintWidget nw = (XmdPrintWidget) new_w;
  Arg args[20];
  int n, i;
  Widget tmp;
  Widget rc_tmp, rc_tmp2;
  Widget printb, cancelb, helpb, sep;
  XmString str, str2;
  char buf[20];

  /* Initialize internal fields */
  nw -> print.num_printers = 0;
  nw -> print.printers = (char**) NULL;
  nw -> print.is_printer = (Boolean*) NULL;
  nw -> print.adding_printer = False;
  nw -> print.num_om_items = 0;
  nw -> print.om_items = (WidgetList) NULL;

  /* Create Manager for each line of widgets.  This will make them
     baseline aligned,  which is much more attractive */
  n = 0;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNtopOffset, 10); n++;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNleftOffset, 10); n++;
  XtSetArg(args[n], XmNspacing, 10); n++;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
  XtSetArg(args[n], XmNpacking, XmPACK_TIGHT); n++;
  rc_tmp = XmCreateRowColumn(new_w, "rc", args, n);
  XtManageChild(rc_tmp);

  /* Create child widgets */
  /* Label for Copies */
  n = 0;
  str = XmStringCreateLocalized("Copies");
  XtSetArg(args[n], XmNlabelString, str); n++;
  tmp = XmCreateLabelGadget(rc_tmp, "copies", args, n);
  XtManageChild(tmp);
  XmStringFree(str);

  /* Text Field for # Copies */
  n = 0;
  XtSetArg(args[n], XmNtopOffset, 15); n++;
  XtSetArg(args[n], XmNcolumns, 3); n++;
  nw -> print.copies_tf = XmCreateTextField(rc_tmp, "copies_tf", args, n);
  XtManageChild(nw -> print.copies_tf);
  XtAddCallback(nw -> print.copies_tf, XmNmodifyVerifyCallback,
		(XtCallbackProc) numeric_only_cb, NULL);
  
  /* Create Manager for each line of widgets.  This will make them
     baseline aligned,  which is much more attractive */
  n = 0;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
  XtSetArg(args[n], XmNtopWidget, rc_tmp); n++;
  XtSetArg(args[n], XmNtopOffset, 10); n++;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNleftOffset, 10); n++;
  XtSetArg(args[n], XmNspacing, 10); n++;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
  XtSetArg(args[n], XmNpacking, XmPACK_TIGHT); n++;
  rc_tmp2 = XmCreateRowColumn(new_w, "rc2", args, n);
  XtManageChild(rc_tmp2);

  /* Toggle for 2 sided */
  n = 0;
  str = XmStringCreateLocalized("2 sided");
  XtSetArg(args[n], XmNlabelString, str); n++;
  nw -> print.two_sided_toggle = 
    XmCreateToggleButtonGadget(rc_tmp2, "two_sided_toggle", args, n);
  XtManageChild(nw -> print.two_sided_toggle);
  XmStringFree(str);

  /* Toggle for reverse order */
  n = 0;
  str = XmStringCreateLocalized("Reverse Order");
  XtSetArg(args[n], XmNlabelString, str); n++;
  nw -> print.reverse_order_toggle = 
    XmCreateToggleButtonGadget(rc_tmp2, "reverse_order_toggle", args, n);
  XtManageChild(nw -> print.reverse_order_toggle);
  XmStringFree(str);

  /* Manager for all/from order */
  n = 0;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_WIDGET); n++;
  XtSetArg(args[n], XmNtopWidget, rc_tmp2); n++;
  XtSetArg(args[n], XmNtopOffset, 10); n++;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNleftOffset, 10); n++;
  XtSetArg(args[n], XmNorientation, XmHORIZONTAL); n++;
  XtSetArg(args[n], XmNpacking, XmPACK_TIGHT); n++;
  XtSetArg(args[n], XmNspacing, 10); n++;
  XtSetArg(args[n], XmNradioBehavior, True); n++;
  XtSetArg(args[n], XmNradioAlwaysOne, True); n++;
  nw -> print.from_all_rc = XmCreateRowColumn(new_w, "from_all_rc", args, n);
  XtManageChild(nw -> print.from_all_rc);

  /* Toggle for all */
  n = 0;
  str = XmStringCreateLocalized("All");
  XtSetArg(args[n], XmNlabelString, str); n++;
  nw -> print.all_toggle = 
    XmCreateToggleButtonGadget(nw -> print.from_all_rc, "all_toggle", args, n);
  XtManageChild(nw -> print.all_toggle);
  XmStringFree(str);

  /* Toggle for from */
  n = 0;
  str = XmStringCreateLocalized("From");
  XtSetArg(args[n], XmNlabelString, str); n++;
  nw -> print.from_toggle = 
    XmCreateToggleButtonGadget(nw -> print.from_all_rc, "from_toggle", 
			       args, n);
  XtManageChild(nw -> print.from_toggle);
  XmStringFree(str);
  
  /* from text field */
  n = 0;
  XtSetArg(args[n], XmNcolumns, 3); n++;
  nw -> print.from_tf = XmCreateTextField(nw -> print.from_all_rc, "from_tf",
					  args, n);
  XtManageChild(nw -> print.from_tf);
  XtAddCallback(nw -> print.from_tf, XmNmodifyVerifyCallback,
		(XtCallbackProc) numeric_only_cb, NULL);

  /* To label */
  tmp = XmCreateLabelGadget(nw -> print.from_all_rc, "to", NULL, 0);
  XtManageChild(tmp);

  /* to text field */
  n = 0;
  XtSetArg(args[n], XmNcolumns, 3); n++;
  nw -> print.to_tf = XmCreateTextField(nw -> print.from_all_rc, "to_tf",
					  args, n);
  XtManageChild(nw -> print.to_tf);
  XtAddCallback(nw -> print.to_tf, XmNmodifyVerifyCallback,
		(XtCallbackProc) numeric_only_cb, NULL);

  /* destination PD */
  nw -> print.destination_pd = XmCreatePulldownMenu(new_w, "pd", NULL, 0);

  /* destination OM */
  n = 0;
  str = XmStringCreateLocalized("Destination:");
  XtSetArg(args[n], XmNlabelString, str); n++;
  XtSetArg(args[n], XmNmnemonic, 'D'); n++;
  XtSetArg(args[n], XmNsubMenuId, nw -> print.destination_pd); n++;
  nw -> print.destination_om = XmCreateOptionMenu(rc_tmp, "om", args, n);
  XtManageChild(nw -> print.destination_om);

  tmp = XmCreateSeparatorGadget(nw -> print.destination_pd,
				"sep", NULL, 0);
  XtManageChild(tmp);

  /* New printer or pathname dialog */
  n = 0;
  str = XmStringCreateLocalized("Enter a new value");
  str2 = XmStringCreateLocalized("Add");
  XtSetArg(args[n], XmNselectionLabelString, str); n++;
  XtSetArg(args[n], XmNokLabelString, str2); n++;
  nw -> print.new_printer_dialog = 
    XmCreatePromptDialog(new_w, "QueryDestination", args, n);
  XmStringFree(str);
  XmStringFree(str2);
  XtAddCallback(nw -> print.new_printer_dialog,
		XmNokCallback, (XtCallbackProc) add_printer_cb,
		(XtPointer) new_w);
  XtAddCallback(nw -> print.new_printer_dialog,
		XmNcancelCallback, (XtCallbackProc) cancel_printer_cb,
		(XtPointer) new_w);

  tmp = XmCreatePushButtonGadget(nw -> print.destination_pd,
				 "Other Printer...", NULL, 0);
  XtManageChild(tmp);
  XtAddCallback(tmp, XmNactivateCallback, 
		(XtCallbackProc) post_add_printer, (XtPointer) new_w);

  tmp = XmCreatePushButtonGadget(nw -> print.destination_pd,
				 "Other File...", NULL, 0);
  XtManageChild(tmp);
  XtAddCallback(tmp, XmNactivateCallback, 
		(XtCallbackProc) post_add_pathname, (XtPointer) new_w);

  process_printer_list(new_w);

  XtAddCallback(nw -> print.all_toggle, XmNvalueChangedCallback,
		(XtCallbackProc) from_all_change_cb, (XtPointer) new_w);

  /* Setup Dialog buttons */
  n = 0;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNtopOffset, 2); n++;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
  XtSetArg(args[n], XmNleftWidget, rc_tmp); n++;
  XtSetArg(args[n], XmNleftOffset, 5); n++;
  XtSetArg(args[n], XmNbottomAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNbottomOffset, 2); n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
  sep = XmCreateSeparatorGadget(new_w, "sep", args, n);
  XtManageChild(sep);


  /* Create Manager for dialog buttons.  These buttons are stacked
     at the right edge of the dialog */
  n = 0;
  XtSetArg(args[n], XmNtopAttachment, XmATTACH_FORM); n++;
  XtSetArg(args[n], XmNtopOffset, 10); n++;
  XtSetArg(args[n], XmNleftAttachment, XmATTACH_WIDGET); n++;
  XtSetArg(args[n], XmNleftWidget, sep); n++;
  XtSetArg(args[n], XmNleftOffset, 5); n++;
  XtSetArg(args[n], XmNrightOffset, 10); n++;
  XtSetArg(args[n], XmNspacing, 10); n++;
  XtSetArg(args[n], XmNorientation, XmVERTICAL); n++;
  rc_tmp2 = XmCreateRowColumn(new_w, "rc_buttons", args, n);
  XtManageChild(rc_tmp2);

  n = 0;
  XtSetArg(args[n], XmNmarginWidth, 20); n++;
  printb = XmCreatePushButtonGadget(rc_tmp2, "Print", args, n);
  XtAddCallback(printb, XmNactivateCallback, 
		(XtCallbackProc) do_print_cb, (XtPointer) new_w);
  XtManageChild(printb);
  cancelb = XmCreatePushButtonGadget(rc_tmp2, "Cancel", args, n);
  XtAddCallback(cancelb, XmNactivateCallback, 
		(XtCallbackProc) unmanage_cb, (XtPointer) new_w);
  XtManageChild(cancelb);
  helpb = XmCreatePushButtonGadget(rc_tmp2, "Help", args, n);
  XtAddCallback(helpb, XmNactivateCallback, 
		(XtCallbackProc) do_help_cb, (XtPointer) new_w);
  XtManageChild(helpb);

  /* Setup ParentProcess information */
  XtVaSetValues(new_w, XmNdefaultButton, printb,
		XmNcancelButton, cancelb,
		NULL, NULL);

  /* Process initial values */
  if (nw -> print.print_all) {
    XmToggleButtonGadgetSetState(nw -> print.all_toggle, True, True);
  } else {
    XmToggleButtonGadgetSetState(nw -> print.all_toggle, False, True);
  }

  sprintf(buf, "%d", nw -> print.from_page);
  XmTextFieldSetString(nw -> print.from_tf, buf);

  sprintf(buf, "%d", nw -> print.to_page);
  XmTextFieldSetString(nw -> print.to_tf, buf);

  sprintf(buf, "%d", nw -> print.number_of_copies);
  XmTextFieldSetString(nw -> print.copies_tf, buf);

  XmToggleButtonGadgetSetState(nw -> print.two_sided_toggle,
			       nw -> print.two_sided, False);
  XmToggleButtonGadgetSetState(nw -> print.reverse_order_toggle,
			       nw -> print.reverse_order, False);

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
  XmdPrintWidget print = (XmdPrintWidget) wid;
  char** strings;
  int count;
  int i;

  strings = print -> print.printers;
  count = print -> print.num_printers;

  /* Cleanup internal allocations */
  for(i = 0; i < count; i++)
    XtFree(strings[i]);
  XtFree((char*) print -> print.printers);

  XtFree((char*) print -> print.is_printer);

  XtFree((char*) print -> print.om_items);
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
  XmdPrintWidget cw = (XmdPrintWidget)old_w;
  XmdPrintWidget rw = (XmdPrintWidget)request_w;
  XmdPrintWidget nw = (XmdPrintWidget)new_w;
  char buf[32];

  process_printer_list(new_w);

  if (nw -> print.print_all != cw -> print.print_all) {
    if (nw -> print.print_all) {
      XmToggleButtonGadgetSetState(nw -> print.all_toggle, True, False);
      XtSetSensitive(nw -> print.from_tf, False);
      XtSetSensitive(nw -> print.to_tf, False);
    } else {
      XmToggleButtonGadgetSetState(nw -> print.from_toggle, True, False);
    }
  }

  if (nw -> print.from_page != cw -> print.from_page) {
    sprintf(buf, "%d", nw -> print.from_page);
    XmTextFieldSetString(nw -> print.from_tf, buf);
  }

  if (nw -> print.to_page != cw -> print.to_page) {
    sprintf(buf, "%d", nw -> print.to_page);
    XmTextFieldSetString(nw -> print.to_tf, buf);
  }

  if (nw -> print.number_of_copies != cw -> print.number_of_copies) {
    sprintf(buf, "%d", nw -> print.number_of_copies);
    XmTextFieldSetString(nw -> print.copies_tf, buf);
  }

  if (nw -> print.two_sided != cw -> print.two_sided)
    XmToggleButtonGadgetSetState(nw -> print.two_sided_toggle,
				 nw -> print.two_sided, False);

  if (nw -> print.reverse_order != cw -> print.reverse_order)
    XmToggleButtonGadgetSetState(nw -> print.reverse_order_toggle,
				 nw -> print.reverse_order, False);

  return(False);
}	    

static void 
process_printer_list(Widget w)
{
  XmdPrintWidget pw = (XmdPrintWidget)w;
  char *str = pw -> print.printer_list;
  char c;
  int n;
  int count;
  Boolean is_path;
  char buf[128];

  /* Clear up old printers (if any) */
  XtUnmanageChildren(pw -> print.om_items, pw -> print.num_om_items);

  for(n = 0; n < pw -> print.num_printers; n++)
    XtFree((char*) pw -> print.printers[n]);
  pw -> print.num_printers = 0;

  if (str == NULL) return;

  /* List of printers is separated with commas or whitespace */
  n = 0;
  while(str[n] != 0) {
    /* skip whitespace and punctuation */
    while((c = str[n]) != 0 &&
	  (isspace(c) || ispunct(c))) n++;
    /* gather characters until whitespace or comma seen */
    count = 0;
    is_path = False;
    while((c = str[n]) != 0 &&
	  ! (isspace(c) || c == ',')) {
      if (c == '/' || c == '~' || c == '.') is_path = True;
      buf[count++] = c;
      n++;
    }
    /* Terminate with 0 */
    buf[count++] = 0;
    /* Make sure printer lists are big enough */
    pw -> print.printers = (char**) XtRealloc((char*) pw -> print.printers,
					      sizeof(char*) * 
					      pw -> print.num_printers + 1);
    pw -> print.is_printer = 
      (Boolean*) XtRealloc((char*) pw -> print.is_printer,
			   sizeof(Boolean) * pw -> print.num_printers + 1);
    pw -> print.printers[pw -> print.num_printers] = XtNewString(buf);
    pw -> print.is_printer[pw -> print.num_printers] = ! is_path;
    pw -> print.num_printers++;
  }

  /* Process list of printers.  Make sure widget array is big enough
     for files and printers */
  if (pw -> print.num_printers > pw -> print.num_om_items) {
    n = pw -> print.num_om_items;
    pw -> print.num_om_items = pw -> print.num_printers;
    pw -> print.om_items = (WidgetList) XtRealloc((char*) pw -> print.om_items,
						  sizeof(Widget) * 
						  pw -> print.num_om_items);
    /* zero out new ones */
    while(n < pw -> print.num_om_items) 
      pw -> print.om_items[n++] = (Widget) 0;
  }

  /* Now put new strings in */
  for(count = 0; count < pw -> print.num_printers; count++) {
    XmString str;

    str = XmStringCreateLocalized(pw -> print.printers[count]);
    if (pw -> print.om_items[count] != (Widget) 0) 
      XtVaSetValues(pw -> print.om_items[count],
		    XmNlabelString, str, 
		    NULL, NULL);
    else {
      Arg args[2];
      XtSetArg(args[0], XmNlabelString, str);
      pw -> print.om_items[count] =
	XmCreatePushButtonGadget(pw -> print.destination_pd, "button", 
				 args, 1);
    }
    XtManageChild(pw -> print.om_items[count]);
    XmStringFree(str);
  }

  /* Fix the position of the widgets in the list */
  for(n = pw -> print.num_om_items; n > 0; n--)
    XtVaSetValues(pw -> print.om_items[n - 1],
		  XmNpositionIndex, 0,
		  NULL, NULL);
}

static void
from_all_change_cb(Widget toggle, XtPointer parent,
		   XmToggleButtonCallbackStruct *cb)
{
  XmdPrintWidget pw = (XmdPrintWidget) parent;
  Boolean state = ! cb -> set;

  XtSetSensitive(pw -> print.from_tf, state);
  XtSetSensitive(pw -> print.to_tf, state);
}

static void 
numeric_only_cb(Widget textf, XtPointer ignore, 
		XmTextVerifyCallbackStruct *cb)
{
  if (cb -> text -> length > 0 &&
      ! isdigit(cb -> text -> ptr[0]))
    cb -> doit = False;
}

static void 
do_print_cb(Widget button, Widget pw, XtPointer ignore)
{
  XmdPrintWidget print = (XmdPrintWidget) pw;
  XmdPrintCallbackStruct cbstruct;
  Widget history;
  int i;
  char* temp;

  cbstruct.reason = XmCR_OK;
  cbstruct.event = NULL;
  cbstruct.two_sided = 
    XmToggleButtonGetState(print -> print.two_sided_toggle);
  cbstruct.reverse_order = 
    XmToggleButtonGetState(print -> print.reverse_order_toggle);
  temp = XmTextFieldGetString(print -> print.copies_tf);
  cbstruct.copies = atol(temp);
  XtFree(temp);

  cbstruct.to_printer = True;
  if (XmToggleButtonGetState(print -> print.all_toggle)) {
    cbstruct.first = 0;
    cbstruct.last = 0;
  } else {
    temp = XmTextFieldGetString(print -> print.from_tf);
    cbstruct.first = atol(temp);
    XtFree(temp);

    temp = XmTextFieldGetString(print -> print.to_tf);
    cbstruct.last = atol(temp);
    XtFree(temp);
  }
  XtVaGetValues(print -> print.destination_om,
		XmNmenuHistory, &history,
		NULL, NULL);
  /* Find the right widget.  This will tell us the value */
  for(i = 0; i < print -> print.num_om_items; i++) 
    if (print -> print.om_items[i] == history) break;

  cbstruct.printer = NULL; /* Error case */
  if (i < print -> print.num_printers) {
    cbstruct.printer = print -> print.printers[i];
    cbstruct.to_printer = print -> print.is_printer[i];
  } 

  /* Call the printer callbacks */
  XtCallCallbackList(pw, print -> print.print_callback,
		     (XtPointer) &cbstruct);

  XtUnmanageChild(pw);
}

static void 
do_help_cb(Widget button, Widget pw, XtPointer ignore)
{
  XmdPrintWidget print = (XmdPrintWidget) pw;
  XmAnyCallbackStruct cb;

  cb.reason = XmCR_HELP;
  cb.event = NULL;

  XtCallCallbackList(pw, print -> manager.help_callback, (XtPointer) &cb);

  XtUnmanageChild(pw);
}

static void 
unmanage_cb(Widget button, Widget pw, XtPointer ignore)
{
  XtUnmanageChild(pw);
}

static void 
post_add_printer(Widget w, Widget pw,
		 XmPushButtonCallbackStruct *cb)
{
  XmdPrintWidget print = (XmdPrintWidget) pw;

  print -> print.adding_printer = True;
  XtManageChild(print -> print.new_printer_dialog);
}

static void 
post_add_pathname(Widget w, Widget pw,
		  XmPushButtonCallbackStruct *cb)
{
  XmdPrintWidget print = (XmdPrintWidget) pw;

  print -> print.adding_printer = False;
  XtManageChild(print -> print.new_printer_dialog);
}

static void
add_printer_cb(Widget w, XtPointer pw,
	       XmSelectionBoxCallbackStruct *cb)
{
  XmdPrintWidget print = (XmdPrintWidget) pw;
  int n;
  int i;
  Arg args[10];
  char *value;
  Widget button;
  
  /* Put the new value in the printer list and fix the 
     option menu.  Put the new value at the head of 
     the menu */
  XmStringGetLtoR(cb -> value, XmFONTLIST_DEFAULT_TAG, &value);

  /* Make sure widget array is big enough
     for all the items */
  i = print -> print.num_om_items;
  print -> print.num_om_items++;
  print -> print.om_items = 
    (WidgetList) XtRealloc((char*) print -> print.om_items,
			   sizeof(Widget) * (i + 1));

  /* Initialize new one */
  n = 0;
  XtSetArg(args[n], XmNpositionIndex, 0); n++; /* Insert at head */
  XtSetArg(args[n], XmNlabelString, cb -> value); n++;
  button = XmCreatePushButtonGadget((Widget) print -> print.destination_pd,
				    "button", args, n);
  XtManageChild(button);
  print -> print.om_items[i] = button;

  /* New printer */
  i = print -> print.num_printers;
  print -> print.num_printers++;
  print -> print.printers = 
    (char**) XtRealloc((char*) print -> print.printers,
		       sizeof(char*) * (i + 1));
  print -> print.is_printer = 
    (Boolean*) XtRealloc((char*) print -> print.is_printer,
			 sizeof(Boolean) * (i + 1));
  print -> print.printers[i] = value;
  print -> print.is_printer[i] = print -> print.adding_printer;

  XtVaSetValues(print -> print.destination_om,
		XmNmenuHistory, button, 
		NULL, NULL);
}

static void
cancel_printer_cb(Widget w, XtPointer pw,
		  XmSelectionBoxCallbackStruct *cb)
{
  XmdPrintWidget print = (XmdPrintWidget) pw;
  Widget history;

  if (print -> print.om_items && print -> print.num_om_items > 0)
    history = print -> print.om_items[0];
  else
    history = NULL;

  /* Just reset the menu history on the print option menu */
  XtVaSetValues(print -> print.destination_om,
		XmNmenuHistory, history,
		NULL, NULL);
}

/* 
 * External functions
 */

/******************************************************************************
 *
 *  XmdCreatePrint:
 *      Called by an application. 
 *
 *****************************************************************************/
Widget 
XmdCreatePrint (
        Widget parent,
        char *name,
        ArgList arglist, 
        Cardinal argcount
              )
{
  /* This is a convenience function to instantiate an XmdPrint widget. */
  return (XtCreateWidget (name, xmdPrintWidgetClass, parent, 
			  arglist, argcount));
}

/******************************************************************************
 *
 *  XmdCreatePrintDialog
 *      Called by an application to create an XmdPrint managed by a
 *      DialogShell. 
 *
 *****************************************************************************/
Widget 
XmdCreatePrintDialog (
        Widget parent,
        char *name,
        ArgList arglist, 
        Cardinal argcount
              )
{
  return(XmeCreateClassDialog(xmdPrintWidgetClass, 
			      parent, name, arglist, argcount));
}

void
XmdPrintDocument(char* pathname,
		 XmdPrintCallbackStruct* cb)
{
  char command[1024];

  command[0] = 0;

  /* These commands may need modification on different systems.  These
     are the system V and berkeley printer commands */
  if (cb -> to_printer) {
#ifdef SYSV
    sprintf(command, "lp -d%s -n%d %s",
	    cb -> printer, 
	    cb -> copies,
	    pathname);
#else /* Berk */
    sprintf(command, "lpr -P%s -#%d %s",
	    cb -> printer, 
	    cb -> copies,
	    pathname);
#endif /* SYSV */
  } else {
    sprintf(command, "cp %s %s", pathname, cb -> printer);
  }

  system(command);

}
