bool WINAPI EnumerateFunc(LPNETRESOURCEW lpnr,tcallbacl_shares f,void *arg)
{
    DWORD dwResult, dwResultEnum;
    HANDLE hEnum;
    DWORD cbBuffer = 16384;
    DWORD cEntries = -1;
    LPNETRESOURCEW lpnrLocal;
    DWORD i;
    dwResult = WNetOpenEnumW(RESOURCE_GLOBALNET, // all network resources
                            RESOURCETYPE_ANY,   // all resources
                            0,  // enumerate all resources
                            lpnr,       // NULL first time the function is called
                            &hEnum);    // handle to the resource

    if (dwResult != NO_ERROR) {
        return false;
    }
	lpnrLocal = (LPNETRESOURCEW) GlobalAlloc(GPTR, cbBuffer);
    if (lpnrLocal == NULL) {
        return false;
    }

    do {
        ZeroMemory(lpnrLocal, cbBuffer);
        dwResultEnum = WNetEnumResourceW(hEnum,  // resource handle
                                        &cEntries,      // defined locally as -1
                                        lpnrLocal,      // LPNETRESOURCE
                                        &cbBuffer);     // buffer size
        if (dwResultEnum == NO_ERROR) {
            for (i = 0; i < cEntries; i++) {
				f(&lpnrLocal[i],arg);
                if (RESOURCEUSAGE_CONTAINER == (lpnrLocal[i].dwUsage
                                                & RESOURCEUSAGE_CONTAINER))
                    EnumerateFunc(&lpnrLocal[i],f,arg);
            }
        }
        else if (dwResultEnum != ERROR_NO_MORE_ITEMS) {
            break;
        }
    }while (dwResultEnum != ERROR_NO_MORE_ITEMS);
    GlobalFree((HGLOBAL) lpnrLocal);
    dwResult = WNetCloseEnum(hEnum);

    if (dwResult != NO_ERROR) {
        return false;
    }

    return true;
}