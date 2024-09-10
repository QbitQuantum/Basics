LRESULT CXTPTrayIcon::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	// Return quickly if its not for this tray icon
	if (wParam != m_niData.uID)
	{
		return 0L;
	}

	if (m_hWndNotify == NULL)
	{
		return 0L;
	}

	// Check to see if our notification window has already handled this
	// message, if so then return success.
	if (::SendMessage(m_hWndNotify, TIN_XTP_TRAYICON, wParam, lParam))
	{
		return 1;
	}

	switch (LOWORD(lParam))
	{

	// Sent when the balloon is shown (balloons are queued).
	case NIN_BALLOONSHOW:
		break;

	// Sent when the balloon disappears-for example, when the
	// icon is deleted. This message is not sent if the balloon
	// is dismissed because of a timeout or a mouse click.
	case NIN_BALLOONHIDE:
		break;

	// Sent when the balloon is dismissed because of a timeout.
	case NIN_BALLOONTIMEOUT:
		break;

	// Sent when the balloon is dismissed because of a mouse click.
	case NIN_BALLOONUSERCLICK:
		break;

	// The version 5.0 Shell sends the associated application a NIN_SELECT message
	// if a user selects a notify icon with the mouse and activates it with the ENTER key

	case NIN_SELECT:
		// intentional fall thru...

	// The version 5.0 Shell sends the associated application a NIN_KEYSELECT message
	// if a user selects a notify icon with the keyboard and activates it with the space bar or ENTER key

	case NIN_KEYSELECT:
		// intentional fall thru...

	// The version 5.0 Shell sends the associated application a WM_CONTEXTMENU
	// If a user requests a notify icon's shortcut menu with the keyboard
	case WM_CONTEXTMENU:
		// intentional fall thru...

	case WM_RBUTTONUP:
		{
			CMenu menu;
			if (!menu.LoadMenu(m_niData.uID))
			{
				return 0;
			}

			CMenu* pSubMenu = menu.GetSubMenu(0);
			if (pSubMenu == NULL)
			{
				return 0;
			}

			// Make chosen menu item the default (bold font)
			::SetMenuDefaultItem(pSubMenu->m_hMenu,
				m_uDefMenuItemID, m_bDefMenuItemByPos);

			// Display the menu at the current mouse location. There's a "bug"
			// (Microsoft calls it a feature) in Windows 95 that requires calling
			// SetForegroundWindow. To find out more, search for Q135788 in MSDN.
			//
			CPoint pos;
			GetCursorPos(&pos);
			::SetForegroundWindow(m_hWndNotify);

			::TrackPopupMenu(pSubMenu->m_hMenu, 0, pos.x, pos.y,
				0, m_hWndNotify, NULL);

			::PostMessage(m_hWndNotify, WM_NULL, 0, 0);

			menu.DestroyMenu();

			ShellNotify(NIM_SETFOCUS);
		}
		break;

	case WM_LBUTTONDBLCLK:
		{
			// double click received, the default action is to execute default menu item
			::SetForegroundWindow(m_hWndNotify);

			UINT uItem;
			if (m_bDefMenuItemByPos)
			{
				CMenu menu;
				if (!menu.LoadMenu(m_niData.uID))
				{
					return 0;
				}

				CMenu* pSubMenu = menu.GetSubMenu(0);
				if (pSubMenu == NULL)
				{
					return 0;
				}

				uItem = pSubMenu->GetMenuItemID(m_uDefMenuItemID);

				menu.DestroyMenu();
			}
			else
			{
				uItem = m_uDefMenuItemID;
			}

			::SendMessage(m_hWndNotify, WM_COMMAND, uItem, 0);
		}
	}

	return 1;
}