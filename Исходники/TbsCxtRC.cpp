BOOL CALLBACK dialogProc (HWND hwnd, 
                          UINT message, 
                          WPARAM wParam, 
                          LPARAM lParam)
{
	USES_CONVERSION;	
    switch (message) {

		case WM_INITDIALOG: {
			CoInitializeEx(NULL,COINIT_MULTITHREADED);
			{
				int numberOfDevices=0;
				SendDlgItemMessage(hwnd,IDC_COMBO_DEVID,CB_RESETCONTENT,0,0);

				// create system device enumerator
				CComPtr <ICreateDevEnum>	pSysDevEnum = NULL;	
				HRESULT hr = pSysDevEnum.CoCreateInstance(CLSID_SystemDeviceEnum);
				if (hr == S_OK)
				{
					// create a class enumerator for the desired category defined by classGuid.
					CComPtr <IEnumMoniker> pEnumCat = NULL;	//moniker enumerator for filter categories
					hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEnumCat, 0);
					if (hr == S_OK)
					{

						// reset the enumeration
						pEnumCat->Reset();

						// now iterate through enumeration
						ULONG cFetched = 0;
						CComPtr <IMoniker> pMoniker = NULL;

						// get a pointer to each moniker
						while(pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
						{
							//get a pointer to property bag (which has filter)
							IPropertyBag* pPropBag = NULL;	
							if (pMoniker->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pPropBag) != S_OK)
								break;

							char szFriendlyName[MAX_PATH];

							CComPtr <IBaseFilter> pFilter = NULL;
							// create an instance of the filter
							hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pFilter);
							if (hr == S_OK)
							{							
								VARIANT varName;
								// retrieve the friendly name of the filter
								VariantInit(&varName);
								hr = pPropBag->Read(L"FriendlyName", &varName, 0);
								WideCharToMultiByte(CP_ACP, 0, varName.bstrVal, -1, szFriendlyName, sizeof(szFriendlyName), 0, 0);
								VariantClear(&varName);

								CComPtr <IKsPropertySet> pKsVCPropSet = NULL;
								// query for interface
								hr = pFilter->QueryInterface(IID_IKsPropertySet, (void **)&pKsVCPropSet);
								if (pKsVCPropSet)
								{
									DWORD type_support;
									hr = pKsVCPropSet->QuerySupported(KSPROPSETID_CustomIRCaptureProperties,
										KSPROPERTY_IRCAPTURE_COMMAND,
										&type_support);
									if ( SUCCEEDED(hr) && (type_support & KSPROPERTY_SUPPORT_SET) )
									{
										PCHAR t=strstr(szFriendlyName,"Video Capture");
										if (t) *t=0;
										SendDlgItemMessage(hwnd,IDC_COMBO_DEVID,CB_ADDSTRING,0,(LPARAM)szFriendlyName);
										numberOfDevices++;
									}
								}
							}
							pMoniker.Release();
						}
					}
				}
			
				if (settings.getDeviceNumber()>=numberOfDevices)
					settings.setDeviceNumber(0);

				if (numberOfDevices == 0)
					SendDlgItemMessage(hwnd,IDC_COMBO_DEVID,CB_ADDSTRING,0,(LPARAM)"NO DEVICE");

				SendDlgItemMessage(hwnd,IDC_COMBO_DEVID,CB_SETCURSEL,settings.getDeviceNumber(),0);

				ShowWindow(hwnd, SW_SHOW);
			}

			CoUninitialize ();

			return TRUE;
		}

		case WM_COMMAND: {
			switch(LOWORD(wParam)) {
				case IDOK: {
					settings.setDeviceNumber(SendDlgItemMessage(hwnd,IDC_COMBO_DEVID,CB_GETCURSEL,0,0));
					settings.saveSettings();
					DestroyWindow (hwnd);
					return TRUE;
				}

				case IDCANCEL: {
					DestroyWindow (hwnd);
					return TRUE;
				}

			}
			return FALSE;
		}

		case WM_DESTROY:
			PostQuitMessage(0);
			return TRUE;
		case WM_CLOSE:
			DestroyWindow (hwnd);
			return TRUE;
	}

    return FALSE;

}