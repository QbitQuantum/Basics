// Если nCtrlId==0 - hParent==hList
int CSetDlgLists::SelectStringExact(HWND hParent, WORD nCtrlId, LPCWSTR asText)
{
	if (!hParent)  // был ghOpWnd. теперь может быть вызван и для других диалогов!
		return -1;

	HWND hList = nCtrlId ? GetDlgItem(hParent, nCtrlId) : hParent;
	_ASSERTE(hList!=NULL);

	int nIdx = SendMessage(hList, CB_FINDSTRINGEXACT, -1, (LPARAM)asText);

	if (nIdx < 0)
	{
		int nCount = SendMessage(hList, CB_GETCOUNT, 0, 0);
		wchar_t* pszNumEnd = NULL;
		int nNewVal = wcstol(asText, &pszNumEnd, 10), nCurVal;
		bool bUseNumCmp = (pszNumEnd && *pszNumEnd) && ((nNewVal != 0) || (lstrcmp(pszNumEnd, L"0") == 0));

		// For `Font Sizes` generally
		if (bUseNumCmp)
		{
			wchar_t temp[MAX_PATH] = {};

			for (int i = 0; i < nCount; i++)
			{
				if (!SendMessage(hList, CB_GETLBTEXT, i, (LPARAM)temp))
					break;

				nCurVal = _wtol(temp);

				if (nCurVal == nNewVal)
				{
					nIdx = i;
					break;
				}
				else if (nCurVal > nNewVal)
				{
					nIdx = SendMessage(hList, CB_INSERTSTRING, i, (LPARAM)asText);
					break;
				}
			}
		}

		if (nIdx < 0)
		{
			nIdx = SendMessage(hList, CB_INSERTSTRING, 0, (LPARAM)asText);
		}
	}

	if (nIdx >= 0)
		SendMessage(hList, CB_SETCURSEL, nIdx, 0);
	else
		SetWindowText(hList, asText);

	return nIdx;
}