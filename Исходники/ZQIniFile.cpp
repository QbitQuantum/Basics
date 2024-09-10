void CZQIniFile::WriteFloat(char* szSection, char* szKey, float fltValue)
{
	char szValue[255];
	sprintf_s(szValue,255, "%f", fltValue);
	WritePrivateProfileString((LPCSTR)szSection, (LPCSTR)szKey, (LPCSTR)szValue, (LPCSTR)m_szFileName);
}