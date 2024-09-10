DBOOL PathMgr::GetPath(char* pBasePathName, PathList* pReturnList)
{
	CServerDE* pServerDE = BaseClass::GetServerDE();
	if (!pServerDE) return DFALSE;

	if (!pBasePathName || !pReturnList || pBasePathName[0] == '\0') return DFALSE;

	// Make sure we've got some keys to look through...

	if (m_pathList.IsEmpty()) return DFALSE;


	// Make sure we start with a clean slate...

	if (!pReturnList->IsEmpty()) pReturnList->RemoveAll();


	int nNumItems = m_pathList.GetNumItems();
	int nNameLen  = _mbstrlen(pBasePathName);
	if (nNameLen < 1) return DFALSE;

	DList sortList;
	dl_InitList(&sortList);
	sortList.m_Head.m_pData = DNULL;

	for (int i=0; i < nNumItems; i++)
	{
		PathListData* pCurData = m_pathList[i];
		if (!pCurData || !pCurData->m_hstrName) return DFALSE;

		char* pName = pServerDE->GetStringData(pCurData->m_hstrName);
		if (!pName) return DFALSE;

		if (strnicmp(pName, pBasePathName, nNameLen) == 0)
		{
			int nTestLen = _mbstrlen(pName);
			
			// Make sure the name is of the form BaseXXX where XXX is
			// a number...

			if (nTestLen > nNameLen)
			{
				if (isdigit(pName[nNameLen]))
				{
					AddToSortedList(&sortList, pCurData);
				}
			}
		}
	}

	if (sortList.m_nElements < 1) return DFALSE;


	// Copy the sorted list to the return list...

	DLink* pLink = sortList.m_Head.m_pNext;

	while (sortList.m_nElements > 0)
	{
		PathListData* pData = (PathListData*)pLink->m_pData;
		if (pData)
		{
			pReturnList->Add(pData);
		}

		dl_RemoveAt(&sortList, pLink);
		delete pLink;

		pLink = sortList.m_Head.m_pNext;
	}


	return DTRUE;
}