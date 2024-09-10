void CExplorerTestView::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	int				nItem = -1;
	CObList			fileList;
	LIST_VIEW*		pListView;
	CListCtrl&		listCtrl = GetListCtrl();
	CSharedFile		sharedFile;
	COleDataSource*	dataSource = new COleDataSource;

	while((nItem = listCtrl.GetNextItem(nItem, LVNI_SELECTED)) != -1)
	{
		pListView = (LIST_VIEW*)listCtrl.GetItemData(nItem);
		fileList.AddTail((CObject*)pListView);
	}

	CArchive	ar(&sharedFile, CArchive::store);
	
	CExplorerTestDoc*	pDoc = (CExplorerTestDoc*)GetDocument();
	pDoc->SetCopyFileList(&fileList);
	pDoc->SerializeCopyFiles(ar);

	ar.Close();

	dataSource->CacheGlobalData(m_cbFormat, sharedFile.Detach());
	dataSource->DoDragDrop();

	delete dataSource;

	*pResult = 0;
}