BOOL CCtrlInfo::Modify(const CWnd* pCtrl, const CWnd* pParent, 
		LPCTSTR lpszString, char chSpr /*= '+'*/)
{
	ASSERT(::IsWindow(pCtrl->m_hWnd));
	ASSERT(::IsWindow(pParent->m_hWnd));
	ASSERT(::IsChild(pParent->m_hWnd, pCtrl->m_hWnd));

	pCtrl->GetWindowRect(&m_rcInit);
	pParent->ScreenToClient(&m_rcInit);

	// XR: Get position information from Initialization string
	CString str = lpszString;
	str.Remove(' ');
	str.MakeUpper();

	int nLen = str.GetLength();
	int posSpr = -1;
	int posSprNext = 0;
	while(posSprNext != -1)
	{
		CString strSection;
		posSprNext = str.Find(chSpr, posSpr + 1);  // XR: default separator between sections is '+'
		if (posSprNext == -1)
			strSection = str.Mid(posSpr + 1, nLen - posSpr - 1);
		else
			strSection = str.Mid(posSpr + 1, posSprNext - posSpr - 1);
		
		if (!this->ExtractOptions(strSection, pCtrl, pParent))
			return FALSE;

		posSpr = posSprNext;
	}
	return TRUE;
}