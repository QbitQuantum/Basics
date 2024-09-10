PLUGIN_EXPORT LPCWSTR GetString(void* data)
{
	static WCHAR result[256];
	wsprintf(result, L"ERROR");
	if (!InitCom() || !pEnumerator)
	{
		UnInitCom();
		wsprintf(result, L"ERROR - Initializing COM");
		return result;
	}

	IMMDevice * pEndpoint = 0;
	if (pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pEndpoint) == S_OK)
	{
		IPropertyStore * pProps = 0;
		if (pEndpoint->OpenPropertyStore(STGM_READ, &pProps) == S_OK)
		{
			PROPVARIANT varName;
			PropVariantInit(&varName);
			if (pProps->GetValue(PKEY_Device_DeviceDesc, &varName) == S_OK)
			{
				wcsncpy(result, varName.pwszVal, 255);
				PropVariantClear(&varName);
				SAFE_RELEASE(pProps)
				SAFE_RELEASE(pEndpoint)
				UnInitCom();
				return result;
			}
			else
			{
				PropVariantClear(&varName);
				SAFE_RELEASE(pProps)
				SAFE_RELEASE(pEndpoint)
				wsprintf(result, L"ERROR - Getting Device Description");
			}
		}
		else
		{
			SAFE_RELEASE(pProps)
			SAFE_RELEASE(pEndpoint)
			wsprintf(result, L"ERROR - Getting Property");
		}
	}
	else
	{
		SAFE_RELEASE(pEndpoint)
		wsprintf(result, L"ERROR - Getting Default Device");
	}

	UnInitCom();
	return result;
}