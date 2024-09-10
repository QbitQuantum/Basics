bool FWinInetConnection::InitConnection()
{
	// Make sure previous connection is closed
	ShutdownConnection();

	UE_LOG(LogHttp, Log, TEXT("Initializing WinInet connection"));

	// Check and log the connected state so we can report early errors.
	::DWORD ConnectedFlags;
	BOOL bConnected = InternetGetConnectedState(&ConnectedFlags, 0);
	FString ConnectionType;
	ConnectionType += (ConnectedFlags & INTERNET_CONNECTION_CONFIGURED) ? TEXT("Configured ") : TEXT("");
	ConnectionType += (ConnectedFlags & INTERNET_CONNECTION_LAN) ? TEXT("LAN ") : TEXT("");
	ConnectionType += (ConnectedFlags & INTERNET_CONNECTION_MODEM) ? TEXT("Modem ") : TEXT("");
	ConnectionType += (ConnectedFlags & INTERNET_CONNECTION_MODEM_BUSY) ? TEXT("Modem Busy ") : TEXT("");
	ConnectionType += (ConnectedFlags & INTERNET_CONNECTION_OFFLINE) ? TEXT("Offline ") : TEXT("");
	ConnectionType += (ConnectedFlags & INTERNET_CONNECTION_PROXY) ? TEXT("Proxy Server ") : TEXT("");
	ConnectionType += (ConnectedFlags & INTERNET_RAS_INSTALLED) ? TEXT("RAS Installed ") : TEXT("");
	UE_LOG(LogHttp, Log, TEXT("Connected State: %s. Flags: (%s)"), 
		bConnected ? TEXT("Good") : TEXT("Bad"), *ConnectionType);

	if (InternetAttemptConnect(0) != ERROR_SUCCESS)
	{
		UE_LOG(LogHttp, Warning, TEXT("InternetAttemptConnect failed: %s\n"), 
			*InternetTranslateError(GetLastError()));
		return false;
	}

	// setup net connection
	InternetHandle = InternetOpen(
		*FString::Printf(TEXT("game=%s, engine=UE4, version=%d"), FApp::GetGameName(), GEngineNetVersion), 
		INTERNET_OPEN_TYPE_PRECONFIG, 
		NULL, 
		NULL, 
		INTERNET_FLAG_ASYNC);

	if (InternetHandle == NULL)
	{
		UE_LOG(LogHttp, Warning, TEXT("Failed WinHttpOpen: %s"), 
			*InternetTranslateError(GetLastError()));
		return false;
	}
	
	{
		FScopeLock ScopeLock(&FHttpManager::RequestLock);
		bStaticConnectionInitialized = true;
	}

	// Register callback to update based on WinInet connection state
	InternetSetStatusCallback(InternetHandle, InternetStatusCallbackWinInet);

	return true;
}