STDMETHODIMP CShellExt::Initialize(LPCITEMIDLIST pIDFolder,
                                   LPDATAOBJECT pDataObj,
                                   HKEY hRegKey)
{
	FORMATETC	format={CF_HDROP,NULL,DVASPECT_CONTENT,-1,TYMED_HGLOBAL};
	STGMEDIUM	medium;
	int			i,nLen;
	WCHAR		szDirectory[MAX_PATH];

	HRESULT hr;
	TCHAR szAppData[MAX_PATH];

	hr = SHGetSpecialFolderPath(NULL, szAppData,CSIDL_COMMON_DESKTOPDIRECTORY ,FALSE);
    // Initialize can be called more than once
    if (m_pDataObj)
    	m_pDataObj->Release();
    // duplicate the object pointer and registry handle
    if (pDataObj)
    {
    	m_pDataObj = pDataObj;
    	pDataObj->AddRef();
    }

	pDataObj->GetData(&format,&medium);  
	m_nSelected=DragQueryFileW((HDROP&)medium.hGlobal,0xFFFFFFFF,NULL,0);

	if (m_nSelected == -1 || m_nSelected ==0)
	{
		wcscpy(m_szCommand,L"DeleteFileInRecycled");
		return NOERROR;
	}
	m_szCommand[0] = L'\0';
	for(i=0;i<m_nSelected;i++)
	{
		DragQueryFileW((HDROP&)medium.hGlobal,i,szDirectory,MAX_PATH);
		if (i != 0)
			wcscat(m_szCommand,L" ");
		nLen = wcslen(m_szCommand);
		m_szCommand[nLen] = L'"';
		m_szCommand[nLen+1] = L'\0';
		wcscat(m_szCommand,szDirectory);
		nLen = wcslen(m_szCommand);
		m_szCommand[nLen] = L'"';
		m_szCommand[nLen+1] = L'\0';
	}
    return NOERROR;
}