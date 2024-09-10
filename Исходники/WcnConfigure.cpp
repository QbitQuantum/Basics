HRESULT RunScenario(__in CONFIGURATION_PARAMETERS* configParams)
{
	//common declarations
	UINT status = ERROR_SUCCESS;	
	HRESULT hr = S_OK;
	UINT pinLen = Pin_Length_8;

	//pin needs to be a null terminated ascii char[] for the IWCNDevice::SetPassword function 
	char pin[Pin_Length_8 + 1] = {0};

	
	int result = 0;

	//WCN declarations
	CComPtr<IWCNDevice> pDevice;
	CComObject<WcnConnectNotification>* pWcnConNotif = NULL;	
	CComObject<CWcnFdDiscoveryNotify> * wcnFdDiscoveryNotify = NULL;	

	//Wlan variable declarations
	WCHAR profileBuffer[WCN_API_MAX_BUFFER_SIZE] = {0}; 
	HANDLE wlanHandle = 0;
	DWORD negVersion = 0;
	GUID interfaceGuid = {0};		
	WLAN_INTERFACE_INFO_LIST* pInterfaceList = 0;
	DWORD wlanResult = 0;		
	WLAN_CONNECTION_PARAMETERS connParams;
	ZeroMemory(&connParams,sizeof(connParams));
	WCN_DEVICE_INFO_PARAMETERS WCNDeviceInformation;
	PWSTR pWlanProfileXml = NULL;
	DWORD dwFlags = WLAN_PROFILE_GET_PLAINTEXT_KEY; 


	//The following wlan profile xml is used to configure an unconfigured WCN enabled Router or device.
	//See http://msdn.microsoft.com/en-us/library/bb525370(VS.85).aspx on how to generate a wlan profile.
	//Alternatively, you can read an existing network profile by calling WlanGetProfile.
	WCHAR WCNConnectionProfileTemplate[] =
		L"<?xml version=\"1.0\" ?>"
		L""
		L"<WLANProfile xmlns=\"http://www.microsoft.com/networking/WLAN/profile/v1\">"
		L"    <name>%s</name>"
		L""
		L"    <SSIDConfig>"
		L"        <SSID>"
		L"            <name>%s</name>"
		L"        </SSID>"
		L"    </SSIDConfig>"
		L"    "
		L"    <connectionType>ESS</connectionType>"
		L"    <connectionMode>auto</connectionMode>"
		L""
		L"    <MSM>"
		L"        <security>"
		L"            <authEncryption>"
		L"                <authentication>WPA2PSK</authentication>"
		L"                <encryption>AES</encryption>"
		L"            </authEncryption>"
		L""
		L""
		L"            <sharedKey>"
		L"                <keyType>passPhrase</keyType>"
		L"                <protected>false</protected>"
		L"                <keyMaterial>%s</keyMaterial>"
		L"            </sharedKey>"
		L""
		L"        </security>"
		L"    </MSM>"
		L"</WLANProfile>";


	std::wstring profileXML;

	//open a wlan handle - this will be used later for saving the profile to the system
	status = WlanOpenHandle(
							WLAN_API_VERSION_2_0,
							NULL,
							&negVersion,
							&wlanHandle);

	if (status != ERROR_SUCCESS)
	{
		wprintf(L"\nERROR: WlanOpenHandle failed with the following error code [%d]", status);
		hr = S_FALSE;
		goto cleanup;
	}

	// Get the first wlan device
	// ideally you would want to be able to choose the wireless device you want to use
	status = WlanEnumInterfaces(
								wlanHandle,
								NULL,
								&pInterfaceList);

	if(status != ERROR_SUCCESS)
	{				
		wprintf(L"\nERROR: WlanEnumInterfaces failed with the following error code [0x%d]",status);
		hr = S_FALSE;
		goto cleanup;		
	}

	//Make sure there is at least one wlan interface on the system
	if (pInterfaceList == 0 || pInterfaceList->dwNumberOfItems == 0)
	{
		wprintf(L"\nERROR: No wireless network adapters on the system");
		hr = S_FALSE;
		goto cleanup;
	}

	//get the wlan interface GUID
	interfaceGuid = pInterfaceList->InterfaceInfo[0].InterfaceGuid;

	//Create an instance of the IWCNConnectNotify Interface
	hr = CComObject<WcnConnectNotification>::CreateInstance(&pWcnConNotif);
	if (hr != S_OK)
	{
		wprintf(L"\nERROR: Creating an instance of WcnConnectNotification failed with the following error hr=[0x%x]", hr);
		goto cleanup;
	}
	pWcnConNotif->AddRef();

	hr = CComObject<CWcnFdDiscoveryNotify>::CreateInstance(&wcnFdDiscoveryNotify);
	if (hr != S_OK)
	{
		wprintf(L"\nERROR: Creating an instance of CWcnFdDiscoveryNotify failed with the following error hr=[0x%x]", hr);
		goto cleanup;
	}
	wcnFdDiscoveryNotify->AddRef();

	//initialize WcnConnectNotification
	hr = pWcnConNotif->Init();
	if(hr !=S_OK)
	{
		wprintf(L"\nERROR: Creating a connection notification event failed with the following error hr=[0x%x]", hr);
		goto cleanup;
	}

	//initialize CWcnFdDiscoveryNotify 
	hr = wcnFdDiscoveryNotify->Init(configParams->bTurnOnSoftAP);
	if(hr != S_OK)
	{
		wprintf(L"\nERROR: Initializing Function Discovery notify failed with the following error hr=[0x%x].",hr);
		goto cleanup;
	}

	//Search for WCN device with function discovery
	hr = wcnFdDiscoveryNotify->WcnFDSearchStart(&configParams->pDeviceUUID, configParams->pSearchSSID);		
	if(hr != S_OK)
	{
		wprintf(L"\nERROR: Function Discovery search failed to start with the following error hr=[0x%x].",hr);
		goto cleanup;
	}

	//Wait for Function Discovery to complete
	wcnFdDiscoveryNotify->WaitForAnyDiscoveryEvent(Discovery_Event_Wait_Time_MS);

	//Attempt to get the IWCNDevice instance
	if(wcnFdDiscoveryNotify->GetWCNDeviceInstance(&pDevice))
	{
		//get information about the device from the IWCNDevice instance
		wprintf(L"\nINFO: The following Device was found by Function Discovery.");
		hr = GetWCNDeviceInformation(pDevice, &WCNDeviceInformation);
		if (hr != S_OK)
		{
			wprintf(L"\nERROR: Failed to get the Device information from the IWCNDevice Instance, hr=[0x%x]", hr);
			goto cleanup;
		}
	}
	else
	{
		wprintf(L"\nERROR: Device was NOT found by Function Discovery.");
		hr = S_FALSE;
		goto cleanup;
	}
	
	

	//The following segment generates a WLAN profile from the template above then saves it to the
	//WLAN store. It the retrieves the profile from the WLAN store for use in configuring a router
	//or device.
	if (configParams->enumConfigScenario != PCConfigPin 
		&& configParams->enumConfigScenario != PCConfigPushButton)
	{
		//add the profiles ssid and passphrase to the wlan profile template
		swprintf_s(
				profileBuffer, 
				WCNConnectionProfileTemplate, 
				configParams->pProfileSSID, 
				configParams->pProfileSSID, 
				configParams->pProfilePassphrase);


		//Add the created profile to the wlan store
		status = WlanSetProfile(
								wlanHandle, 
								&interfaceGuid, 
								0,				//all-user profile
								profileBuffer, 
								NULL,			// Default Security - All user profile
								TRUE,			// Overwrite profile
								NULL,			// reserved
								&wlanResult);

		if (status != ERROR_SUCCESS)
		{
			wprintf(L"\nERROR: Failed to save the profile return code was [0x%x]", wlanResult);
			hr = S_FALSE;
			goto cleanup;
		}
		else
		{
			wprintf(L"\nINFO: Successfully saved the profile to the wlan store");
		}

		//Here is where the profile is retrieved from the wlan store to be used in the configuration
		//of the device.  
		//If so desired a list of available profiles could be presented to the user so that 
		//they could decied which profile will be used to configure the device
		//The wlan profile must be retrieved in plain text inorder for the IWCNDEVICE::SetNetWorkProfile
		// method to succeede.  In order to do this you need to be elevated to get the wlan profile
		// in plain text.
		status = WlanGetProfile(
								wlanHandle,
								&interfaceGuid,
								configParams->pProfileSSID,
								NULL,						//reserved
								&pWlanProfileXml,
								&dwFlags,					// Flags - get profile in plain text 
								NULL);						// GrantedAccess - none

		if (status != ERROR_SUCCESS)
		{
			wprintf(L"\nERROR: WlanGetprofile Failed to get profile [%s] with error code [0x%x]", configParams->pProfileSSID, status);
			hr = S_FALSE;
			goto cleanup;
		}
		else
		{
			wprintf(L"\nINFO: Successfully retrieved profile [%s] from the wlan store.", configParams->pProfileSSID);
		}

		//check to make sure the profile from the wlan store is not a Group Policy profile
		if (WLAN_PROFILE_GROUP_POLICY & dwFlags)
		{
			wprintf(L"\nERROR: Profile [%s] is a group policy WLAN profile which is not supported by WCN", configParams->pProfileSSID);
			hr = S_FALSE;
			goto cleanup;
		}


		//The IWCNDevice::SetNetworkProfile method queues an XML WLAN profile to be 
		//provisioned to the device. This method may only be called prior to IWCNDevice::Connect.
		hr = pDevice->SetNetworkProfile(pWlanProfileXml);
		if(hr != S_OK)
		{
			wprintf(L"\nERROR: IWCNDevice::SetNetworkProfile failed with error code [0x%x]", hr);
			goto cleanup;
		}
		else
		{				
			wprintf(L"\nINFO: IWCNDevice::SetNetworkProfile() succeeded with result [0x%x]", hr);
		}
	}
	
	switch (configParams->enumConfigScenario)
	{
		case DeviceConfigPushButton:
			
			pinLen = 0;
			break;

		case DeviceConfigPin:
		case RouterConfig:
			if (configParams->pDevicePin == 0)
			{
				wprintf(L"\nERROR: Pin must not be 0 when doing a pin configuration");
				hr = S_FALSE;
				goto cleanup;
			}


			 result = WideCharToMultiByte(
							CP_UTF8,
							0,
							configParams->pDevicePin,
							-1,
							(LPSTR)pin,
							sizeof(pin),
							NULL,
							NULL);
			if (result == 0 )
			{
				wprintf(L"\nERROR: Failed to convert the pin to multibyte.");
				goto cleanup;
			}


			pinLen = sizeof(pin) - 1 ;
			break;

		case PCConfigPushButton:
			//check to make sure the device supports push button before doing the push button configuration
			if (WCNDeviceInformation.uConfigMethods & WCN_VALUE_CM_PUSHBUTTON) 
			{
				//set the pin length to 0 this is necessary for a Push button configuration scenario				
				pinLen = 0;
			}
			else
			{
				wprintf(L"ERROR: The [%s] device does not support the Push Button Method", WCNDeviceInformation.wszDeviceName);
				hr = S_FALSE;
				goto cleanup;
			}
			break;
			
		case PCConfigPin:
			//check to make sure the device supports pin before doing the pin configuration
			if ((WCNDeviceInformation.uConfigMethods & WCN_VALUE_CM_LABEL)|| 
				(WCNDeviceInformation.uConfigMethods & WCN_VALUE_CM_DISPLAY))
			{
				if (configParams->pDevicePin == 0)
				{
					wprintf(L"\nERROR: Pin must not be 0 when doing a pin configuration");
					hr = S_FALSE;
					goto cleanup;
				}
			
				result = WideCharToMultiByte(
							CP_UTF8,					//CodePage
							0,							//Unmapped character flags
							configParams->pDevicePin,
							-1,							//null terminated string
							(LPSTR)pin,
							sizeof(pin),
							NULL,						//lpDefaultChar - use system default value
							NULL);						//lpUsedDefaultChar ignored
				if (result == 0 )
				{
					wprintf(L"\nERROR: Failed to convert the pin to multibyte.");
					goto cleanup;
				}

				pinLen = sizeof(pin) - 1 ;

			}
			else
			{
				wprintf(L"\nERROR: The [%s] device does not supprot the pin method", WCNDeviceInformation.wszDeviceName);
				hr = S_FALSE;
				goto cleanup;
			}
			break;

		default:
			break;
	}
	
	//The IWCNDevice::SetPassword method configures the authentication method value, and if required, 
	//a password used for the pending session. This method may only be called prior to IWCNDevice::Connect.
	hr = pDevice->SetPassword(
								configParams->enumConfigType, 
								pinLen,
								(BYTE*)pin);

	if(hr != S_OK)
	{	
		wprintf(L"\nERROR: IWCNDevice::SetPassword failed with error code [0x%x]", hr);
		goto cleanup;
	}
	else
	{
		wprintf(L"\nINFO: IWCNDevice::SetPassword succeeded with result [0x%x]", hr);
	}


	//The IWCNDevice::Connect method initiates the session.
	hr = pDevice->Connect(pWcnConNotif);
	if(hr != S_OK)
	{
		//Device Push button configuration is only supported on SoftAP capable wireless Nics 
		if (hr == HRESULT_FROM_WIN32(ERROR_CONNECTION_UNAVAIL) 
			&& 	configParams->enumConfigScenario == DeviceConfigPushButton)
		{
			wprintf(L"\nERROR: PushButton Configuration of non AP devices is only supported on");
			wprintf(L"\n       SoftAP capable wireless network cards.");
		}
		else
		{
			wprintf(L"\nERROR: IWCNDevice::Connect failed with error code [0x%x]", hr);
		}
		goto cleanup;
	}
	else
	{
		wprintf(L"\nINFO: IWCNDevice::Connect succeeded with result [0x%x]", hr);
	}

	//wait for the configuration result
	hr = pWcnConNotif->WaitForConnectionResult();
	if (hr != S_OK)
	{
		wprintf(L"ERROR: WaitforconnectionResult returned the following error [ox%x]", hr);
		goto cleanup;
	}

	//check to see which connection callbacks were called
	if(pWcnConNotif->connectSucceededCallBackInvoked)
	{
		wprintf(L"\nINFO: IWCNConnectNotify::ConnectSucceeded was invoked");		
	}
	else if(pWcnConNotif->connectFailedCallBackInvoked)
	{
		wprintf(L"\nERROR: IWCNConnectNotify::ConnectFailed was invoked");
		hr = S_FALSE;
		goto cleanup;
	}

	
	//save the profile from the IWCNDevice instance to the WLAN store if doing a PCConfigPushButton 
	//or a PCConfigPin scenario

	// this is the profile that was received from the router
	if (configParams->enumConfigScenario == PCConfigPushButton  || configParams->enumConfigScenario == PCConfigPin)
	{	
		//The IWCNDevice::GetNetworkProfile method gets a network profile from the device.
		hr = pDevice->GetNetworkProfile(ARRAYSIZE(profileBuffer), profileBuffer);		
		if(hr != S_OK)
		{
			wprintf(L"\nERROR: IWCNDevice::GetNetworkProfile failed with  [0x%x]", hr);
			goto cleanup;
		}

		//save the profile to the system if doing a RouterConfig or a pushbutton scenario
		//The SoftapConfig and DeviceConfig scenarios will generally use a profile that is already on the system
		//save the profile to the wlan interface			
		status = WlanSetProfile(
								wlanHandle, 
								&interfaceGuid, 
								0,				//Flags - none
								profileBuffer, 
								NULL,			// Default Security - All user profile
								TRUE,			// Overwrite profile
								NULL,			// reserved
								&wlanResult);

		if (status != ERROR_SUCCESS)
		{
			wprintf(L"\nERROR: Failed to save the profile to the WLAN store, return code was [0x%x]", wlanResult);
			hr = S_FALSE;
		}
		else
		{
			wprintf(L"\nINFO: Successfully saved the profile to the WLAN store");
		}
	}
	
	//Display the SSID and passphrase used to configure the Router or device
	if (configParams->enumConfigScenario != PCConfigPin && configParams->enumConfigScenario != PCConfigPushButton)
	{
		wprintf(L"\nINFO: Profile SSID Used: [%s]", configParams->pProfileSSID);
		wprintf(L"\nINFO: Profile Passphrase Used: [%s]", configParams->pProfilePassphrase);
	}

cleanup:

	if(pWcnConNotif)
	{
		pWcnConNotif->Release();
		pWcnConNotif = 0;
	}

	if(wcnFdDiscoveryNotify)
	{
		wcnFdDiscoveryNotify->Release();
		wcnFdDiscoveryNotify = 0;
	}

	if (wlanHandle != NULL)
	{
		WlanCloseHandle(wlanHandle,NULL);
	}

	if (pInterfaceList != NULL)
	{
		WlanFreeMemory(pInterfaceList);
	}

	return hr;
}