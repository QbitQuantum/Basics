/******************************************************************************
 * IAutoComplete_fnInit
 */
static HRESULT WINAPI IAutoComplete_fnInit(
    IAutoComplete * iface,
    HWND hwndEdit,
    IUnknown *punkACL,
    LPCOLESTR pwzsRegKeyPath,
    LPCOLESTR pwszQuickComplete)
{
    IAutoCompleteImpl *This = (IAutoCompleteImpl *)iface;
    static const WCHAR lbName[] = {'L','i','s','t','B','o','x',0};

    TRACE("(%p)->(0x%08lx, %p, %s, %s)\n", 
	  This, (long)hwndEdit, punkACL, debugstr_w(pwzsRegKeyPath), debugstr_w(pwszQuickComplete));

    if (This->options & ACO_AUTOSUGGEST) TRACE(" ACO_AUTOSUGGEST\n");
    if (This->options & ACO_AUTOAPPEND) TRACE(" ACO_AUTOAPPEND\n");
    if (This->options & ACO_SEARCH) FIXME(" ACO_SEARCH not supported\n");
    if (This->options & ACO_FILTERPREFIXES) FIXME(" ACO_FILTERPREFIXES not supported\n");
    if (This->options & ACO_USETAB) FIXME(" ACO_USETAB not supported\n");
    if (This->options & ACO_UPDOWNKEYDROPSLIST) TRACE(" ACO_UPDOWNKEYDROPSLIST\n");
    if (This->options & ACO_RTLREADING) FIXME(" ACO_RTLREADING not supported\n");

    This->hwndEdit = hwndEdit;

    if (!SUCCEEDED (IUnknown_QueryInterface (punkACL, &IID_IEnumString, (LPVOID*)&This->enumstr))) {
	TRACE("No IEnumString interface\n");
	return  E_NOINTERFACE;
    }

    This->wpOrigEditProc = (WNDPROC) SetWindowLongPtrW( hwndEdit, GWLP_WNDPROC, (LONG_PTR) ACEditSubclassProc);
    SetWindowLongPtrW( hwndEdit, GWLP_USERDATA, (LONG_PTR)This);

    if (This->options & ACO_AUTOSUGGEST) {
	HWND hwndParent;

	hwndParent = GetParent(This->hwndEdit);
	
	/* FIXME : The listbox should be resizable with the mouse. WS_THICKFRAME looks ugly */
	This->hwndListBox = CreateWindowExW(0, lbName, NULL, 
					    WS_BORDER | WS_CHILD | WS_VSCROLL | LBS_HASSTRINGS | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT, 
					    CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
					    hwndParent, NULL, 
					    (HINSTANCE)GetWindowLongPtrW( hwndParent, GWLP_HINSTANCE ), NULL);
					    
	if (This->hwndListBox) {
	    This->wpOrigLBoxProc = (WNDPROC) SetWindowLongPtrW( This->hwndListBox, GWLP_WNDPROC, (LONG_PTR) ACLBoxSubclassProc);
	    SetWindowLongPtrW( This->hwndListBox, GWLP_USERDATA, (LONG_PTR)This);
	}
    }

    if (pwzsRegKeyPath) {
	WCHAR *key;
	WCHAR result[MAX_PATH];
	WCHAR *value;
	HKEY hKey = 0;
	LONG res;
	LONG len;

	/* pwszRegKeyPath contains the key as well as the value, so we split */
	key = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (lstrlenW(pwzsRegKeyPath)+1)*sizeof(WCHAR));
	strcpyW(key, pwzsRegKeyPath);
	value = strrchrW(key, '\\');
	*value = 0;
	value++;
	/* Now value contains the value and buffer the key */
	res = RegOpenKeyExW(HKEY_CURRENT_USER, key, 0, KEY_READ, &hKey);
	if (res != ERROR_SUCCESS) {
	    /* if the key is not found, MSDN states we must seek in HKEY_LOCAL_MACHINE */
	    res = RegOpenKeyExW(HKEY_LOCAL_MACHINE, key, 0, KEY_READ, &hKey);  
	}
	if (res == ERROR_SUCCESS) {
	    res = RegQueryValueW(hKey, value, result, &len);
	    if (res == ERROR_SUCCESS) {
		This->quickComplete = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len*sizeof(WCHAR));
		strcpyW(This->quickComplete, result);
	    }
	    RegCloseKey(hKey);
	}
	HeapFree(GetProcessHeap(), 0, key);
    }

    if ((pwszQuickComplete) && (!This->quickComplete)) {
	This->quickComplete = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (lstrlenW(pwszQuickComplete)+1)*sizeof(WCHAR));
	lstrcpyW(This->quickComplete, pwszQuickComplete);
    }

    return S_OK;
}