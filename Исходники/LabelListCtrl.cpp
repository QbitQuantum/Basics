void CLabelListCtrl::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	//		make sure window is active
	//
	GetParentFrame()->ActivateFrame();

	// If one of the label modeless dialogs is up, don't display a context menu
	// instead set the focus to the modeless dialog.
	if (m_AddReplaceDlg)
	{
		m_AddReplaceDlg->SetFocus();
		return;
	}
	if (m_DelSyncDlg)
	{
		m_DelSyncDlg->SetFocus();
		return;
	}

	///////////////////////////////
	// See ContextMenuRules.txt for order of menu commands!

	//		create an empty context menu
	//
	CP4Menu popMenu;
	popMenu.CreatePopupMenu();

	int	index;
    SetIndexAndPoint( index, point );

	// Can always create new label
	popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABEL_NEW );

	if(index != -1)
	{
		// Make sure item is selected
		SetItemState(index, LVIS_SELECTED|LVIS_FOCUSED, LVIS_DROPHILITED|LVIS_SELECTED|LVIS_FOCUSED );

		popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABEL_EDIT_SPEC );
		popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABEL_DESCRIBE );
		popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABEL_DELETE );
		popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABEL_TEMPLATE );
		popMenu.AppendMenu(MF_SEPARATOR);
		popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABEL_LISTFILES );
		popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABEL_SYNC );
		popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABEL_DELETEFILES );
		popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABEL_SYNC_CLIENT );
		popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABEL_ADDTOLABELVIEW );
		popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABEL_DIFF2, LoadStringResource(IDS_LABEL_DIFF2) );
	}	

	popMenu.AppendMenu( MF_SEPARATOR );
	if(m_LabelFilterView.GetCount() > 0)
		popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_LABELFILTER_CLEARVIEW, LoadStringResource( IDS_CLEARFILTER ) );
	popMenu.AppendMenu(MF_ENABLED | MF_STRING, ID_VIEW_UPDATE, LoadStringResource(IDS_REFRESH) );
	
	MainFrame()->AddToolsToContextMenu(&popMenu);

	popMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,	point.x, point.y, AfxGetMainWnd());
}