BOOL ReadImageGlobalFlagsFromRegistry( _In_z_ PCWSTR ImageName, _Out_ ULONG* Flag )
{
    HKEY hKey;
    WCHAR FullKey[260];
    if(!ImageName || !ImageName[0])
    {
        *Flag = 0;
        return TRUE;
    }
    StringCchPrintfW(FullKey, 260, IMAGE_FILE_OPTIONS, ImageName);
    if(EnableDebug())
    {
        LONG lRet = RegOpenKeyExW( HKEY_LOCAL_MACHINE, FullKey, 0, KEY_READ, &hKey );
        if( ERROR_SUCCESS == lRet )
        {
            AutoCloseReg raii(hKey);
            DWORD Type = 0, cbData = sizeof(*Flag);
            if( ERROR_SUCCESS == RegQueryValueExW( hKey, GLOBALFLAG_VALUENAME, NULL, &Type, (LPBYTE)Flag, &cbData ) && Type == REG_DWORD )
            {
                return TRUE;
            }
        }
        else if(ERROR_FILE_NOT_FOUND == lRet)
        {
            *Flag = 0;
            return TRUE;
        }
    }
    return FALSE;
}