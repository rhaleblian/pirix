/* $TOG: Menus.c /main/7 1997/04/15 10:03:39 dbl $ */
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
#include <Xm/PushBG.h>
#include <Xm/CascadeBG.h>
#include <Xm/SeparatoG.h>
#include <Xm/RowColumn.h>
#include "Menus.h"

typedef struct _menu_info {
  char* label;
  char	mnemonic;
  char* accelerator;
  char* acc_text;
  Boolean managed;
  Boolean is_separator;
} menu_info;

static Widget CreateMenuButton(Widget, char*, char, char*, char*, 
			       WidgetClass wc);
static Widget CreatePulldown(char* name, char mnemonic, Widget, 
			     menu_info*, WidgetList, Cardinal);

menu_info file_pulldown[] = {
  /*label	mnem.	acc.		acc. text	mnged.	is_sep */
  {"New",	'N',	"Ctrl<Key>N",	"Ctrl+N",	True,	False},
  {"Open",	'O', 	"Ctrl<Key>O",	"Ctrl+O",	True,	False},
  {"Save",	'S',	"Ctrl<Key>S",	"Ctrl+S",	True,	False},
  {"Save As...",'A',	NULL,		NULL,		True,	False},
  {"Revert",	0,	NULL,		NULL,		False,	False},
  {"separator1", 0,	NULL,  		NULL,		True,	True},
  {"Copy To...",0,	NULL,		NULL,		False,	False},
  {"Drag",	0,	NULL,		NULL,		False,	False},
  {"Print...",	'P',	"Ctrl<Key>P",	"Ctrl+P",	True,	False},
  {"Print Setup", 'r',	NULL,		NULL,		False,  False},
  {"separator2", 0,	NULL,  		NULL,		True,	True},
  {"Close",	'C',	NULL,		NULL,		False,	False},
  {"Exit",	'x',	NULL,		NULL,		True,	False}
};

menu_info selected_pulldown[] = {
  /*label	mnem.	acc.		acc. text	mnged.	is_sep */
  {"Properties", 's',	"Ctrl<Key>I",	"Ctrl+I",	False,	False},
  {"New",	'N',	NULL,		NULL,		False,	False},
  {"Open",	'O',	NULL,		NULL,		True,	False},
  {"separator1", 0,	NULL,  		NULL,		True,	True},
  {"Copy To...", 0,	NULL,		NULL,		False,	False},
  {"Move To...", 0,	NULL,		NULL,		False,	False},
  {"separator2", 0,	NULL,  		NULL,		True,	True},
  {"Clear To Trash",
     		'e',	NULL,		NULL,		False,	False},
  {"Delete To Trash",
		'D',	"<Key>osfDelete", "Delete",	False,	False},
  {"Print...",	0,	NULL,		NULL,		False,	False},
  {"Exit",	'x',	NULL,		NULL,		True,	False}
};

/* Edit menu */

menu_info edit_pulldown[] = {
  {"Undo",	'U',	NULL,		NULL,		False,	False},
  {"Repeat",	'R',	NULL,		NULL,		False,	False},
  {"Drag",	0,	NULL,		NULL,		False,	False},
  {"Size",	0,	NULL,		NULL,		False,	False},
  {"Duplicate",	0,	NULL,		NULL,		False,	False},
  {"separator1", 0,	NULL,  		NULL,		False,	True},
  {"Cut",	't',	"Ctrl<Key>x",	"Ctrl+x",	True,	False},
  {"Copy",	'C',	"Ctrl<Key>c",	"Ctrl+c",	True,	False},
  {"Copy Link",	'k',	NULL,		NULL,		False,	False},
  {"Copy Special...",
     		0,	NULL,		NULL,		False,	False},
  {"Paste",	'P',	"Ctrl<Key>v",	"Ctrl+v",	True,	False},
  {"Paste Link",0,	NULL,		NULL,		False,	False},
  {"Paste Special...",
     		0,	NULL,		NULL,		False,	False},
  {"Insert...",	'I',	NULL,		NULL,		False,	False},
  {"separator2", 0,	NULL,  		NULL,		True,	True},
  {"Primary Copy", 0,	"Alt,Ctrl<Key>c", "Alt+Ctrl+c",	False,	False},
  {"Primary Move", 0,	"Alt,Ctrl<Key>x", "Alt+Ctrl+x",	False,	False},
  {"Primary Link", 0,	NULL,		NULL,		False,	False},
  {"separator3", 0,	NULL,  		NULL,		True,	True},
  {"Clear",	'e',	NULL,		NULL,		False,	False},
  {"Delete",	'D',	"<Key>osfDelete", "Delete",	True,	False},
  {"Select All",'S',	"Ctrl<Key>a",	"Ctrl+a",	False,	False},
  {"separator4", 0,	NULL,  		NULL,		False,	True},
  {"Unselect All",     
     		0,	"Ctrl<Key>\\",	"Ctrl+\\",	False,	False},
  {"Select Pasted",
     		0,	NULL,		NULL,		False,	False},
  {"Reselect",	0,	NULL,		NULL,		False,	False}
};

/* View menu */

menu_info view_pulldown[] = {
  {"Change View",'C',	NULL,		NULL,	False,	False},
  {"New",	'N',	NULL,		NULL,	False,	False},
  {"separator", 0,	NULL,  		NULL,	False,	True},
  {"Include...",'I',	NULL,		NULL,	False,	False},
  {"Sort...",	'S',	NULL,		NULL,	False,	False},
  {"Find...",	'F',	NULL,		NULL,	False,	False}
};

