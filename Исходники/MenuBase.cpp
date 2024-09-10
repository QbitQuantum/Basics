// Sorts a file list.  This was taken from the old menu code.
FileEntry* CMenuBase::SortFileList(FileEntry *pfe)
{

	FileEntry	*pfindex;
	FileEntry	*pfList[MAX_FILE_LIST];
	int nCount=0;


	// Build an array of FileEntries.
	pfindex = pfe;
	while (pfindex && nCount < MAX_FILE_LIST)
	{
		pfList[nCount++] = pfindex;
		pfindex = pfindex->m_pNext;
	}
	if (pfindex) // Free any remaining items
	{
		m_pClientDE->FreeFileList(pfindex);
	}

	for (int i = nCount / 2; i > 0; i = (i == 2) ? 1 : (int) (i / 2.2))
	{
		for (int j = i; j < nCount; j++)
		{
			FileEntry *pfTemp = pfList[j];
			
			for (int k = j; k >= i && _mbsicmp((const unsigned char*)pfTemp->m_pBaseFilename, (const unsigned char*)pfList[k - i]->m_pBaseFilename) < 0; k -= i)
			{
				pfList[k] = pfList[k - i];
			}

			pfList[k] = pfTemp;
		}
	}

	pfindex = pfList[0];
	for (i=1; i < nCount-1; i++)
	{
		pfindex->m_pNext = pfList[i];
		pfindex = pfindex->m_pNext;
	}
	pfindex->m_pNext = DNULL;

	return pfList[0];
}