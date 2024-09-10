    PluginSettings(
#ifdef FAR3
        FARAPISETTINGSCONTROL settingsControl, const GUID &guid)
    {
        SettingsControl = settingsControl;
	handle = INVALID_HANDLE_VALUE;

	FarSettingsCreate settings = {sizeof settings,guid,handle};
	if(SettingsControl(INVALID_HANDLE_VALUE,SCTL_CREATE,PSL_ROAMING,&settings))
	    handle = settings.Handle;
#else
        bool bWrite)
    {
        extern TCHAR PluginRootKey[];
        DWORD disp;
        if((bWrite ?
            RegCreateKeyEx(HKEY_CURRENT_USER, PluginRootKey, 0, 0, 0, KEY_WRITE|KEY_READ, 0, &hKey, &disp) :
            RegOpenKeyEx(HKEY_CURRENT_USER, PluginRootKey, 0, KEY_READ, &hKey))
                !=ERROR_SUCCESS)
                hKey = 0;
#endif
    }

    ~PluginSettings()
    {
#ifdef FAR3
	SettingsControl(handle,SCTL_FREE,0,0);
#else
        for each(HKEY hk in subKeys) //for(HKEY hk : subKeys) after moving to a newer VC
            RegCloseKey(hk);
        subKeys.clear();
        if(hKey)
            RegCloseKey(hKey);
        hKey = 0;
#endif
    }

    KEY_TYPE CreateSubKey(PCWSTR Name, KEY_TYPE root = 0)
    {
#ifdef FAR3
	FarSettingsValue value = {sizeof value, root, Name};
	return (KEY_TYPE)SettingsControl(handle,SCTL_CREATESUBKEY,0,&value);
#else
        if(root == 0) root = hKey;
        HKEY hk;
        if(RegCreateKeyW(root, Name, &hk) != ERROR_SUCCESS)
            return 0;
        subKeys.push_back(hk);
        return hk;
#endif
    }