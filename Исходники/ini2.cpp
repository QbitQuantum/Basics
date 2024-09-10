CString CIni::GetStringUTF8(LPCTSTR strEntry, LPCTSTR strDefault/*=NULL*/, LPCTSTR strSection/* = NULL*/)
{
	USES_CONVERSION;
	if(strSection != NULL)
		m_strSection = strSection;

	CStringA strUTF8;
	GetPrivateProfileStringA(T2CA(m_strSection), T2CA(strEntry), T2CA(strDefault), 
							 strUTF8.GetBufferSetLength(MAX_INI_BUFFER), MAX_INI_BUFFER, T2CA(m_strFileName));
	strUTF8.ReleaseBuffer();
	return OptUtf8ToStr(strUTF8);
}