bool CValueMap::Lookup(const CString & strKey, CVariant * pvarVal) const
{
	bool found = false;

	CString strRealKey = strKey;
	if (!m_bCaseSensitive) {
		strRealKey.ToLower();
	}

	CKeyValPair *pResult = m_map.Search(CKeyValPair(strRealKey));
	if (pResult) {
		*pvarVal = pResult->GetVal();
		found = true;
	}

	return found;
}