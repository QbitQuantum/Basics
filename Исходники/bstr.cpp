DWORD CbBSTR::SetCharString(char *str)
{
	Release();
	//if (str[0] == 0) return NULL;
	int	i;
	int	len = strlen(str);
	m_bstr = SysAllocStringByteLen(NULL,(len)*2); if (m_bstr == NULL) return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CbBSTR::SetCharString ... SysAllocStringByteLen ");
	m_bstr_size = len;
	i = MultiByteToWideChar(CP_ACP,0,str,len,m_bstr,len);
	if (i == len) return ERR_OK;
	Release();
	return SetError_Add_W32_code_msg(true,ERR_API,GetLastError(),"CbBSTR::SetCharString ... MultiByteToWideChar ");
}