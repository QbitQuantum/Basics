void CSetPgBase::setHotkeyCheckbox(HWND hDlg, WORD nCtrlId, int iHotkeyId, LPCWSTR pszFrom, LPCWSTR pszTo, UINT uChecked)
{
	wchar_t szKeyFull[128] = L"";
	gpSet->GetHotkeyNameById(iHotkeyId, szKeyFull, false);
	if (szKeyFull[0] == 0)
	{
		EnableWindow(GetDlgItem(hDlg, nCtrlId), FALSE);
		checkDlgButton(hDlg, nCtrlId, BST_UNCHECKED);
	}
	else
	{
		if (pszFrom)
		{
			wchar_t* ptr = (wchar_t*)wcsstr(szKeyFull, pszFrom);
			if (ptr)
			{
				*ptr = 0;
				if (pszTo)
				{
					wcscat_c(szKeyFull, pszTo);
				}
			}
		}

		CEStr lsText(GetDlgItemTextPtr(hDlg, nCtrlId));
		LPCWSTR pszTail = lsText.IsEmpty() ? NULL : wcsstr(lsText, L" - ");
		if (pszTail)
		{
			CEStr lsNew(szKeyFull, pszTail);
			SetDlgItemText(hDlg, nCtrlId, lsNew);
		}

		checkDlgButton(hDlg, nCtrlId, uChecked);
	}
}