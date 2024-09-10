BOOL CMarkersPropertyPage::OnInitDialog() 
{
	CDialog     *pConfigDlg;
	CFileMarker *pMarker;
 int          Index;

	CResizablePage::OnInitDialog();
	
	// preset resize layout
	AddAnchor(IDC_SELECTION_CHECKLIST, TOP_LEFT,BOTTOM_LEFT);
	AddAnchor(IDC_SELECTION_FRAME,  TOP_LEFT,BOTTOM_LEFT);
	AddAnchor(IDC_SELECTION_INFO_FRAME,  TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_SELECTION_DESCRIPTION,  TOP_LEFT,TOP_RIGHT);
	AddAnchor(IDC_SELECTION_CONFIG_FRAME, TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_PROPERTYSHEET,  TOP_LEFT, BOTTOM_RIGHT);
	AddAnchor(IDC_SELECTIONS_MAKE,  BOTTOM_LEFT);
 //

 // subclass checklistbox
 m_SelectionCheckList.SubclassDlgItem(IDC_SELECTION_CHECKLIST,this);
 //


	for (Index = 0; Index < g_DupeFileFind.GetFileSelectionArray()->GetSize(); Index++)
	{
		pMarker = g_DupeFileFind.GetFileSelectionArray()->GetAt(Index);
		pConfigDlg = pMarker->GetForm();
				
	 if (pConfigDlg)
		{
 		CRect rcSheet;
			pConfigDlg->Create(pMarker->GetFormID(), this);
			GetDlgItem( IDC_PROPERTYSHEET )->GetWindowRect( &rcSheet );
			ScreenToClient( &rcSheet );
			pConfigDlg->SetWindowPos( NULL, rcSheet.left-7, rcSheet.top-7, 0, 0, 	SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE );
			pConfigDlg->UpdateData();
 	}
	 m_SelectionCheckList.AddString ( pMarker->GetName() );
  m_SelectionCheckList.SetItemData ( Index, (DWORD)pMarker );
	}

	if ( m_SelectionCheckList.GetCount() != 0 )
	{
		m_SelectionCheckList.SetCurSel(0);
  UpdateForm();	
	}


// CANNOT LOG HERE

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}