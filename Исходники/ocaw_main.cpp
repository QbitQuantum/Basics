int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int nCmdShow)
{
    CAErrno caErr;
    int nProcExit = CA_PROC_EXIT_OK;

    g_hInstance = hInstance;

    InitCommonControls();
    caErr = CAS_PStartup(__argc, __argv, &g_ocawProc);
    if (CA_ERR_SUCCESS != caErr)
    {
        CAS_Panic(CA_SRC_MARK, CA_PROC_EXIT_INIT_FAILED, 
            TEXT("Startup failed. Can't load run time library or config."
                 "Last Error code (%u). "), caErr);
        return CA_PROC_EXIT_INIT_FAILED;
    }

    nProcExit = CAS_PRun(&g_ocawProc);
    CAS_PCleanup(&g_ocawProc);
    return nProcExit;
}