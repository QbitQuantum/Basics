void *Tk_GetHINSTANCE()
{
    void *hInstance = NULL;

    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
	    (const char *) &tkIntStubs, &hInstance);
    return hInstance;
}