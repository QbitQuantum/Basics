BOOL CMGTOOls::WriteConfig_String( LPCTSTR lpAppName,LPCTSTR lpKeyName,LPCTSTR lpString,LPCTSTR lpFileName )
{
	if(!m_bRelative)
		return WritePrivateProfileStringW(lpAppName,lpKeyName,lpString,lpFileName);
	return WriteConfigParamValue(lpAppName,lpKeyName,lpString,lpFileName);
}