BOOL ResolveShortcut(TCHAR *shortcut, TCHAR *file)
{
	CoInitialize(NULL);

    IShellLink* psl = NULL;

    HRESULT hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **) &psl);

    if (SUCCEEDED(hr)) 
    {
        IPersistFile* ppf = NULL; 
		hr = psl->QueryInterface(IID_IPersistFile,  (void **) &ppf); 

        if (SUCCEEDED(hr))
		{
#ifdef _UNICODE
			hr = ppf->Load(shortcut, STGM_READ); 
#else
			WCHAR tmp[MAX_PATH]; 
			MultiByteToWideChar(CP_ACP, 0, shortcut, -1, tmp, MAX_PATH); 
			hr = ppf->Load(tmp, STGM_READ); 
#endif

			if (SUCCEEDED(hr))
			{
				hr = psl->Resolve(NULL, SLR_UPDATE); 

				if (SUCCEEDED(hr))
				{
					WIN32_FIND_DATA wfd;
					hr = psl->GetPath(file, MAX_PATH, &wfd, SLGP_RAWPATH); 
				}
			}

            ppf->Release(); 
		}
        psl->Release(); 
    }

	if(FAILED(hr))
		ErrorExit(NULL,_T("CreateShortcut"));
	return SUCCEEDED(hr);
}