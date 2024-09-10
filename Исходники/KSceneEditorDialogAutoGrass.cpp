void KSceneEditorDialogAutoGrass::OnLbnSelchangeListPattern()
{
	HRESULT hRetCode = E_FAIL;
	int nCount = 0;
	int nSelCount = 0;
	int* pSelPatterns = NULL;
	TCHAR strPatternPathName[MAX_PATH];
	KG_PROCESS_ERROR(m_lpSceneSceneEditor);
	KG_PROCESS_ERROR(m_lpOutDoorSpaceMgr);
	

	nSelCount = m_ListBoxPattern.GetSelCount();
	KG_PROCESS_ERROR(nSelCount > 0);

	pSelPatterns = new int[nSelCount];
	KG_PROCESS_ERROR(pSelPatterns);
	for(int n = 0;n< 8;n++ )
		m_pbyPatternIndex[n] = 255;

	nCount = 0;
	for (int i = 0; i < m_ListBoxPattern.GetCount(); i++)
	{
		int nSel = m_ListBoxPattern.GetSel(i);
		if ( nSel > 0)
		{
			CString strGrassPatternName;
			m_ListBoxPattern.GetText(i, strGrassPatternName);
			
			sprintf(strPatternPathName, "Data\\public\\GrassPattern\\%s.mesh",strGrassPatternName);
			
			_strlwr_s(strPatternPathName, sizeof(TCHAR) * MAX_PATH);
			int nPatternIndex = -1;
			
			hRetCode = m_lpOutDoorSpaceMgr->FindPattern(strPatternPathName,&nPatternIndex,MAP_GRASS);

			KGLOG_COM_PROCESS_ERROR(hRetCode);
			ASSERT(nPatternIndex != -1);
			pSelPatterns[nCount] = nPatternIndex;
			if(nCount < 8)
				m_pbyPatternIndex[nCount] = (BYTE)i;
			nCount++;
		}
	}
	m_lpSceneSceneEditor->UpdatePatternList(pSelPatterns, nSelCount);

Exit0:
	
	SAFE_DELETE_ARRAY(pSelPatterns);
	//OnBnClickedButtonAddgrass();
	return;
}