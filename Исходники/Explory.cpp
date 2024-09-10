HRESULT ResolveShortcut(const TCHAR* LnkFile, TCHAR* FilePath,
                        TCHAR* LnkDesc, TCHAR* WorkDir) 
{ 
    CoInitialize(NULL);
    HRESULT hres; 
    IShellLink* psl; 
    WIN32_FIND_DATA wfd; 
    TCHAR strfilepath[MAX_PATH];     
    TCHAR strlnkdesc[INFOTIPSIZE];
    TCHAR strworkdir[MAX_PATH];

    USES_CONVERSION;
 
    hres = CoCreateInstance(CLSID_ShellLink, NULL, 
            CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID *) &psl); 
    if (SUCCEEDED(hres)) 
    { 
        IPersistFile* ppf;         
        hres = psl->QueryInterface(IID_IPersistFile, (LPVOID *)&ppf); 
        if (SUCCEEDED(hres)) 
        { 
            hres = ppf->Load(LnkFile, STGM_READ); 
            if (SUCCEEDED(hres)) 
            {               
                hres = psl->Resolve(GetDesktopWindow(), 0); 
                if (SUCCEEDED(hres)) 
                { 
                    hres = psl->GetPath(strfilepath,MAX_PATH, &wfd, 
                                           SLGP_UNCPRIORITY );
                    
                    if (SUCCEEDED(hres)) 
                    {      
						_tcscpy(FilePath, strfilepath); 
                        hres = psl->GetDescription(strlnkdesc,INFOTIPSIZE);
                    }

                    if (SUCCEEDED(hres)) 
                    {
                        _tcscpy(LnkDesc,strlnkdesc);
                        hres = psl->GetWorkingDirectory(strworkdir,MAX_PATH);
                    }

                    if (SUCCEEDED(hres)) 
                    {
                        _tcscpy(WorkDir,strworkdir);
                    }
                } 
            }         
            ppf->Release(); 
        }     
        psl->Release(); 
    } 
    CoUninitialize();
    return hres; 
} 