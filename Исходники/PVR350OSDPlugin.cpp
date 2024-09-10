/*
 * Class:     sage_PVR350OSDRenderingPlugin
 * Method:    openOSD0
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_sage_PVR350OSDRenderingPlugin_openOSD0
  (JNIEnv *env, jobject jo)
{
	CoInitializeEx(NULL, COM_THREADING_MODE);
	HRESULT hr;
	slog((env, "BVF open350OSD0 called\r\n"));
	PVR350OSDPluginNativeData rv;
	ZeroMemory(&rv, sizeof(PVR350OSDPluginNativeData));
	rv.ntscModeFor350 = 1;
	// We can't load this by the GUID just like some of the KS CC stuff
    ICreateDevEnum *pSysDevEnum = NULL;
    IEnumMoniker *pEnum = NULL;
    IMoniker *pMoniker = NULL;
    hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, 
        CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
        (void**)&pSysDevEnum);
	if (FAILED(hr)) return 0;
    hr = pSysDevEnum->CreateClassEnumerator(KSCATEGORY_DATADECOMPRESSOR, &pEnum, 0);
	if (hr != S_OK)
	{
		// Nothing to enumerate
		SAFE_RELEASE(pSysDevEnum);
		return hr;
	}
    while (S_OK == pEnum->Next(1, &pMoniker, NULL))
    {
        IPropertyBag *pPropBag = NULL;
        hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag, 
                                (void **)&pPropBag);
		if (SUCCEEDED(hr))
		{
			VARIANT var;
			VariantInit(&var);
			hr = pPropBag->Read(L"FriendlyName", &var, 0);
			if (SUCCEEDED(hr))
			{
				char conv[512];
				WideCharToMultiByte(CP_ACP, 0, var.bstrVal, -1, conv, 512, 0, 0);
				if (strstr(conv, "PVR"))
				{
        			hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter,
        				(void**)(&(rv.pOSD)));
        			if (SUCCEEDED(hr))
					{
						VariantClear(&var);
						SAFE_RELEASE(pPropBag);
						SAFE_RELEASE(pMoniker);
						break;
					}
				}
			}
			VariantClear(&var);
		}
        SAFE_RELEASE(pPropBag);
        SAFE_RELEASE(pMoniker);
    }

    SAFE_RELEASE(pSysDevEnum);
    SAFE_RELEASE(pEnum);
	if (rv.pOSD)
	{
		hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
			IID_IGraphBuilder, (void **)&(rv.pGraph));
		TEST_AND_BAIL
		if (!rv.mutex350OSD)
		{
			rv.mutex350OSD = CreateMutex(NULL, FALSE, "Global\\SageTV350Sync");
			WaitForSingleObject(rv.mutex350OSD, MUTEX350WAITTIME);
		}
		hr = rv.pGraph->AddFilter(rv.pOSD, L"OSD");
		if (FAILED(hr))
		{
			SAFE_RELEASE(rv.pOSD);
			SAFE_RELEASE(rv.pGraph);
			ReleaseMutex(rv.mutex350OSD);
			CloseHandle(rv.mutex350OSD);
			elog((env, "Error opening 350 OSD hr=0x%x\r\n", hr));
			return 0;
		}
		DWORD holder;
		HKEY myKey;
		DWORD readType;
		DWORD hsize = sizeof(holder);
		if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Frey Technologies\\Common", 0, 0,
			REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, 0, &myKey, 0) == ERROR_SUCCESS)
		{
			if (RegQueryValueEx(myKey, "NTSC", 0, &readType, (LPBYTE) &holder, &hsize) == ERROR_SUCCESS)
			{
				rv.ntscModeFor350 = holder;
			}
			else
			{
				RegSetValueEx(myKey, "NTSC", 0, REG_DWORD, (LPBYTE) &(rv.ntscModeFor350), sizeof(rv.ntscModeFor350));
			}

			RegCloseKey(myKey);
		}

		PVR350OSDPluginNativeData* realRV = new PVR350OSDPluginNativeData;
		memcpy(realRV, &rv, sizeof(PVR350OSDPluginNativeData));
		if (Print350OSDInfo(realRV, env, TRUE))
		{
			ReleaseMutex(realRV->mutex350OSD);
			return (jlong) realRV;
		}
		else
		{
			ReleaseMutex(realRV->mutex350OSD);
			Java_sage_PVR350OSDRenderingPlugin_closeOSD0(env, jo, (jlong)realRV);
			return 0;
		}
	}