void *TclWinGetTclInstance()
{
    void *hInstance = NULL;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
	    (const char *)&winTCharEncoding, &hInstance);
    return hInstance;
}