STDMETHODIMP
CDeskBand::QueryContextMenu(HMENU hMenu,
                            UINT indexMenu,
                            UINT idCmdFirst,
                            UINT idCmdLast,
                            UINT uFlags)
{
  TRACE_ENTER("CDeskBand::QueryContextMenu");
  if ((!m_HasAppletMenu) || (CMF_DEFAULTONLY & uFlags) || !IsWindow( get_command_window() ))
    return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));

  int m = 0;
  HMENU popup = NULL;
  while (m < m_AppletMenu.num_items)
    {
      AppletMenuItemData *d = &m_AppletMenu.items[m];
      wchar_t textw[APPLET_MENU_TEXT_MAX_LENGTH*2];
      MultiByteToWideChar(CP_UTF8, 0, d->text, -1,
                          textw, sizeof(textw)/sizeof(textw[0]));
      wchar_t *abbrev = wcschr(textw, '_');
      UINT flags = MF_STRING | MF_BYPOSITION;
      if (d->flags & APPLET_MENU_FLAG_SELECTED)
        {
          flags |= MF_CHECKED;
        }
      if (abbrev != NULL)
        {
          *abbrev = '&';
        }
      if (d->flags & APPLET_MENU_FLAG_POPUP)
        {
          if (popup == NULL)
            {
              popup = CreatePopupMenu();
            }
          AppendMenuW(popup,
                      flags,
                      idCmdFirst + m,
                      textw);
        }
      else
        {
          if (popup != NULL)
            {
              InsertMenuW(hMenu,
                          indexMenu++,
                          MF_POPUP | flags,
                          (UINT) popup,
                          textw);
              popup = NULL;
            }
          else
            {
              InsertMenuW(hMenu,
                          indexMenu++,
                          flags,
                          idCmdFirst + m,
                          textw);
            }
        }
      m++;
    }

  TRACE_EXIT();
  return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(m_AppletMenu.num_items + 1));
}