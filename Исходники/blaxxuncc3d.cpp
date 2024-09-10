BOOL CGLViewCtrlApp::InitInstance()
{
    TRACE("CGLViewCtrlApp::InitInstance() \n");

    cc3d_old_new_handler=_set_new_handler(cc3d_new_handler);
    cc3d_old_new_mode=_set_new_mode(1); // for malloc too



#ifdef _KATMAI
    if (!KatmaiInit()) {
        // AfxMessageBox("This version requires an Intel Katmai processor \n Program will be terminated ");

        //MessageBox(NULL,"This version requires an Intel Katmai processor \n Program will be terminated " ,_PROGRAM,MB_OK);

        //return FALSE;
    }
    else {
        TRACE("CGLViewCtrlApp::Running on Intel Katmai processor \n");
    }
#endif


    BOOL bInit = COleControlModule::InitInstance();

    // Initialize the ATL Module
    _Module.Init(ObjectMap,m_hInstance);

#if 0 // only for EXE's
#ifdef _AFXDLL
    Enable3dControls();			// Call this when using MFC in a shared DLL
#else
    Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif
    VERIFY(SUCCEEDED(_Module.RegisterServer(TRUE)));// ATL Classes
    //VERIFY(SUCCEEDED(_Module.RegisterTypeLib("glviewvrml.tlb")));// type lib


    if (bInit)
    {
        // TODO: Add your own module initialization code here.

        // set the default error reporting object
        GReporter::SetCurrent(new GReporter());
        GReporter::SetDefault(GReporter::current);

#ifdef _EAI_TRACE
        // for tracing EAI calls
        if (GTrace::current == NULL) {
            FILE *f = fopen("\\temp\\glviewlog.txt","w");
            GTrace::SetCurrent(new GTrace(f));
        }
#endif


        EAI_TRACE("CGLViewCtrlApp::InitInstance()\n");
        EAI_FLUSH();

        // make sure Gv VRML  database is init
        GvDB::init();

        // set the cache directory
        CString tmp;
        CString installDir;

        if (1) { // use local install directory
            GetModuleFileName(AfxGetInstanceHandle( ), tmp.GetBuffer(_MAX_PATH),_MAX_PATH);
            tmp.ReleaseBuffer();
            int iBackslash = tmp.ReverseFind('\\');
            if (iBackslash != -1) 	tmp = tmp.Left(iBackslash+1);
            installDir = tmp;

        } else {
            GetTempPath(_MAX_PATH,tmp.GetBuffer(_MAX_PATH));
            tmp.ReleaseBuffer();
        }
        if (tmp.GetLength()>0) {
            int l = tmp.GetLength();
            if (tmp[l-1] != '\\')
                tmp += '\\';
        }
        tmp += "cache";
        GFile::cacheDirectory = tmp;
        TRACE("Cache directory is : %s \n",(const char *)tmp);

        // set the new ini-file name (stored in the ccpro directory, name is cc3d.ini)
        tmp = installDir + "cc3d.ini";
        if (m_pszProfileName)  free( (void*)m_pszProfileName );
        m_pszProfileName = _tcsdup( tmp );

        TRACE("Ini file is : %s \n",(const char *)tmp);

        if (m_pszAppName)  free( (void*)m_pszAppName );
        m_pszAppName = _tcsdup(_PROGRAM);


    }

    return bInit;
}