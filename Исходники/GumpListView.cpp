void CGumpListView::OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	
	COleDataSource srcItem;
	CString sType = _T("");
	HGLOBAL hTextData = 0;	

	CSharedFile clipb (GMEM_MOVEABLE|GMEM_DDESHARE|GMEM_ZEROINIT);

	dynDropSource.nControlType = DYN_PICTURE;

	CString strText;
	strText.Format("%d",0);
	sType = strText;

	clipb.Write(sType, sType.GetLength()*sizeof(TCHAR));
	hTextData = clipb.Detach();

	srcItem.CacheGlobalData(m_nIDClipFormat, hTextData);
	srcItem.DoDragDrop(DROPEFFECT_COPY,NULL,&dynDropSource);
}