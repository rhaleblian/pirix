/* $XConsortium: onHelp.c /main/4 1995/07/15 20:44:13 drk $ */
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
#include <Xm/Xm.h>
#include "Help.h"

void quitCB( Widget widget, char *tag, XmAnyCallbackStruct *callback_data )
{
  exit(0);
}

/*
 *  Main program
 */
int main(int argc, String argv[])
{
  Arg	args[10];
  XtAppContext app_context;
  int n;
  Widget toplevel, help;
  Cardinal size;
  XmRendition rend[10];
  XmRenderTable rt;
  int i;
  XmTab tabs[5];
  XmTabList tablist;
  Widget dismiss;

  toplevel = XtVaAppInitialize(&app_context, "HelpOnHelp", NULL, 0, 
			       &argc, argv, NULL, 0);
  n = 0;
  XtSetArg(args[n], XmdNhelpFile, "helpOn"); n++;
  help = XmdCreateHelp(toplevel, "help", args, n);
  dismiss = XtNameToWidget(help, "*Dismiss");
  XtAddCallback(dismiss, XmNactivateCallback,
		(XtCallbackProc) quitCB, NULL);
  /* Get the rendertable and add some new renditions */
  XtVaGetValues(help, XmNrenderTable, &rt, NULL, NULL);
  /* Make the tabs for the tables */
  n = 0;
  tabs[n] = XmTabCreate(2.0, XmINCHES, XmABSOLUTE,
			XmALIGNMENT_BEGINNING, NULL); n++;
  tabs[n] = XmTabCreate(4.0, XmINCHES, XmABSOLUTE,
			XmALIGNMENT_BEGINNING, NULL); n++;
  tablist = XmTabListInsertTabs(NULL, tabs, n, 0);
  for(i = 0; i < n; i++) XmTabFree(tabs[i]);

  /* Add extra renditions needed for the help file */
  n = 0; i = 0;
  XtSetArg(args[n], XmNtabList, tablist); n++;
  rend[i] = XmRenditionCreate(help, "table", args, n); i++;
  n = 0;
  XtSetArg(args[n], XmNfontName, "*courier-medium-r-*-12-*"); n++;
  XtSetArg(args[n], XmNfontType, XmFONT_IS_FONT); n++;
  rend[i] = XmRenditionCreate(help, "program", args, n); i++; 
  n = 0;
  XtSetArg(args[n], XmNunderlineType, XmSINGLE_LINE); n++;
  rend[i] = XmRenditionCreate(help, "underline", args, n); i++; 
  /* Make a copy so that setvalues will work correctly */
  rt = XmRenderTableCopy(rt, NULL, 0);
  rt = XmRenderTableAddRenditions(rt, rend, i, XmMERGE_NEW);
  for(n = 0; n < i; n++) XmRenditionFree(rend[n]);

  XtVaSetValues(help, XmNrenderTable, rt, NULL, NULL);
  XmRenderTableFree(rt);

  XtManageChild(help);

  XtRealizeWidget(toplevel);

  XtAppMainLoop(app_context);

  return 0;    /* make compiler happy */
}