/* Help menu */

menu_info help_pulldown[] = {
  {"Overview",	'O',	NULL,		NULL,	True,	False},
  {"separator1", 0,	NULL,  		NULL,	True,	True},
  {"Index",	'I',	NULL,		NULL,	False,	False},
  {"Table Of Contents",
     		'C',	NULL,		NULL,	True,	False},
  {"Tasks",	'T',	NULL,		NULL,	False,	False},
  {"Reference",	'R',	NULL,		NULL,	False,	False},
  {"Tutorial",	'L',	NULL,		NULL,	False,	False},
  {"Keyboard",	'K',	NULL,		NULL,	False,	False},
  {"Mouse",	'M',	NULL,		NULL,	False,	False},
  {"separator2", 0,	NULL,  		NULL,	True,	True},
  {"On Item",	0,	NULL,		NULL,	False,	False},
  {"Using Help",'U',	NULL,		NULL,	False,	False},
  {"About App.",'A',	NULL,		NULL,	False,	False}
};

Widget
XmdCreateMenu(XmdMenuType type, Widget parent, 
	      WidgetList *array, Cardinal *size)
{
  Widget retval = NULL;

  if (type > POPUPS) {
    /* This is a popup menu */
  } else {
    /* This is a pulldown menu */
    switch(type) {
    case FILE_MENU:
      *array = (WidgetList) XtMalloc(sizeof(Widget) * XtNumber(file_pulldown));
      *size = XtNumber(file_pulldown);
      retval = CreatePulldown("File", 'F', 
			    parent, file_pulldown, *array, *size);
      break;
    case EDIT_MENU:
      *array = (WidgetList) XtMalloc(sizeof(Widget) * XtNumber(edit_pulldown));
      *size = XtNumber(edit_pulldown);
      retval = CreatePulldown("Edit", 'E',
			    parent, edit_pulldown, *array, *size);
      break;
    case SELECTED_MENU:
      *array = (WidgetList) XtMalloc(sizeof(Widget) * 
				     XtNumber(selected_pulldown));
      *size = XtNumber(selected_pulldown);
      retval = CreatePulldown("Selected", 'S',
			    parent, selected_pulldown, *array, *size);
      break;
    case VIEW_MENU:
      *array = (WidgetList) XtMalloc(sizeof(Widget) * XtNumber(view_pulldown));
      *size = XtNumber(view_pulldown);
      retval = CreatePulldown("View", 'V',
			    parent, view_pulldown, *array, *size);
      break;
    case HELP_MENU:
      *array = (WidgetList) XtMalloc(sizeof(Widget) * XtNumber(help_pulldown));
      *size = XtNumber(help_pulldown);
      retval = CreatePulldown("Help", 'H',
			    parent, help_pulldown, *array, *size);
      break;
    default:
	/* internal error */
	break;
    }
  }

  return retval;
}

static Widget
CreateMenuButton(Widget menu, char* label, char mnemonic,
		 char* acc, char* acc_text, WidgetClass wc)
{
  Widget tmp;
  Arg args[10];
  int n;
  XmString tmp1, tmp2;

  tmp1 = NULL;
  tmp2 = NULL;

  n = 0;

  if (label != NULL) {
    tmp1 = XmStringCreateLocalized(label);
    XtSetArg(args[n], XmNlabelString, tmp1); n++;
  }
  if (mnemonic != 0) {
    XtSetArg(args[n], XmNmnemonic, mnemonic); n++;
  }
  if (acc != NULL) {
    XtSetArg(args[n], XmNaccelerator, acc); n++;
    if (acc_text != NULL) {
      tmp2 = XmStringCreateLocalized(acc_text);
      XtSetArg(args[n], XmNacceleratorText, tmp2); n++;
    }      
  }

  tmp = XtCreateWidget(label, wc, menu, args, n);

  if (tmp1) XmStringFree(tmp1);
  if (tmp2) XmStringFree(tmp2);

  return(tmp);
}

static Widget
CreatePulldown(char* name, char mnemonic,
	       Widget parent, menu_info *info, 
	       WidgetList array, Cardinal size)
{
  int i;
  Widget cascade_button, pulldown;
  Arg args[10];
  char buffer[128];

  sprintf(buffer,"%s_pulldown", name);
  pulldown = XmCreatePulldownMenu(parent, buffer, NULL, 0);

  i = 0;
  if (mnemonic != 0) {
    XtSetArg(args[i], XmNmnemonic, mnemonic); 
    i++;
  }
  XtSetArg(args[i], XmNsubMenuId, pulldown); i++;
  cascade_button = XmCreateCascadeButtonGadget(parent, name, args, i);
  XtManageChild(cascade_button);

  if (strcmp(name, "Help") == 0)
    XtVaSetValues(parent, XmNmenuHelpWidget, cascade_button, NULL, NULL);

  /* Create menu items,  special exception for the first item 
     in the View menu,  which is a cascadebutton*/
  for(i = 0; i < size; i++) {
    if (info[i].is_separator)
      array[i] = XmCreateSeparatorGadget(pulldown, info[i].label, NULL, 0);
    else
      array[i] = CreateMenuButton(pulldown, info[i].label, 
				  info[i].mnemonic,
				  info[i].accelerator,
				  info[i].acc_text,
				  (info != view_pulldown && i != 0) 
				  ? xmPushButtonGadgetClass : 
				    xmCascadeButtonGadgetClass
				  );

    if (info[i].managed)
      XtManageChild(array[i]);
  }

  return(pulldown);
}

