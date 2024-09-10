void COXMulticlipboardDlg::RemovePocket(int nPocket)
{
	//the function remove pocket from 
	//the collection, actually destroying 
	//the window and deleting COXClipPocket object 
	
	if (nPocket>m_pPockets.GetUpperBound())
		return;
	
	COXClipPocket* pPocket=(COXClipPocket*) m_pPockets.GetAt(nPocket);

	if (m_pPockets.GetUpperBound())
	{
		pPocket->DestroyWindow();
		delete pPocket;
		m_pPockets.RemoveAt(nPocket);
		if (m_nCurrentPocket>=nPocket)
			m_nCurrentPocket--;
	}
	else
		pPocket->SetData(NULL,NULL);

	//one pocket less - we have to adjust ths size
	AdjustSize(PtrToUint(m_pPockets.GetUpperBound()));

}