int CCOMStringW::Collate(const WCHAR*  lpsz) const
{
	ATLASSERT(lpsz != NULL);
	ATLASSERT(::IsBadStringPtrW(lpsz, -1) == 0);
	return wcscoll(m_pszString, lpsz);	
}