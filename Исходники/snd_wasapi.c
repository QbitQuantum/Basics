static qboolean QDECL WASAPI_Enumerate (void (QDECL *callback) (const char *drivername, const char *devicecode, const char *readablename))
{
	FORCE_DEFINE_PROPERTYKEY(PKEY_Device_FriendlyName,           0xa45c254e, 0xdf1c, 0x4efd, 0x80, 0x20, 0x67, 0xd1, 0x46, 0xa8, 0x50, 0xe0, 14);    // DEVPROP_TYPE_STRING

	static IMMDeviceEnumerator *pEnumerator = NULL;
	IMMDeviceCollection *pCollection = NULL;
	CoInitialize(NULL);
	if (!pEnumerator)
	{
		if (SUCCEEDED(CoCreateInstance(&CLSID_MMDeviceEnumerator, NULL, CLSCTX_ALL, &IID_IMMDeviceEnumerator, (void**)&pEnumerator)))
		{
			pEnumerator->lpVtbl->RegisterEndpointNotificationCallback(pEnumerator, &WASAPI_Notifications);
		}
	}

	if (pEnumerator)
	{
		if (SUCCEEDED(pEnumerator->lpVtbl->EnumAudioEndpoints(pEnumerator, eRender, DEVICE_STATE_ACTIVE, &pCollection)))
		{
			IMMDevice *pEndpoint;
			IPropertyStore *pProps;
			LPWSTR pwszID;
			UINT count, i;
			if (FAILED(pCollection->lpVtbl->GetCount(pCollection, &count)))
				count = 0;
			for (i = 0; i < count; i++)
			{
				if (SUCCEEDED(pCollection->lpVtbl->Item(pCollection, i, &pEndpoint)))
				{
					if (SUCCEEDED(pEndpoint->lpVtbl->GetId(pEndpoint, &pwszID)))
					{
						if (SUCCEEDED(pEndpoint->lpVtbl->OpenPropertyStore(pEndpoint, STGM_READ, &pProps)))
						{
							PROPVARIANT varName;
							PropVariantInit(&varName);
							if (SUCCEEDED(pProps->lpVtbl->GetValue(pProps, &PKEY_Device_FriendlyName, &varName)))
							{
								char nicename[256];
								char internalname[256];
								strcpy(nicename, AUDIODRIVERNAME ": ");
								narrowen(nicename+strlen(AUDIODRIVERNAME)+2, sizeof(nicename)-(strlen(AUDIODRIVERNAME)+2), varName.pwszVal);
								narrowen(internalname, sizeof(internalname), pwszID);
								callback(AUDIODRIVERNAME, internalname, nicename);
							}
							PropVariantClear(&varName);
							pProps->lpVtbl->Release(pProps);
						}
						CoTaskMemFree(pwszID);
					}
					pEndpoint->lpVtbl->Release(pEndpoint);
				}
			}

			pCollection->lpVtbl->Release(pCollection);
		}

//		pEnumerator->lpVtbl->Release(pEnumerator);
//		pEnumerator = NULL;
		return true;
	}
	return true;	//if we couldn't enumerate stuff, we won't be able to initialise anything anyway, so there's no point in doing any default device crap
}