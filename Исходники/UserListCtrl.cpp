void CUserListCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	//		make sure window is active
	//
	GetParentFrame()->ActivateFrame();


	///////////////////////////////
	// See ContextMenuRules.txt for order of menu commands!

	//		create an empty context menu
	//
	CP4Menu popMenu;
    popMenu.LoadMenu(IDR_USER);

	int	index;
    SetIndexAndPoint( index, point );

	if( index != -1 )
	{
		// Can only edit or delete my user
		if ( GetSelectedItemText( ) == GET_P4REGPTR( )->GetP4User( ) )
		{
            // can't switch if already there
            popMenu.GetSubMenu(0)->DeleteMenu(ID_USER_SWITCHTOUSER,MF_BYCOMMAND);
        }
        else
        {
            // can't edit, delete, set password or set as default if not current
            popMenu.GetSubMenu(0)->DeleteMenu(ID_USER_EDITMY,MF_BYCOMMAND);
            popMenu.GetSubMenu(0)->DeleteMenu(ID_USER_DELETE,MF_BYCOMMAND);
            popMenu.GetSubMenu(0)->DeleteMenu(ID_USER_PASSWORD,MF_BYCOMMAND);
            popMenu.GetSubMenu(0)->DeleteMenu(ID_SETDEFUSER,MF_BYCOMMAND);
        }
	}
    else
    {
        // can't do much if no user selected
        popMenu.GetSubMenu(0)->DeleteMenu(ID_USER_EDITMY,MF_BYCOMMAND);
        popMenu.GetSubMenu(0)->DeleteMenu(ID_USER_DESCRIBE,MF_BYCOMMAND);
        popMenu.GetSubMenu(0)->DeleteMenu(ID_USER_DELETE,MF_BYCOMMAND);
        popMenu.GetSubMenu(0)->DeleteMenu(ID_USER_SWITCHTOUSER,MF_BYCOMMAND);
        popMenu.GetSubMenu(0)->DeleteMenu(ID_USER_PASSWORD,MF_BYCOMMAND);
        popMenu.GetSubMenu(0)->DeleteMenu(ID_SETDEFUSER,MF_BYCOMMAND);
        // clobber extra separator
        popMenu.GetSubMenu(0)->DeleteMenu(1,MF_BYPOSITION);

    }

	MainFrame()->AddToolsToContextMenu((CP4Menu *)(popMenu.GetSubMenu(0)));

	popMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,	point.x, point.y, AfxGetMainWnd());
}