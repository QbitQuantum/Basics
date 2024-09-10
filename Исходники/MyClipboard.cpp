wchar_t* GetCliboardText(DWORD& rnErrCode, wchar_t* rsErrText, INT_PTR cchErrMax)
{
	if (!rsErrText || cchErrMax < 255)
	{
		_ASSERTE(FALSE && "Invalid arguments");
		return NULL;
	}

	HGLOBAL hglb;
	LPCWSTR lptstr;
	wchar_t* pszBuf = NULL;

	if ((hglb = GetClipboardData(CF_UNICODETEXT)) == NULL)
	{
		rnErrCode = GetLastError();
		_wsprintf(rsErrText, SKIPLEN(cchErrMax) L"Clipboard does not contain CF_UNICODETEXT, nothing to paste (code=%u)", rnErrCode);
		gpConEmu->LogString(rsErrText);
		_wcscpy_c(rsErrText, cchErrMax, L"Available formats:");
		int nLen = lstrlen(rsErrText);
		UINT fmt = 0;
		while (((nLen + 11) < cchErrMax) && ((fmt = EnumClipboardFormats(fmt)) != 0))
		{
			_wsprintf(rsErrText+nLen, SKIPLEN(cchErrMax-nLen) L" x%04X", fmt);
			nLen += lstrlen(rsErrText+nLen);
		}
		gpConEmu->LogString(rsErrText);
		rsErrText[0] = 0; // Don't call DisplayLastError
		TODO("Сделать статусное сообщение с таймаутом");
		//this->SetConStatus(L"Clipboard does not contains text. Nothing to paste.");
	}
	else if ((lptstr = (LPCWSTR)GlobalLock(hglb)) == NULL)
	{
		rnErrCode = GetLastError();
		_wsprintf(rsErrText, SKIPLEN(cchErrMax) L"Can't lock CF_UNICODETEXT, paste failed (code=%u)", rnErrCode);
		gpConEmu->LogString(rsErrText);
	}
	else if (*lptstr == 0)
	{
		rnErrCode = GetLastError();
		_wsprintf(rsErrText, SKIPLEN(cchErrMax) L"CF_UNICODETEXT is empty, nothing to paste (code=%u)", rnErrCode);
		gpConEmu->LogString(rsErrText);
		rsErrText[0] = 0; // Don't call DisplayLastError
		GlobalUnlock(hglb);
	}
	else
	{
		pszBuf = lstrdup(lptstr, 1); // Reserve memory for space-termination
		Assert(pszBuf!=NULL);
		GlobalUnlock(hglb);
	}

	return pszBuf;
}