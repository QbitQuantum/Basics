/***********************************************************************
 *           CoGetClassObject [COMPOBJ.7]
 *
 */
HRESULT WINAPI CoGetClassObject16(
    SEGPTR rclsid, DWORD dwClsContext, COSERVERINFO *pServerInfo,
    SEGPTR riid, SEGPTR ppv)
{
    LPVOID *ppvl = MapSL(ppv);

    TRACE("CLSID: %s, IID: %s\n", debugstr_guid(MapSL(rclsid)), debugstr_guid(MapSL(riid)));

    *ppvl = NULL;

    if (pServerInfo) {
        FIXME("pServerInfo->name=%s pAuthInfo=%p\n",
              debugstr_w(pServerInfo->pwszName), pServerInfo->pAuthInfo);
    }

    if (CLSCTX_INPROC_SERVER & dwClsContext)
    {
        char idstr[CHARS_IN_GUID];
        char buf_key[CHARS_IN_GUID+19], dllpath[MAX_PATH+1];
        LONG dllpath_len = sizeof(dllpath);

        HMODULE16 dll;
        FARPROC16 DllGetClassObject;

        WORD args[6];
        DWORD dwRet;

        StringFromGUID216(MapSL(rclsid), idstr, CHARS_IN_GUID);
        sprintf(buf_key, "CLSID\\%s\\InprocServer", idstr);
        if (RegQueryValueA(HKEY_CLASSES_ROOT, buf_key, dllpath, &dllpath_len))
        {
            ERR("class %s not registered\n", debugstr_guid(MapSL(rclsid)));
            return REGDB_E_CLASSNOTREG;
        }

        dll = LoadLibrary16(dllpath);
        if (!dll)
        {
            ERR("couldn't load in-process dll %s\n", debugstr_a(dllpath));
            return E_ACCESSDENIED; /* FIXME: or should this be CO_E_DLLNOTFOUND? */
        }

        DllGetClassObject = GetProcAddress16(dll, "DllGetClassObject");
        if (!DllGetClassObject)
        {
            ERR("couldn't find function DllGetClassObject in %s\n", debugstr_a(dllpath));
            FreeLibrary16(dll);
            return CO_E_DLLNOTFOUND;
        }

        TRACE("calling DllGetClassObject %p\n", DllGetClassObject);
        args[5] = SELECTOROF(rclsid);
        args[4] = OFFSETOF(rclsid);
        args[3] = SELECTOROF(riid);
        args[2] = OFFSETOF(riid);
        args[1] = SELECTOROF(ppv);
        args[0] = OFFSETOF(ppv);
        WOWCallback16Ex((DWORD) DllGetClassObject, WCB16_PASCAL, sizeof(args), args, &dwRet);
        if (dwRet != S_OK)
        {
            ERR("DllGetClassObject returned error 0x%08x\n", dwRet);
            FreeLibrary16(dll);
            return dwRet;
        }

        return S_OK;
    }

    FIXME("semi-stub\n");
    return E_NOTIMPL;
}