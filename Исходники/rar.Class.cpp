int __stdcall RarArchive::pGetArchiveItem (
		ArchiveItemInfo *pItem
		)
{
	RARHeaderDataEx *fileHeader = (RARHeaderDataEx *)malloc (sizeof(RARHeaderDataEx));

	int nResult = m_pModule->m_pfnReadHeaderEx (m_hArchive, fileHeader);

	if ( !nResult )
	{
		memset (pItem, 0, sizeof (PluginPanelItem));

		strcpy ((char*)pItem->pi.FindData.cFileName, fileHeader->FileName);

		pItem->pi.FindData.dwFileAttributes = (BYTE)(fileHeader->FileAttr >> 16); //бред!

		if ( (fileHeader->Flags & 0x04) == 0x04 )
			pItem->dwFlags |= AIF_CRYPTED;

		FILETIME lFileTime;

		DosDateTimeToFileTime (HIWORD(fileHeader->FileTime), LOWORD(fileHeader->FileTime), &lFileTime);
		LocalFileTimeToFileTime (&lFileTime, &pItem->pi.FindData.ftLastWriteTime);

		pItem->pi.FindData.nFileSizeHigh = fileHeader->UnpSizeHigh;
		pItem->pi.FindData.nFileSizeLow = fileHeader->UnpSize;

		m_pModule->m_pfnProcessFile (m_hArchive, RAR_SKIP, NULL, NULL);

		free(fileHeader);

		return E_SUCCESS;
	}