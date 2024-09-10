HRESULT CMainFrameDropTarget::PasteHDROP(COleDataObject &data)
{
	HRESULT hrPasteResult = E_FAIL;
	HANDLE hMem;
	if ((hMem = data.GetGlobalData(CF_HDROP)) != NULL)
	{
		LPDROPFILES lpDrop;
		if ((lpDrop = (LPDROPFILES)GlobalLock(hMem)) != NULL)
		{
			if (lpDrop->fWide)
			{
				LPCWSTR pszFileNameW = (LPCWSTR)((LPBYTE)lpDrop + lpDrop->pFiles);
				while (*pszFileNameW != L'\0')
				{
					USES_CONVERSION;
					if (FAILED(AddUrlFileContents(W2CT(pszFileNameW))))
						break;
					hrPasteResult = S_OK;
					pszFileNameW += wcslen(pszFileNameW) + 1;
				}
			}
			else
			{
				LPCSTR pszFileNameA = (LPCSTR)((LPBYTE)lpDrop + lpDrop->pFiles);
				while (*pszFileNameA != '\0')
				{
					USES_CONVERSION;
					if (FAILED(AddUrlFileContents(A2CT(pszFileNameA))))
						break;
					hrPasteResult = S_OK;
					pszFileNameA += strlen(pszFileNameA) + 1;
				}
			}
			GlobalUnlock(hMem);
		}
		GlobalFree(hMem);
	}
	return hrPasteResult;
}