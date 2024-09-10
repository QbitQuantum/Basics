int COXCustomizeManager::GetAllPageCount() const 
{
	int nPageCount=0;
	int nGroupCount= PtrToInt(m_shb.GetGroupCount());
	for(int nIndex=0; nIndex<nGroupCount; nIndex++)
	{
		HSHBGROUP hGroup=m_shb.FindGroupByOrder(nIndex);
		ASSERT(hGroup!=NULL);
		nPageCount+=GetPageCount(hGroup);
	}
	return nPageCount;
}