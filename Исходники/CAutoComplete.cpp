/******************************************************************************
 * IAutoComplete_fnInit
 */
HRESULT WINAPI CAutoComplete::Init(HWND hwndEdit, IUnknown *punkACL, LPCOLESTR pwzsRegKeyPath, LPCOLESTR pwszQuickComplete)
{
    TRACE("(%p)->(0x%08lx, %p, %s, %s)\n",
      this, hwndEdit, punkACL, debugstr_w(pwzsRegKeyPath), debugstr_w(pwszQuickComplete));

    if (options & ACO_AUTOSUGGEST)
        TRACE(" ACO_AUTOSUGGEST\n");
    if (options & ACO_AUTOAPPEND)
        TRACE(" ACO_AUTOAPPEND\n");
    if (options & ACO_SEARCH)
        FIXME(" ACO_SEARCH not supported\n");
    if (options & ACO_FILTERPREFIXES)
        FIXME(" ACO_FILTERPREFIXES not supported\n");
    if (options & ACO_USETAB)
        FIXME(" ACO_USETAB not supported\n");
    if (options & ACO_UPDOWNKEYDROPSLIST)
        TRACE(" ACO_UPDOWNKEYDROPSLIST\n");
    if (options & ACO_RTLREADING)
        FIXME(" ACO_RTLREADING not supported\n");

    if (!hwndEdit || !punkACL)
        return E_INVALIDARG;

    if (this->initialized)
    {
        WARN("Autocompletion object is already initialized\n");
        /* This->hwndEdit is set to NULL when the edit window is destroyed. */
        return this->hwndEdit ? E_FAIL : E_UNEXPECTED;
    }

    if (!SUCCEEDED(punkACL->QueryInterface(IID_PPV_ARG(IEnumString,&enumstr))))
    {
        TRACE("No IEnumString interface\n");
        return  E_NOINTERFACE;
    }

    this->hwndEdit = hwndEdit;
    this->initialized = TRUE;
    this->wpOrigEditProc = (WNDPROC)SetWindowLongPtrW(hwndEdit, GWLP_WNDPROC, (LONG_PTR) ACEditSubclassProc);
    /* Keep at least one reference to the object until the edit window is destroyed. */
    this->AddRef();
    SetPropW( this->hwndEdit, autocomplete_propertyW, (HANDLE)this );

    if (options & ACO_AUTOSUGGEST)
    {
        this->CreateListbox();
    }

    if (pwzsRegKeyPath)
    {
        WCHAR *key;
        WCHAR result[MAX_PATH];
        WCHAR *value;
        HKEY hKey = 0;
        LONG res;
        LONG len;

        /* pwszRegKeyPath contains the key as well as the value, so we split */
        key = (WCHAR *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (wcslen(pwzsRegKeyPath) + 1) * sizeof(WCHAR));

        if (key)
        {
            wcscpy(key, pwzsRegKeyPath);
            value = const_cast<WCHAR *>(wcsrchr(key, '\\'));

            if (value)
            {
                *value = 0;
                value++;
                /* Now value contains the value and buffer the key */
                res = RegOpenKeyExW(HKEY_CURRENT_USER, key, 0, KEY_READ, &hKey);
        
                if (res != ERROR_SUCCESS)
                {
                    /* if the key is not found, MSDN states we must seek in HKEY_LOCAL_MACHINE */
                    res = RegOpenKeyExW(HKEY_LOCAL_MACHINE, key, 0, KEY_READ, &hKey);
                }
        
                if (res == ERROR_SUCCESS)
                {
                    len = sizeof(result);
                    res = RegQueryValueW(hKey, value, result, &len);
                    if (res == ERROR_SUCCESS)
                    {
                        quickComplete = (WCHAR *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len * sizeof(WCHAR));
                        wcscpy(quickComplete, result);
                    }
                    RegCloseKey(hKey);
                }
            }

            HeapFree(GetProcessHeap(), 0, key);
        }
        else
        {
            TRACE("HeapAlloc Failed when trying to alloca %d bytes\n", (wcslen(pwzsRegKeyPath) + 1) * sizeof(WCHAR));
            return S_FALSE;
        }
    }

    if ((pwszQuickComplete) && (!quickComplete))
    {
        quickComplete = (WCHAR *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (wcslen(pwszQuickComplete) + 1) * sizeof(WCHAR));

        if (quickComplete)
        {
            wcscpy(quickComplete, pwszQuickComplete);
        }
        else
        {
            TRACE("HeapAlloc Failed when trying to alloca %d bytes\n", (wcslen(pwszQuickComplete) + 1) * sizeof(WCHAR));
            return S_FALSE;
        }
    }

    return S_OK;
}