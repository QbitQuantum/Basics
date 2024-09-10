DWORD
DeleteTreeFromRegistry(
    PCSTR pszPath
    )
{
    DWORD ceError = ERROR_SUCCESS;
    HANDLE hReg = (HANDLE)NULL;
    HKEY pRootKey = NULL;

    ceError = RegOpenServer(&hReg);
    BAIL_ON_CENTERIS_ERROR(ceError);

    ceError = RegOpenKeyExA(
                hReg,
                NULL,
                HKEY_THIS_MACHINE,
                0,
                KEY_ALL_ACCESS,
                &pRootKey);
    if (ceError)
    {
        DJ_LOG_ERROR( "Failed to open registry root key %s",HKEY_THIS_MACHINE);
        goto error;
    }

    ceError = RegDeleteTreeA(
                hReg,
                pRootKey,
                pszPath);
    if (ceError)
    {
        //Donot log if ceError is about the key which is not present
        ceError = ERROR_SUCCESS;
    }

cleanup:

    RegCloseKey(hReg, pRootKey);
    pRootKey = NULL;

    RegCloseServer(hReg);
    hReg = NULL;

    return(ceError);
error:
    goto cleanup;

}