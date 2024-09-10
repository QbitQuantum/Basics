static WINBASEAPI BOOL WINAPI GetCPInfoExUW_EMULATE(UINT CodePage, DWORD dwFlags, LPCPINFOEXA lpCPInfoEx)
{
	// Emulate GetCPInfoExUW() on platforms that don't have GetCPInfoExW().
	// This can be done by using GetCPInfo(), then filling in the other fields.
	if (!lpCPInfoEx)
	{
		// Struct not specified. Don't bother converting anything.
		return GetCPInfo(CodePage, (LPCPINFO)lpCPInfoEx);
	}
	
	// Get the code page information.
	BOOL bRet = GetCPInfo(CodePage, (LPCPINFO)lpCPInfoEx);
	if (!bRet)
		return bRet;
	
	// Get the other fields for the CPINFOEX struct.
	switch (CodePage)
	{
		case CP_ACP:
			lpCPInfoEx->CodePage = GetACP();
			break;
		case CP_OEMCP:
			lpCPInfoEx->CodePage = GetOEMCP();
			break;
		default:
			lpCPInfoEx->CodePage = CodePage;
			break;
	}
	
	// Use a reasonable default for the Unicode default character.
	lpCPInfoEx->UnicodeDefaultChar = L'?';
	
	// Clear the code page name for now.
	// TODO: Add a lookup table.
	lpCPInfoEx->CodePageName[0] = 0x00;
	
	return bRet;
}