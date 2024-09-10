nsresult
XPCOMGlueLoad(const char *xpcomFile, GetFrozenFunctionsFunc *func)
{
    CHAR pszError[_MAX_PATH];
    ULONG ulrc = NO_ERROR;
    HMODULE h;

    if (xpcomFile[0] == '.' && xpcomFile[1] == '\0') {
        xpcomFile = XPCOM_DLL;
    }
    else {
        char xpcomDir[MAXPATHLEN];

        _fullpath(xpcomDir, xpcomFile, sizeof(xpcomDir));
        char *lastSlash = ns_strrpbrk(xpcomDir, "/\\");
        if (lastSlash) {
            *lastSlash = '\0';

            XPCOMGlueLoadDependentLibs(xpcomDir, ReadDependentCB);

            snprintf(lastSlash, MAXPATHLEN - strlen(xpcomDir), "\\" XUL_DLL);

            DosLoadModule(pszError, _MAX_PATH, xpcomDir, &sXULLibrary);
        }
    }

    ulrc = DosLoadModule(pszError, _MAX_PATH, xpcomFile, &h);

    if (ulrc != NO_ERROR)
        return nsnull;

    AppendDependentLib(h);

    GetFrozenFunctionsFunc sym;

    ulrc = DosQueryProcAddr(h, 0, "_NS_GetFrozenFunctions", (PFN*)&sym);

    if (ulrc != NO_ERROR) {
        XPCOMGlueUnload();
        return NS_ERROR_NOT_AVAILABLE;
    }

    *func = sym;

    return NS_OK;
}