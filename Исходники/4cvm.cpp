int __cdecl _tmain(int argc, TCHAR** argv)
{
    int nErrors;

    //init the static g_szModuleName:
    if(GetModuleFileName(NULL, g_szModuleName, FC_ARRAY_LEN(g_szModuleName))==0)
    {
	   FC_ASSERT_LASTERR(_T("GetModuleFileName"));
       return 1;
    }

    //do some core init:
    InitModuleCheckMemory(MODULE_NAME);

    if(FAILED(CoInitialize(NULL)))
    {
        _tprintf(CG_FATAL_MSGFMT,__FILE__,__LINE__,_T("CoInitialize failed"));
        nErrors = 1;
        goto Ende;
    }


    //always remove the module name.
    argv++;
    argc--;

    //get internal debug switches:
    if(argc>0 && !lstrcmpi(_T("-!bug"), argv[0]))
    {
        argv++;argc--;
        if(argc>0 && !lstrcmpi(_T("heap"), argv[0]))
        {
            argv++;argc--;
            if(argc>0)
            {
                FC_SetAllocBreak(_tcstoul(argv[0], NULL, 10));
                argv++;argc--;
            }
        }
    }


    //TODO get from registry
    if(!SetThreadLocale(MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),SORT_DEFAULT)))
    {
        FC_ASSERT_LASTERR("SetThreadLocale()");
        //don't care any more...
    }

    //enter main backend routine:
    nErrors = CGPCmain(argc, argv);
    
    CoUninitialize();

Ende:
    ExitModuleCheckMemory(MODULE_NAME);
    return nErrors?1:0;
}