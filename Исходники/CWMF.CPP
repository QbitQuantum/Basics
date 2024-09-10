BOOL CWindowsMetaFile::Play(CDC* pDC, BOOL fMask /*=FALSE*/, LPARAM lParam /*=0*/)
{
	BOOL fSuccess = FALSE;
	
	ASSERT(pDC != NULL);
	
	if (GetMetaFile())
	{
		EnumData FAR* pData = new EnumData;
		pData->pObject = this;
		pData->pDC = pDC;
		pData->fMask = fMask;
		pData->lParam = lParam;
		
		fSuccess = EnumMetaFile(pDC->GetSafeHdc(), m_hMetaFile, EnumMetaFileDispatch, (LPARAM)pData);
		
		delete pData;
	}
	
	return fSuccess;
}