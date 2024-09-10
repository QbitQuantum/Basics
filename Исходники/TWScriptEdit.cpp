void CTWScriptEdit::FormatTextRange(int nStart, int nEnd)
{
	if (nStart >= nEnd)
		return;

	m_bInForcedChange = TRUE;

	CHARRANGE crOldSel;

	GetSel(crOldSel);
	LockWindowUpdate();
	HideSelection(TRUE, FALSE);

	WCHAR *pBuffer = NULL;
	try {
		SetSel(nStart, nEnd);
		//pBuffer = new WCHAR[nEnd - nStart + 1];
		CHAR* pBuffer2 = new CHAR[nEnd - nStart + 1];
		long nLen = GetSelText(pBuffer2);
		pBuffer = GetUnicode(pBuffer2);
		ASSERT(nLen <= nEnd - nStart);

		pBuffer[nLen] = 0;

		WCHAR *pStart, *pPtr;
		pStart = pPtr = pBuffer;

		WCHAR* pSymbolStart = NULL;
		SymbolColor ic;

		while (*pPtr != 0) {
			WCHAR ch = *pPtr;

			if (ch == m_chComment && (m_chComment2 == 0 || pPtr[1] == m_chComment2)) {
				pSymbolStart = pPtr;
				do {
					ch = *(++pPtr);
				} while (ch != 0 && ch != '\r');
				ic = m_icComment;
			} else if (IsStringQuote(ch)) { // Process strings
				pSymbolStart = pPtr;
				WCHAR ch1 = ch;
				do {
					ch = *(++pPtr);
				} while (ch != 0 && ch != ch1 && ch != '\r');
				if (ch == ch1) pPtr++;
				ic = m_icString;
			} else if (_istdigit(ch)) { // Process numbers
				pSymbolStart = pPtr;
				wcstod(pSymbolStart, &pPtr);
				ic = m_icNumber;
			} else if (_istalpha(ch) || ch == '_') { // Process keywords
				pSymbolStart = pPtr;
				do {
					ch = *(++pPtr);
				} while (_istalnum(ch) || ch == '_');
				*pPtr = 0;
				int nPos = IsKeyword(pSymbolStart);
				if (nPos >= 0) {
					ChangeCase(nStart + pSymbolStart - pBuffer, nStart + pPtr - pBuffer, 
								m_strKeywords.Mid(nPos+1, pPtr - pSymbolStart));
					if (wcsicmp(m_strComment, pSymbolStart) == 0) {
						*pPtr = ch;
						*pSymbolStart = m_chComment;
						if (pSymbolStart[1] != 0 && m_chComment2 != 0)
							pSymbolStart[1] = m_chComment2;
						pPtr = pSymbolStart;
						pSymbolStart = NULL;
						continue;
					}
					ic = m_icKeyword;
				} else {
					nPos = IsConstant(pSymbolStart);
					if (nPos >= 0) {
							ChangeCase(nStart + pSymbolStart - pBuffer, nStart + pPtr - pBuffer, 
										m_strConstants.Mid(nPos+1, pPtr - pSymbolStart));
						ic = m_icConstant;
					} else {
						pSymbolStart = NULL;
					}
				}
				*pPtr = ch;
			} else {
				pPtr++;
			}

			if (pSymbolStart != NULL) {
				ASSERT(pSymbolStart < pPtr);
				SetFormatRange(nStart + pStart - pBuffer, nStart + pSymbolStart - pBuffer, FALSE, RGB(0,0,0));
				SetFormatRange(nStart + pSymbolStart - pBuffer, nStart + pPtr - pBuffer, ic.bBold, ic.clrColor);
				pStart = pPtr;
				pSymbolStart = 0;
			} else if (*pPtr == 0)
				SetFormatRange(nStart + pStart - pBuffer, nStart + pPtr - pBuffer, FALSE, RGB(0,0,0));
		}

	} catch(...){}

	//delete [] pBuffer;

	SetSel(crOldSel);
	HideSelection(FALSE, FALSE);
	UnlockWindowUpdate();

	m_bInForcedChange = FALSE;
}