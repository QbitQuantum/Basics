HRESULT CSimpleShlExt::GetCommandString( UINT idCmd, UINT uFlags,UINT* pwReserved, LPSTR pszName, UINT cchMax ) 
{
	USES_CONVERSION; 
	//检查 idCmd, 它必须是0，因为我们仅有一个添加的菜单项. 
	if ( 0 != idCmd ) 
		return E_INVALIDARG; 

	// 如果 Explorer 要求帮助字符串，就将它拷贝到提供的缓冲区中. 
	if ( uFlags & GCS_HELPTEXT ) 
	{
		LPCTSTR szText = _T("This is the simple shell extension's help");              
		if ( uFlags & GCS_UNICODE )
		{ 
			// 我们需要将 pszName 转化为一个 Unicode 字符串, 接着使用Unicode字符串拷贝 API. 
			lstrcpynW ( (LPWSTR) pszName, T2CW(szText), cchMax ); 
		} 
		else
		{ 
			// 使用 ANSI 字符串拷贝API 来返回帮助字符串. 
			lstrcpynA ( pszName, T2CA(szText), cchMax ); 
		} 
		return S_OK;
	} 
	return E_INVALIDARG; 
}