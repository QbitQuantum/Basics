bool _GetDescription(ISpObjectToken *p_token, WCHAR **r_description)
{
	typedef HRESULT (WINAPI *_RegLoadMUIStringWPtr)(HKEY, LPCWSTR, LPWSTR, DWORD, LPDWORD, DWORD, LPCWSTR);
	static HMODULE s_advapi32 = NULL;
	static _RegLoadMUIStringWPtr s_RegLoadMUIStringW = NULL;

	if (s_advapi32 == NULL)
	{
		// Attempt to load function RegLoadMUIStringW which should be available if we're running on Vista & later
        s_advapi32 = LoadLibraryA("advapi32.dll");
        if(s_advapi32 != NULL)
			s_RegLoadMUIStringW = (_RegLoadMUIStringWPtr)GetProcAddress(s_advapi32, "RegLoadMUIStringW");
	}

	bool t_success = true;

    if (r_description == NULL)
    {
        return false;
    }

	WCHAR *t_description = NULL;

    if(s_RegLoadMUIStringW != NULL)
    {
		WCHAR* t_path = NULL;
		WCHAR* t_reg_key = NULL;
		HKEY   t_hkey = NULL;

        t_success = SUCCEEDED(p_token->GetId(&t_reg_key));

        if (t_success)
        {
			// Split the path & base of the registry key - path is invalid if there is no separator
            t_path = wcschr(t_reg_key, L'\\');
			t_success = t_path != NULL;
		}
        if(t_success)
        {
            *t_path++ = L'\0';

            if (wcscmp(t_reg_key, L"HKEY_LOCAL_MACHINE") == 0)
				t_success = ERROR_SUCCESS == RegOpenKeyExW(HKEY_LOCAL_MACHINE, t_path, 0, KEY_QUERY_VALUE, &t_hkey);
            else if (wcscmp(t_reg_key, L"HKEY_CURRENT_USER") == 0)
                t_success = ERROR_SUCCESS == RegOpenKeyExW(HKEY_CURRENT_USER, t_path, 0, KEY_QUERY_VALUE, &t_hkey);
            else
				t_success = false;
            
			DWORD t_size = 0;
            if (t_success)
				t_success = ERROR_MORE_DATA == s_RegLoadMUIStringW(t_hkey, L"Description", NULL, 0, &t_size, 0, NULL);
			if (t_success)
				t_success = NULL != (t_description = (WCHAR*) CoTaskMemAlloc(t_size));
			if (t_success)
                t_success = ERROR_SUCCESS == s_RegLoadMUIStringW(t_hkey, L"Description", t_description, t_size, NULL, 0, NULL);
        }

		// Cleanup
        if(t_hkey)
            RegCloseKey(t_hkey);
        if(t_reg_key)
            CoTaskMemFree(t_reg_key);

		if (!t_success && t_description != NULL)
		{
			CoTaskMemFree(t_description);
			t_description = NULL;
		}
    }

    // fetch from the registry - if all else fails, fallback to the default attribute
	if (s_RegLoadMUIStringW == NULL || !t_success)
    {
	    WCHAR t_lang_id[10];

		if (_ultow_s(GetUserDefaultUILanguage(), t_lang_id, 9, 16))
		{
			t_lang_id[0] = L'0';
			t_lang_id[1] = 0;
		}

		HRESULT hr;
        hr = p_token->GetStringValue(t_lang_id, &t_description);
        if (hr == SPERR_NOT_FOUND)
        {
            hr = p_token->GetStringValue(NULL, &t_description);
        }
		t_success = SUCCEEDED(hr);
    }

	if (t_success)
		*r_description = t_description;

    return t_success;
}