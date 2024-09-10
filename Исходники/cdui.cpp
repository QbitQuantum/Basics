void
CRecoveryHandler::PrintW(
	DWORD inPrintWhat,
	LPCWSTR inFormat,
	va_list inArgList)
/*++

Routine Description:

	Does for unicode strings what PrintA does for ascii strings

Arguments:

	refer PrintA

Returns:

	None

--*/
{
	wchar_t szMsg[1024];

	StringCchVPrintfW(
					szMsg,
					sizeof(szMsg)/sizeof(wchar_t),
					inFormat,
					inArgList);

	std::wstring trcMsg = szMsg;

	size_t i_CR = 0;

	while (i_CR != -1)
	{
		i_CR = trcMsg.find_first_of(L'\r', 0);

		if (i_CR != -1)
		{
			trcMsg.erase(i_CR, 1);
		}
	}

	std::wstring lastMsg;
	bool bUseLastMsg = false;

	int itemCount = ListView_GetItemCount(m_hwndListCtrl);
	if (itemCount > 0)
	{
		LVITEMW lastLvItem;
		ZeroMemory(&lastLvItem, sizeof(LVITEMW));
		lastLvItem.mask			= LVIF_TEXT | LVIF_PARAM;
		lastLvItem.pszText		= szMsg;
		lastLvItem.cchTextMax	= 512;
		lastLvItem.iItem		= itemCount - 1;
		lastLvItem.iSubItem		= 0;
		SendMessageW(m_hwndListCtrl, LVM_GETITEMW, 0, (LPARAM)&lastLvItem);

		if ((lastLvItem.lParam & 0x80000000) == 0 &&
			(lastLvItem.lParam & 0xFF) == inPrintWhat)
		{
			bUseLastMsg = true;
			lastMsg = lastLvItem.pszText;
			itemCount--;
		}
	}

	size_t i_begin = 0;
    size_t i_end = 0;

	do
	{
		if (i_begin >= trcMsg.length())
		{
			break;
		}

		DWORD templParam = 0;
		std::wstring newMsg;

		i_end = trcMsg.find_first_of('\n', i_begin);

		if (i_end != -1)
		{
			templParam = 0x80000000;
			newMsg = trcMsg.substr(i_begin, i_end - i_begin);
			i_begin = i_end + 1;
		}
		else
		{
			newMsg = trcMsg.substr(i_begin, trcMsg.length() - i_begin);
		}


		newMsg = lastMsg + newMsg;
		lastMsg = L"";

		LVITEMW lvItem;
		ZeroMemory(&lvItem, sizeof(LVITEMW));
		lvItem.mask		= LVIF_TEXT | LVIF_PARAM;
		lvItem.iItem	= itemCount++;
		lvItem.iSubItem = 0;
		lvItem.pszText	= (LPWSTR)newMsg.c_str();
		lvItem.lParam	= inPrintWhat | templParam;

		if(bUseLastMsg)
		{
			bUseLastMsg = false;
			SendMessageW(m_hwndListCtrl, LVM_SETITEMW, 0, (LPARAM)&lvItem);
		}
		else
		{
			SendMessageW(m_hwndListCtrl, LVM_INSERTITEMW, 0, (LPARAM)&lvItem);
			ListView_EnsureVisible(m_hwndListCtrl, itemCount - 1, FALSE);
		}
	}while (i_end != -1);
}