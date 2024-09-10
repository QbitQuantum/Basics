//***************************************************************************************
BOOL CBCGPXMLSettings::DeleteKey (LPCTSTR pszPath, BOOL bAdmin)
{
	if (m_bReadOnly)
	{
		return FALSE;
	}
	
	CBCGPXMLNode* pNode = bAdmin ? &m_Local : &m_User;

	ASSERT (pszPath != NULL);
	CString strPath = pszPath;

	int iPathLen = strPath.GetLength ();
	if (iPathLen > 0 && strPath [iPathLen - 1] != _T('\\'))
	{
		strPath += _T('\\');
	}
	
	for (int iFrom = 0; iFrom < strPath.GetLength ();)
	{
		int iEnd = strPath.Find (_T('\\'), iFrom);
		if (iEnd < 0)
		{
			ASSERT (FALSE);
			return FALSE;
		}

		CString strSubKey = strPath.Mid (iFrom, iEnd - iFrom);
		strSubKey.Remove (_T(' '));
		
		CBCGPXMLNode* pChild = pNode->FindChild (strSubKey);
		if (pChild == NULL)
		{
			return FALSE;
		}

		pNode = pChild;
		iFrom = iEnd + 1;
	}

	ASSERT_VALID (pNode->m_pParent);
	for (POSITION pos = pNode->m_pParent->m_lstChildren.GetHeadPosition (); pos != NULL;)
	{
		POSITION posSave = pos;

		CBCGPXMLNode* pCurrNode = pNode->m_pParent->m_lstChildren.GetNext (pos);
		ASSERT_VALID (pCurrNode);

		if (pNode == pCurrNode)
		{
			pNode->m_pParent->m_lstChildren.RemoveAt (posSave);
			delete pNode;
			return TRUE;
		}
	}

	ASSERT(FALSE);
	return FALSE;
}