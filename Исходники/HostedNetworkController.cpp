//Performs legwork of configuring and starting the wireless hosted network
bool HostedNetworkController::initialize(QString networkName, QString networkPassword)
{

	/* Create variables to receive the result of Wlan API calls */

	HRESULT result;													//HRESULT to store the return value 
	PWLAN_HOSTED_NETWORK_REASON pHostedNetworkFailReason = nullptr;	//Pointer to the specific call failure reason
	DWORD negotiatedVersion = 0;									//DWORD for the Wlan API to store the negotiated API version in

	if (wlanHandle == 0)
	{
		/* Open a handle to the Wlan API */

		DWORD negotiatedVersion = 0;					//DWORD for the Wlan API to store the negotiated API version in
		result = WlanOpenHandle(
			WLAN_API_VERSION_2_0,						//Request API version 2.0
			nullptr,									//Reserved
			&negotiatedVersion,							//Address of the DWORD to store the negotiated version
			&wlanHandle									//Address of the HANDLE to store the Wlan handle
			);

		if (result != NO_ERROR)
		{
			/* Something went wrong */

			MessageBox(nullptr, reinterpret_cast<const wchar_t*>(QString(
				("Unable to open a handle to the Wlan API. Error: \n   ")
				+ QString::fromWCharArray(_com_error(result).ErrorMessage())
				).utf16()),
				L"Inssidious failed to start.", MB_OK);
			ExitProcess(1);
		}
	}

	/* Stop any existing running Hosted Network */
	
	emit hostedNetworkMessage("Stopping any currently running Hosted Networks.", HOSTED_NETWORK_STARTING);
	result = WlanHostedNetworkForceStop(
		wlanHandle,									//Wlan handle
		pHostedNetworkFailReason,					//Pointer to where the API can store a failure reason in
		nullptr										//Reserved
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to stop an existing, running Hosted Network. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Prepare the network name in the appropriate SSID format */

	DOT11_SSID hostedNetworkSSID;						//DOT11_SSID struct to use later with WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS
	hostedNetworkSSID.uSSIDLength = networkName.count();//Set the length of the array in th uSSIDLength struct value
	for (int i = 0; i < networkName.count(); i++)		//Fill the ucSSID array
	{
		hostedNetworkSSID.ucSSID[i] = networkName.at(i).unicode();
	}
	

	/* Initialize the WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS with the SSID and max peer count */
	/* And Set the Hosted Network network name and peer count */

	emit hostedNetworkMessage("Setting the network name and password.", HOSTED_NETWORK_STARTING);
	WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS hostedNetworkConnectionSettings{ hostedNetworkSSID, maxNumberOfPeers };
	result = WlanHostedNetworkSetProperty(
		wlanHandle,										//Wlan handle
		wlan_hosted_network_opcode_connection_settings, //Type of data being passed to the API
		sizeof(hostedNetworkConnectionSettings),		//Size of the data at the pointer to hosted network connection settings
		static_cast<PVOID>(&hostedNetworkConnectionSettings),		//Pointer to the hosted network connection settings we are setting
		pHostedNetworkFailReason,						//Pointer to where the API can store a failure reason in
		nullptr											//Reserved
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to set hosted network settings. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Prepare the network password in the appropriate UCHAR format */

	DWORD dwKeyLength = networkPassword.count() + 1;	//Length of the network password, needed for the API call, +1 for the null
	PUCHAR pucKeyData = new UCHAR[dwKeyLength];			//Initialize our UCHAR variable
	for (int i = 0; i < networkPassword.count(); i++)	//Fill the array
	{
		pucKeyData[i] = networkPassword.at(i).unicode();
		pucKeyData[i + 1] = '\0';						//null the next character to ensure we have a null at the end of the loop
	}


	/* Set the Hosted Network password */

	result = WlanHostedNetworkSetSecondaryKey(
		wlanHandle,										//Wlan handle
		dwKeyLength,									//Length of the network password array including the null character
		pucKeyData,										//Pointer to a UCHAR array with the network password
		TRUE,											//Is a pass phrase
		TRUE,											//Do not persist this key for future hosted network sessions
		pHostedNetworkFailReason,						//Pointer to where the API can store a failure reason in
		nullptr											//Reserved
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to set hosted network password. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Save the hosted network settings */

	emit hostedNetworkMessage("Saving the hosted network settings.", HOSTED_NETWORK_STARTING);
	result = WlanHostedNetworkInitSettings(
		wlanHandle,									//Wlan handle
		pHostedNetworkFailReason,					//Pointer to where the API can store a failure reason in
		nullptr										//Reserved
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to save hosted network settings. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}

	/* Start the Hosted Network */

	emit hostedNetworkMessage("Starting the Hosted Network.", HOSTED_NETWORK_STARTING);
	result = WlanHostedNetworkStartUsing(
		wlanHandle,										//Wlan handle
		pHostedNetworkFailReason,						//Pointer to where the API can store a failure reason in
		nullptr											//Reserved
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to start the wireless hosted network. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Register to receive hosted network related notifications in our callback function */

	result = WlanRegisterNotification(
		wlanHandle,									//Wlan handle
		WLAN_NOTIFICATION_SOURCE_HNWK,				//Specifically receive Hosted Network notifications
		TRUE,										//Don't send duplicate notifications
		&WlanNotificationCallback,					//WLAN_NOTIFICATION_CALLBACK function to call with notifactions
		this,										//Context to pass along with the notification
		nullptr,										//Reserved
		nullptr										//Previously registered notification sources
		);
	if (result != NO_ERROR)
	{
		emit hostedNetworkMessage("Unable to register for Wlan Hosted Network Notifications. Error: \n" + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* Check the hosted network status */

	int loop30 = 0;
	PWLAN_HOSTED_NETWORK_STATUS pHostedNetworkStatus = nullptr;
	while (loop30 < 30)
	{
		loop30++;
		pHostedNetworkStatus = nullptr;
		result = WlanHostedNetworkQueryStatus(
			wlanHandle,										//Wlan handle
			&pHostedNetworkStatus,							//Pointer to a pointer for HOSTED_NETWORK_STATUS
			nullptr											//Reserved
			);
		if (result != NO_ERROR)
		{
			Sleep(500);
			continue;
		}
		else
		{
			break;
		}
	}

	/* Left the loop */

	if (result != NO_ERROR || !pHostedNetworkStatus)
	{
		emit hostedNetworkMessage("Unable to query hosted network status. Error: \n   " + QString::fromWCharArray(_com_error(result).ErrorMessage()), HOSTED_NETWORK_STARTING_FAILED);
		return false;
	}


	/* The Hosted Network started. Free memory, emit the status, save the network GUID, and return true */

	hostedNetworkGUID = pHostedNetworkStatus->IPDeviceID;
	WlanFreeMemory(pHostedNetworkStatus);
	pHostedNetworkStatus = nullptr;


	emit hostedNetworkMessage("Hosted Network started successfully.", HOSTED_NETWORK_STARTED);

	return true;
}