void CStatCounterArray::Insert (const CString &sStat, int iCount, const CString &sSection, const CString &sSort)

//	Insert
//
//	Adds the given stat. If the stat already exists (by name) the counts are added

	{
	if (iCount == 0)
		return;

	ASSERT(!sStat.IsBlank());
	ASSERT(!sSection.IsBlank());

	//	First look for the section

	TMap<CString, SEntry> *pSection = m_Array.Find(sSection);
	if (pSection == NULL)
		pSection = m_Array.Insert(sSection);

	//	Next look for the entry

	SEntry *pEntry = pSection->Find(sStat);
	if (pEntry == NULL)
		{
		pEntry = pSection->Insert(sStat);
		pEntry->iCount = iCount;
		pEntry->sSort = sSort;
		}
	else
		{
		if (iCount > pEntry->iCount)
			pEntry->sSort = sSort;

		pEntry->iCount += iCount;
		}
	}