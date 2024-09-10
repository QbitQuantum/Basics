void CDialogClasses::OnOK()
{
	unsigned numselected = m_ClassView.GetSelectedCount();
	POSITION pos = m_ClassView.GetFirstSelectedItemPosition();
	while (pos)
	{
		int nItem = m_ClassView.GetNextSelectedItem(pos);

		// FUUUUCK pushign this out last second shutup
		CString szBuffer = m_ClassView.GetItemText(nItem, 0);
	
		printf("nitem %d\n", nItem);

		nItem = FindClassByName(szBuffer.GetBuffer());

		//printf( "szBuffer %s new %d\n", szBuffer.GetBuffer( ), nItem );

		CMainFrame*  pFrame = static_cast<CMainFrame*>(AfxGetApp( )->m_pMainWnd);
		CChildFrame* pChild = (CChildFrame*)pFrame->CreateNewChild(RUNTIME_CLASS(CChildFrame), IDR_ReClass2015TYPE, theApp.m_hMDIMenu, theApp.m_hMDIAccel);
		pChild->m_wndView.m_pClass = theApp.Classes[nItem];

		// This will get overwritten for each class that is opened
		pChild->SetTitle(theApp.Classes[nItem]->Name);
		pChild->SetWindowTextA(theApp.Classes[nItem]->Name);
		pFrame->UpdateFrameTitleForDocument(theApp.Classes[nItem]->Name);
	}

	CDialogEx::OnOK();
}