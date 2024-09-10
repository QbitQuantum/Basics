// Set current configuration to VPN Azure client
void AcApplyCurrentConfig(AZURE_CLIENT *ac, DDNS_CLIENT_STATUS *ddns_status)
{
	bool disconnect_now = false;
	SOCK *disconnect_sock = NULL;
	// Validate arguments
	if (ac == NULL)
	{
		return;
	}

	// Get current DDNS configuration
	Lock(ac->Lock);
	{
		if (ddns_status != NULL)
		{
			if (StrCmpi(ac->DDnsStatus.CurrentHostName, ddns_status->CurrentHostName) != 0)
			{
				// If host name is changed, disconnect current data connection
				disconnect_now = true;
			}

			if (Cmp(&ac->DDnsStatus.InternetSetting, &ddns_status->InternetSetting, sizeof(INTERNET_SETTING)) != 0)
			{
				// If proxy setting is changed, disconnect current data connection
				disconnect_now = true;
			}

			Copy(&ac->DDnsStatus, ddns_status, sizeof(DDNS_CLIENT_STATUS));
		}

		if (ac->IsEnabled == false)
		{
			// If VPN Azure client is disabled, disconnect current data connection
			disconnect_now = true;
		}

		if (disconnect_now)
		{
			if (ac->CurrentSock != NULL)
			{
				disconnect_sock = ac->CurrentSock;
				AddRef(disconnect_sock->ref);
			}
		}
	}
	Unlock(ac->Lock);

	if (disconnect_sock != NULL)
	{
		Disconnect(disconnect_sock);
		ReleaseSock(disconnect_sock);
	}

	Set(ac->Event);
}