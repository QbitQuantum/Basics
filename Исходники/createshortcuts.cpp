long GetShortCut( char *linkpath, char *newpath )
{
	HRESULT hres;
	IShellLink* psl;
	WIN32_FIND_DATA fd; 
    
	CoInitialize(NULL);
	hres = CoCreateInstance(CLSID_ShellLink, NULL, 
        CLSCTX_INPROC_SERVER, IID_IShellLink,(void**)&psl); 
    if (SUCCEEDED(hres)) {
		IPersistFile *ppf;
		hres = psl->QueryInterface (IID_IPersistFile, (void **)&ppf);		//IID_IPersistFile
		if (SUCCEEDED(hres)) { 
            WCHAR wsz[MAX_PATH];

            MultiByteToWideChar(CP_ACP, 0, linkpath, -1, wsz,  MAX_PATH);              // Load the shortcut. 
			hres = ppf->Load(wsz, TRUE); 
			if (SUCCEEDED(hres)) {
				psl->GetPath(newpath ,256, &fd, SLGP_SHORTPATH );
			}
            ppf->Release();
			if(!SUCCEEDED(hres))
				return false;
		} else
			return false;
        psl->Release();
	} else
		return false;
	CoUninitialize();
	return true;
}