void COXCustomizeShortkeysPage::OnInitDialog()
{
	// must call default implementation
	COXCustomizePage::OnInitDialog();

	// add here initialization code for your demo dialog. Treat it as a
	// normal CDialog::OnInitDialog function

	// separators
	COLORREF clr=::GetSysColor(COLOR_WINDOW);
	m_sepShortkeys.SetTextColor(clr);
	m_sepDescription.SetTextColor(clr);
	m_sepConflict.SetTextColor(clr);
	m_sepCommands.SetTextColor(clr);

	// populate tree
	GetVars();

	// populate table of accelerator contexts
	COXArrAccelTables* pAccelTables=m_shortkeysOrganizer.GetAccelTables();
	ASSERT(pAccelTables!=NULL);
	if(pAccelTables->GetSize()==0)
	{
		// there is no accelerator tables defined for this application
		// as aresult all controls on this dialog must be disabled
		CWnd* pWndChild=GetWindow(GW_CHILD);
		while(pWndChild!=NULL)
		{
			pWndChild->EnableWindow(FALSE);
			pWndChild=pWndChild->GetNextWindow();
		}
		m_bReadOnly=TRUE;
	}
	else
	{
		for(int nIndex=0; nIndex<pAccelTables->GetSize(); nIndex++)
		{
			CString sText=OXDEFAULTACCEL;
			if(pAccelTables->GetAt(nIndex).m_docTemplate!=NULL)
			{
				pAccelTables->GetAt(nIndex).m_docTemplate->
					GetDocString(sText,CDocTemplate::docName);
			}
			m_comboTable.AddString(sText);
		}
	}

	m_nAccelTableIndex=0;

	// layout
	//
	m_LayoutManager.TieChild(&m_treeCommands,OX_LMS_ANY,OX_LMT_SAME);
	m_LayoutManager.TieChild(&m_sepCommands,
		OX_LMS_LEFT|OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(&m_sepDescription,
		OX_LMS_LEFT|OX_LMS_RIGHT|OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_STATIC_DESCRIPTION,
		OX_LMS_LEFT|OX_LMS_RIGHT|OX_LMS_BOTTOM,OX_LMT_SAME);

	m_LayoutManager.TieChild(IDC_OX_SEPARATOR_SHORTKEYS,OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_STATIC_FOR,OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_COMBO_TABLE,OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_STATIC_CURRENT_KEYS,OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_LIST_SHORTKEYS,
		OX_LMS_RIGHT|OX_LMS_BOTTOM|OX_LMS_TOP,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_BUTTON_ASSIGN,OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_BUTTON_REMOVE,OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_BUTTON_REMOVE_ALL,OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_BUTTON_RESET_ALL,OX_LMS_RIGHT,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_STATIC_NEW_KEY,
		OX_LMS_RIGHT|OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_HOTKEY_SHORTKEY,
		OX_LMS_RIGHT|OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_SEPARATOR_CONFLICTS,
		OX_LMS_RIGHT|OX_LMS_BOTTOM,OX_LMT_SAME);
	m_LayoutManager.TieChild(IDC_OX_STATIC_ASSIGNED_TO,
		OX_LMS_RIGHT|OX_LMS_BOTTOM,OX_LMT_SAME);
	//
	///////////////////////////////////////

	UpdateData(FALSE);
	GetShortkeys();
	ShowVars();

	m_bInitialized=TRUE;
}