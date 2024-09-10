static HRESULT WINAPI IAssemblyNameImpl_GetDisplayName(IAssemblyName *iface,
                                                       LPOLESTR szDisplayName,
                                                       LPDWORD pccDisplayName,
                                                       DWORD dwDisplayFlags)
{
    IAssemblyNameImpl *name = (IAssemblyNameImpl *)iface;
    WCHAR verstr[30];
    DWORD size;
    LPWSTR cultureval = 0;

    static const WCHAR equals[] = {'=',0};

    TRACE("(%p, %p, %p, %d)\n", iface, szDisplayName,
          pccDisplayName, dwDisplayFlags);

    if (dwDisplayFlags == 0)
    {
        if (!name->displayname || !*name->displayname)
            return FUSION_E_INVALID_NAME;

        size = min(*pccDisplayName, lstrlenW(name->displayname) + 1);

        lstrcpynW(szDisplayName, name->displayname, size);
        *pccDisplayName = size;

        return S_OK;
    }

    if (!name->name || !*name->name)
        return FUSION_E_INVALID_NAME;

    /* Verify buffer size is sufficient */
    size = lstrlenW(name->name) + 1;

    if ((dwDisplayFlags & ASM_DISPLAYF_VERSION) && (name->versize > 0))
    {
        static const WCHAR spec[] = {'%','d',0};
        static const WCHAR period[] = {'.',0};
        int i;

        wsprintfW(verstr, spec, name->version[0]);

        for (i = 1; i < name->versize; i++)
        {
            WCHAR value[6];
            wsprintfW(value, spec, name->version[i]);

            lstrcatW(verstr, period);
            lstrcatW(verstr, value);
        }

        size += lstrlenW(separator) + lstrlenW(version) + lstrlenW(equals) + lstrlenW(verstr);
    }

    if ((dwDisplayFlags & ASM_DISPLAYF_CULTURE) && (name->culture))
    {
        static const WCHAR neutral[] = {'n','e','u','t','r','a','l', 0};

        cultureval = (lstrlenW(name->culture) == 2) ? name->culture : (LPWSTR) neutral;
        size += lstrlenW(separator) + lstrlenW(culture) + lstrlenW(equals) + lstrlenW(cultureval);
    }

    if ((dwDisplayFlags & ASM_DISPLAYF_PUBLIC_KEY_TOKEN) && (name->haspubkey))
        size += lstrlenW(separator) + lstrlenW(pubkey) + lstrlenW(equals) + CHARS_PER_PUBKEY;

    if ((dwDisplayFlags & ASM_DISPLAYF_PROCESSORARCHITECTURE) && (name->procarch))
        size += lstrlenW(separator) + lstrlenW(procarch) + lstrlenW(equals) + lstrlenW(name->procarch);

    if (size > *pccDisplayName)
        return S_FALSE;

    /* Construct the string */
    lstrcpyW(szDisplayName, name->name);

    if ((dwDisplayFlags & ASM_DISPLAYF_VERSION) && (name->versize > 0))
    {
        lstrcatW(szDisplayName, separator);

        lstrcatW(szDisplayName, version);
        lstrcatW(szDisplayName, equals);
        lstrcatW(szDisplayName, verstr);
    }

    if ((dwDisplayFlags & ASM_DISPLAYF_CULTURE) && (name->culture))
    {
        lstrcatW(szDisplayName, separator);

        lstrcatW(szDisplayName, culture);
        lstrcatW(szDisplayName, equals);
        lstrcatW(szDisplayName, cultureval);
    }

    if ((dwDisplayFlags & ASM_DISPLAYF_PUBLIC_KEY_TOKEN) && (name->haspubkey))
    {
        WCHAR pkt[CHARS_PER_PUBKEY + 1];
        static const WCHAR spec[] = {'%','0','x','%','0','x','%','0','x',
            '%','0','x','%','0','x','%','0','x','%','0','x','%','0','x',0};

        lstrcatW(szDisplayName, separator);

        lstrcatW(szDisplayName, pubkey);
        lstrcatW(szDisplayName, equals);

        wsprintfW(pkt, spec, name->pubkey[0], name->pubkey[1], name->pubkey[2],
            name->pubkey[3], name->pubkey[4], name->pubkey[5], name->pubkey[6],
            name->pubkey[7]);

        lstrcatW(szDisplayName, pkt);
    }

    if ((dwDisplayFlags & ASM_DISPLAYF_PROCESSORARCHITECTURE) && (name->procarch))
    {
        lstrcatW(szDisplayName, separator);

        lstrcatW(szDisplayName, procarch);
        lstrcatW(szDisplayName, equals);
        lstrcatW(szDisplayName, name->procarch);
    }

    *pccDisplayName = size;
    return S_OK;
}