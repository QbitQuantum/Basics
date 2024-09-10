static int winListMapMethod(Ihandle* ih)
{
  char* class_name;
  DWORD dwStyle = WS_CHILD|WS_CLIPSIBLINGS,
      dwExStyle = WS_EX_CLIENTEDGE;

  if (!ih->parent)
    return IUP_ERROR;

  if (ih->data->is_dropdown || ih->data->has_editbox)
  {
    class_name = "COMBOBOX";

    dwStyle |= CBS_NOINTEGRALHEIGHT;

    if (ih->data->is_dropdown)
      dwStyle |= WS_VSCROLL|WS_HSCROLL;
    else if (ih->data->sb)
    {
      dwStyle |= WS_VSCROLL|WS_HSCROLL;

      if (!iupAttribGetBoolean(ih, "AUTOHIDE"))
        dwStyle |= CBS_DISABLENOSCROLL;
    }

    if (ih->data->has_editbox)
    {
      dwStyle |= CBS_AUTOHSCROLL;

      if (ih->data->is_dropdown)
        dwStyle |= CBS_DROPDOWN;  /* hidden-list+edit */
      else
        dwStyle |= CBS_SIMPLE;  /* visible-list+edit */
    }
    else
      dwStyle |= CBS_DROPDOWNLIST;  /* hidden-list */

    if (iupAttribGetBoolean(ih, "SORT"))
      dwStyle |= CBS_SORT;
  }
  else
  {
    class_name = "LISTBOX";

    dwStyle |= LBS_NOINTEGRALHEIGHT|LBS_NOTIFY;

    if (ih->data->is_multiple)
      dwStyle |= LBS_EXTENDEDSEL;

    if (ih->data->sb)
    {
      dwStyle |= WS_VSCROLL|WS_HSCROLL;

      if (!iupAttribGetBoolean(ih, "AUTOHIDE"))
        dwStyle |= LBS_DISABLENOSCROLL;
    }

    if (iupAttribGetBoolean(ih, "SORT"))
      dwStyle |= LBS_SORT;
  }

  if (iupAttribGetBoolean(ih, "CANFOCUS"))
    dwStyle |= WS_TABSTOP;

  if (!iupwinCreateWindowEx(ih, class_name, dwExStyle, dwStyle))
    return IUP_ERROR;

  /* Custom Procedure */
  IupSetCallback(ih, "_IUPWIN_CTRLPROC_CB", (Icallback)winListProc);

  /* Process background color */
  IupSetCallback(ih, "_IUPWIN_CTLCOLOR_CB", (Icallback)winListCtlColor);

  /* Process WM_COMMAND */
  IupSetCallback(ih, "_IUPWIN_COMMAND_CB", (Icallback)winListWmCommand);

  if (ih->data->is_dropdown || ih->data->has_editbox)
  {
    COMBOBOXINFO boxinfo;

    ZeroMemory(&boxinfo, sizeof(COMBOBOXINFO));
    boxinfo.cbSize = sizeof(COMBOBOXINFO);

    GetComboBoxInfo(ih->handle, &boxinfo);

    iupwinHandleAdd(ih, boxinfo.hwndList);
    iupAttribSetStr(ih, "_IUPWIN_LISTBOX", (char*)boxinfo.hwndList);

    /* subclass the list box. */
    IupSetCallback(ih, "_IUPWIN_LISTOLDPROC_CB", (Icallback)GetWindowLongPtr(boxinfo.hwndList, GWLP_WNDPROC));
    SetWindowLongPtr(boxinfo.hwndList, GWLP_WNDPROC, (LONG_PTR)winListComboListWinProc);

    if (ih->data->has_editbox)
    {
      iupwinHandleAdd(ih, boxinfo.hwndItem);
      iupAttribSetStr(ih, "_IUPWIN_EDITBOX", (char*)boxinfo.hwndItem);

      /* subclass the edit box. */
      IupSetCallback(ih, "_IUPWIN_EDITOLDPROC_CB", (Icallback)GetWindowLongPtr(boxinfo.hwndItem, GWLP_WNDPROC));
      SetWindowLongPtr(boxinfo.hwndItem, GWLP_WNDPROC, (LONG_PTR)winListEditWinProc);

      /* set defaults */
      SendMessage(ih->handle, CB_LIMITTEXT, 0, 0L);
    }
  }

  /* configure for DRAG&DROP */
  if (IupGetCallback(ih, "DROPFILES_CB"))
    iupAttribSetStr(ih, "DRAGDROP", "YES");

  IupSetCallback(ih, "_IUP_XY2POS_CB", (Icallback)winListConvertXYToPos);

  iupListSetInitialItems(ih);

  return IUP_NOERROR;
}