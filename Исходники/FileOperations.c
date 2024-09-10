HRESULT ResolveLink(HWND hwnd,DWORD fFlags,TCHAR *LinkFile,TCHAR *LinkPath,int nBufferSize)
{
	IShellLink		*pShellLink = NULL;
	IPersistFile	*pPersistFile = NULL;
	SHFILEINFO		shfi;
	WCHAR			LinkFileW[MAX_PATH];
	TCHAR			ResolvedFilePath[MAX_PATH];
	HRESULT			hr;

	SHGetFileInfo(LinkFile,NULL,&shfi,sizeof(shfi),SHGFI_ATTRIBUTES);

	if(!(shfi.dwAttributes & SFGAO_LINK))
	{
		StringCchCopy(LinkPath,nBufferSize,LinkFile);
		return E_UNEXPECTED;
	}

	hr = CoCreateInstance(CLSID_ShellLink,NULL,CLSCTX_INPROC_SERVER,
	IID_IShellLink,(LPVOID*)&pShellLink);

	if(hr == S_OK)
	{
		hr = pShellLink->QueryInterface(IID_IPersistFile,(LPVOID *)&pPersistFile);

		if(hr == S_OK)
		{
			#ifndef UNICODE
			MultiByteToWideChar(CP_ACP,0,LinkFile,-1,LinkFileW,MAX_PATH);
			#else
			StringCchCopy(LinkFileW,SIZEOF_ARRAY(LinkFileW),LinkFile);
			#endif

			hr = pPersistFile->Load(LinkFileW,STGM_READ);

			if(hr == S_OK)
			{
				pShellLink->Resolve(hwnd,fFlags);
				pShellLink->GetPath(ResolvedFilePath,MAX_PATH,NULL,SLGP_UNCPRIORITY);

				StringCchCopy(LinkPath,nBufferSize,ResolvedFilePath);
			}

			pPersistFile->Release();
		}

		pShellLink->Release();
	}

	return hr;
}