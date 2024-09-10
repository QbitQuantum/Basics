BOOL CXTPColorDialog::CopyToClipboard(const CString& strText)
{
	if (::OpenClipboard(m_hWnd))
	{
		::EmptyClipboard();

		HGLOBAL hGlobalBuff = ::GlobalAlloc(GMEM_MOVEABLE, strText.GetLength() + 1);
		if (!hGlobalBuff)
		{
			::CloseClipboard();
			return FALSE;
		}

		CHAR* szBuffer = (CHAR*)::GlobalLock(hGlobalBuff);

		WCSTOMBS_S(szBuffer, strText, strText.GetLength() + 1);
		::GlobalUnlock(hGlobalBuff);

		if (::SetClipboardData(CF_TEXT, hGlobalBuff) == NULL)
			return FALSE;

		::CloseClipboard();
		return TRUE;
	}

	return FALSE;
}