wyInt32
EditorBase::OnContextMenuHelper(LPARAM lParam)
{
	wyBool	    nmenuselect;
	LONG	    lstyle=0;
	HMENU	    hmenu, htrackmenu;
	POINT	    pnt;
	wyInt32		pos;
    RECT        rect;
    MDIWindow*  wnd = GetActiveWin();

	VERIFY(hmenu = GetMenu(pGlobals->m_pcmainwin->m_hwndmain));

	//lStyle = GetWindowLongPtr ( m_hwndparent, GWL_STYLE );
	lstyle = GetWindowLongPtr(GetParent(m_hwndparent), GWL_STYLE);

    if ((lstyle & WS_MAXIMIZE) && wyTheme::IsSysmenuEnabled(GetParent(m_hwndparent)))
		VERIFY(htrackmenu =	GetSubMenu(hmenu, 2));
	else
		VERIFY(htrackmenu =	GetSubMenu(hmenu, 1));

	//If we are pressing the context button,then lParam is -1.
	if(lParam == -1)
	{		
		//for getting the current cursor pos.
		pos = SendMessage(m_hwnd, SCI_GETCURRENTPOS, 0, 0);
		pnt.x = SendMessage(m_hwnd, SCI_POINTXFROMPOSITION, 0, pos) ; 
		pnt.y = SendMessage(m_hwnd, SCI_POINTYFROMPOSITION, 0, pos); 
		VERIFY(ClientToScreen(m_hwnd, &pnt));
	}
	else
	{
		pnt.x = GET_X_LPARAM(lParam); 
		pnt.y = GET_Y_LPARAM(lParam); 
	}

    GetClientRect(m_hwnd, &rect);
    MapWindowPoints(m_hwnd, NULL, (LPPOINT)&rect, 2);

    if(!PtInRect(&rect, pnt))
    {
        return -1;
    }

	//VERIFY(ClientToScreen(m_hwnd, &pnt));
    SetFocus(m_hwnd);

	// Now change the menu item.
	ChangeEditMenuItem(htrackmenu);

    pGlobals->m_pcmainwin->m_connection->HandleTagsMenu((HMENU)hmenu);

    if(wnd)
    {
        //FrameWindow::RecursiveMenuEnable(htrackmenu, wyFalse, MF_ENABLED);

        if(wnd->m_executing == wyTrue || wnd->m_pingexecuting == wyTrue)
        {
            FrameWindow::RecursiveMenuEnable(htrackmenu, wyFalse, MF_DISABLED);
        }

        wyTheme::SetMenuItemOwnerDraw(htrackmenu);
	    nmenuselect = (wyBool)TrackPopupMenu(htrackmenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON, pnt.x, pnt.y, 0, pGlobals->m_pcmainwin->m_hwndmain, NULL);
    }
    return 1;
}