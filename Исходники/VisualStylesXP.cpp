/////////////////////////////////////////////////////////////////////////////
// Added by Mathias Tunared 2002-07-27
//
BOOL CVisualStylesXP::UseVisualStyles()
{
	static BOOL bUse = -1;
	if( bUse != -1 )
		return bUse;

	HINSTANCE hinstDll;
	DLLVERSIONINFO dvi;
	ZeroMemory(&dvi, sizeof(dvi));

	hinstDll = LoadLibrary(TEXT("comctl32.dll"));
	if(hinstDll)
	{
		DLLGETVERSIONPROC pDllGetVersion;
		pDllGetVersion = (DLLGETVERSIONPROC) GetProcAddress(hinstDll, "DllGetVersion");
		if(pDllGetVersion)
		{
			ZeroMemory(&dvi, sizeof(dvi));
			dvi.cbSize = sizeof(dvi);
			(*pDllGetVersion)(&dvi);
		}
		FreeLibrary(hinstDll);
	}

	if( dvi.dwMajorVersion == 6 && dvi.dwMinorVersion == 0 )
	{
		//+++
		WCHAR szName [256];
		WCHAR szColor [256];

		if (!GetCurrentThemeName(szName, 255, szColor, 255, NULL, 0))
		{
			CString strWinXPThemeColor = szColor;
			if (strWinXPThemeColor.CompareNoCase (_T("normalcolor")) == 0 ||
				strWinXPThemeColor.CompareNoCase (_T("homestead")) == 0 ||
				strWinXPThemeColor.CompareNoCase (_T("metallic")) == 0)
			{
				bUse = TRUE;
				return IsAppThemed() && m_hThemeDll; // No need to test HTHEME, but...
			}
		}
	}

	bUse = FALSE;
	return FALSE;
}