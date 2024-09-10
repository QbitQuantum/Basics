	inline HRESULT RegisterAppId(bool bService = false) throw()
	{
		if (!Uninstall())
			return E_FAIL;

		HRESULT hr = UpdateRegistryAppId(TRUE);
		if (FAILED(hr))
			return hr;

		CRegKey keyAppID;
		LONG lRes = keyAppID.Open(HKEY_CLASSES_ROOT, _T("AppID"), KEY_WRITE);
		if (lRes != ERROR_SUCCESS)
			return AtlHresultFromWin32(lRes);

		CRegKey key;

		lRes = key.Create(keyAppID, GetAppIdT());
		if (lRes != ERROR_SUCCESS)
			return AtlHresultFromWin32(lRes);

		key.DeleteValue(_T("LocalService"));

		if (!bService)
			return S_OK;

		key.SetStringValue(_T("LocalService"), m_szServiceName);

		// change LaunchACL and AccessACL,so that no "Administrator" privileges is need.
		//S-1-5-32-545 is USERS's SID
		TCHAR szUsersSID[] = _T("S-1-5-32-545");
		DWORD error = ChangeAppIDLaunchACL(GetAppIdT(),szUsersSID,true,true,COM_RIGHTS_ACTIVATE_LOCAL);
		if(error){
			DebugOutF(filelog::log_error,"ChangeAppIDLaunchACL failed with %d",error);
		}
		error = ChangeAppIDAccessACL(GetAppIdT(),szUsersSID,true,true,COM_RIGHTS_EXECUTE_LOCAL);
		
		if(error){
			DebugOutF(filelog::log_error,"ChangeAppIDAccessACL failed with %d",error);
		}

		// Create service
		if (!Install())
			return E_FAIL;
		return S_OK;
	}