STDAPI_(void) OleUIMetafilePictIconFree(HGLOBAL hMetaPict)
{
	LPMETAFILEPICT pMF;

	if (NULL == hMetaPict)
		return;

	pMF = (LPMETAFILEPICT)GlobalLock(hMetaPict);

	if (NULL != pMF)
	{
		if (NULL != pMF->hMF)
			DeleteMetaFile(pMF->hMF);
	}

	GlobalUnlock(hMetaPict);
	GlobalFree(hMetaPict);
	return;
}