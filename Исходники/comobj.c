/*
* CopEnumInterfaces
*
* Purpose:
*
* Remember list of available interfaces, excluding IUnknown.
*
*/
BOOL CopEnumInterfaces(
    _In_ INTERFACE_INFO_LIST *InterfaceList
)
{
    BOOL        bResult = FALSE;
    HKEY        hKey = NULL;
    LRESULT     lRet;
    RPC_STATUS  RpcStatus = 0;
    LPWSTR      lpKeyName = NULL;
    SIZE_T      k;
    DWORD       i, cSubKeys = 0, cMaxLength = 0, cchKey;
    IID         iid;

    INTERFACE_INFO *infoBuffer;

    __try {

        lRet = RegOpenKeyEx(HKEY_CLASSES_ROOT, TEXT("Interface"), 0, KEY_READ, &hKey);
        if (lRet != ERROR_SUCCESS)
            __leave;

        lRet = RegQueryInfoKey(hKey, NULL, NULL, NULL, &cSubKeys, &cMaxLength, NULL,
            NULL, NULL, NULL, NULL, NULL);
        if ((lRet != ERROR_SUCCESS) || (cSubKeys == 0))
            __leave;

        infoBuffer = (INTERFACE_INFO*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cSubKeys * sizeof(INTERFACE_INFO));
        if (infoBuffer == NULL)
            __leave;

        cMaxLength = (DWORD)((cMaxLength + 1) * sizeof(WCHAR));
        lpKeyName = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, cMaxLength);
        if (lpKeyName == NULL)
            __leave;

        for (k = 0, i = 0; i < cSubKeys; i++) {

            cchKey = (DWORD)(cMaxLength / sizeof(WCHAR));
            if (RegEnumKeyEx(hKey, i, lpKeyName, &cchKey, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {

                if (IIDFromString(lpKeyName, &iid) == S_OK) {

                    //skip IUnknown
                    if (UuidCompare((UUID*)&iid, (UUID*)&IID_IUnknown, &RpcStatus) == 0)
                        continue;

                    cchKey = MAX_PATH * sizeof(WCHAR);
                    infoBuffer[k].iid = iid;

                    RegGetValue(hKey, lpKeyName, TEXT(""), RRF_RT_REG_SZ, NULL,
                        (LPWSTR)&infoBuffer[k].szInterfaceName, &cchKey);

                    k++;
                }
            }
        }
        InterfaceList->cEntries = (ULONG)k;
        InterfaceList->List = infoBuffer;
        bResult = TRUE;
    }
    __finally {
        if (hKey)
            RegCloseKey(hKey);

        if (lpKeyName)
            HeapFree(GetProcessHeap(), 0, lpKeyName);
    }

    return bResult;
}