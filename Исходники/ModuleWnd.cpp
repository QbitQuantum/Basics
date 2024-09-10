void CModuleWnd::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMLISTVIEW * phdn = (NMLISTVIEW *) pNMHDR;
	
	if (m_pCurrentDocument != NULL)
	{
		COleDataSource* pData = PrepareDataSource();
		if (pData != NULL)
		{
			m_isDragBeginer = TRUE;
			DROPEFFECT dropEffect = pData->DoDragDrop(DROPEFFECT_COPY);
			delete pData;
			m_isDragBeginer = FALSE;
		}
	}
	
	*pResult = 0;
}