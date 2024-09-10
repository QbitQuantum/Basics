/*
 * AdminValueDialogProc:  Dialog procedure for editing a property's value.
 *   lParam of INITDIALOG message is index of property in object list box.
 */
BOOL CALLBACK AdminValueDialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
   static int index;
   int type, i;
   char *value, line[MAX_PROPERTYLEN], *str, property[MAX_PROPERTYLEN];
   static HWND hEdit;

   switch (message)
   {
   case WM_INITDIALOG:
      index = lParam;
      hEdit = GetDlgItem(hDlg, IDC_EDITVALUE);
      Edit_LimitText(hEdit, MAX_PROPERTYLEN - 1);

      ListBox_GetText(hObjectList, index, line);

      value = AdminPropertyValue(line, &type);
      if (value != NULL)
      {
	 // Initialize dialog with current value
	 for (i = 0; type_table[i].word != NULL; i++)
	    if (type == type_table[i].type)
	       CheckDlgButton(hDlg, type_table[i].control, 1);

	 Edit_SetText(hEdit, value);
	 Edit_SetSel(hEdit, 0, -1);

	 strcpy(property, AdminNthToken(line, 1));
	 str = strchr(property, ' ');
	 if (str != NULL)
	    *str = 0;
	 SetDlgItemText(hDlg, IDC_PROPERTY, property);
      }

      sprintf(line, "%d", current_obj);
      SetDlgItemText(hDlg, IDC_OBJECTNUM, line);

      CenterWindow(hDlg, GetParent(hDlg));
      SetWindowFont(hEdit, GetFont(FONT_INPUT), TRUE);
      SetFocus(hEdit);
      return FALSE;

   case WM_COMMAND:
      switch (GET_WM_COMMAND_ID(wParam, lParam))
      {
      case IDOK:
	 // Get type and value
	 str = NULL;
	 for (i = 0; type_table[i].word != NULL; i++)
	    if (IsDlgButtonChecked(hDlg, type_table[i].control))
	    {
	       str = type_table[i].word;
	       break;
	    }
	 if (str != NULL)
	 {
	    Edit_GetText(hEdit, line, MAX_PROPERTYLEN);
	    GetDlgItemText(hDlg, IDC_PROPERTY, property, MAX_PROPERTYLEN);
	    
	    // Special case for NIL:  value must be zero
	    if (type_table[i].type == TAG_NIL)
	       strcpy(line, "0");
	    
	    sprintf(command, "set object %d %s %s %s", current_obj, property, str, line);
	    
	    SendMessage(hAdminDlg, BK_SENDCMD, 0, (LPARAM) command);
	    
	    // Change value in object list box
	    sprintf(command, "%s = %s %s", property, str, line);
	    WindowBeginUpdate(hObjectList);
	    ListBox_DeleteString(hObjectList, index);
	    ListBox_InsertString(hObjectList, index, command);
	    WindowEndUpdate(hObjectList);
	 }
	    
	 EndDialog(hDlg, IDOK);
	 return TRUE;

      case IDCANCEL:
	 EndDialog(hDlg, IDCANCEL);
	 return TRUE;
      }
      break;
   }

   return FALSE;
}