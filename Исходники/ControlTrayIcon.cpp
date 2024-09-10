void ControlTrayIcon::onRightButtonUp()
{
  HMENU hRoot = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_TRAYMENU));
  HMENU hMenu = GetSubMenu(hRoot, 0);

  SetMenuDefaultItem(hMenu, ID_CONFIGURATION, FALSE);

  if (m_appControl->m_slaveModeEnabled) {
    RemoveMenu(hMenu, ID_CLOSE_CONTROL_INTERFACE, MF_BYCOMMAND);
  }

  POINT pos;

  if (!GetCursorPos(&pos)) {
    pos.x = pos.y = 0;
  }

  SetForegroundWindow(getWindow());

  int action = TrackPopupMenu(hMenu,
                              TPM_NONOTIFY | TPM_RETURNCMD | TPM_RIGHTBUTTON,
                              pos.x, pos.y, 0, getWindow(), NULL);

  switch (action) {
  case ID_KILLCLIENTS:
    onDisconnectAllClientsMenuItemClick();
    break;
  case ID_SHUTDOWN_SERVICE:
    onShutdownServerMenuItemClick();
    break;
  case ID_CONFIGURATION:
    onConfigurationMenuItemClick();
    break;
  case ID_OUTGOING_CONN:
    onOutgoingConnectionMenuItemClick();
    break;
  case IDM_ATTACH_TO_DISPATCHER:
    onAttachToDispatcher();
    break;
  case ID_ABOUT_TIGHTVNC_MENUITEM:
    onAboutMenuItemClick();
    break;
  case ID_CLOSE_CONTROL_INTERFACE:
    onCloseControlInterfaceMenuItemClick();
    break;
  }
}