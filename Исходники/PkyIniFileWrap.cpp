void
PkyIniFileWrap::SetStringW( const wchar_t* pszSect, const wchar_t* pszKey, std::wstring const& val )
{
	WritePrivateProfileStringW( pszSect, pszKey, val.c_str(), m_strFileName.c_str() );
}