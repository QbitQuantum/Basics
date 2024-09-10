BOOL CShellMgr::GetName(LPSHELLFOLDER lpsf, LPITEMIDLIST lpi, DWORD dwFlags, LPTSTR lpFriendlyName)
{
	BOOL bSuccess = TRUE;
	STRRET str = { STRRET_CSTR };

	if (lpsf->GetDisplayNameOf(lpi, dwFlags, &str) == NOERROR)
	{
		USES_CONVERSION;

		switch (str.uType)
		{
		case STRRET_WSTR:
			lstrcpy(lpFriendlyName, W2CT(str.pOleStr));
			::CoTaskMemFree(str.pOleStr);
			break;
		case STRRET_OFFSET:
			lstrcpy(lpFriendlyName, (LPTSTR)lpi + str.uOffset);
			break;
		case STRRET_CSTR:
			lstrcpy(lpFriendlyName, A2CT(str.cStr));
			break;
		default:
			bSuccess = FALSE;
			break;
		}
	}
	else
	{
		bSuccess = FALSE;
	}

	return bSuccess;
}