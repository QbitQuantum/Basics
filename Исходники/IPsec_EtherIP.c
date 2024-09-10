// IPC connection processing thread
void EtherIPIpcConnectThread(THREAD *t, void *p)
{
	ETHERIP_SERVER *s;
	IPC *ipc = NULL;
	UINT error_code = 0;
	char tmp[MAX_SIZE];
	ETHERIP_ID id;
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	s = (ETHERIP_SERVER *)p;

	GetHostName(tmp, sizeof(tmp), &s->ClientIP);

	// Get the setting of the virtual HUB to be connected based on the client ID presented
	if (SearchEtherIPId(s->Ike->IPsec, &id, s->ClientId) == false &&
		SearchEtherIPId(s->Ike->IPsec, &id, "*") == false)
	{
		// Failed to get the settings for the virtual HUB
		Debug("Not Found: EtherIP Settings for Client ID \"%s\".\n", s->ClientId);

		EtherIPLog(s, "LE_NO_SETTING", s->ClientId);
	}
	else
	{
		UINT mss = CalcEtherIPTcpMss(s);
		char client_name[MAX_SIZE];

		if (s->L2TPv3 == false)
		{
			StrCpy(client_name, sizeof(client_name), ETHERIP_CLIENT_NAME);
		}
		else
		{
			if (IsEmptyStr(s->VendorName))
			{
				StrCpy(client_name, sizeof(client_name), ETHERIP_L2TPV3_CLIENT_NAME);
			}
			else
			{
				Format(client_name, sizeof(client_name), ETHERIP_L2TPV3_CLIENT_NAME_EX, s->VendorName);
			}
		}

		// Execution of IPC connection process
		EtherIPLog(s, "LE_START_IPC", id.HubName, id.UserName, mss);
		ipc = NewIPC(s->Cedar, client_name,
			(s->L2TPv3 ? ETHERIP_L2TPV3_POSTFIX : ETHERIP_POSTFIX),
			id.HubName, id.UserName, id.Password,
			&error_code,
			&s->ClientIP, s->ClientPort,
			&s->ServerIP, s->ServerPort,
			tmp,
			s->CryptName, true, mss);

		if (ipc != NULL)
		{
			Copy(&s->CurrentEtherIPIdSetting, &id, sizeof(ETHERIP_ID));
			EtherIPLog(s, "LE_IPC_CONNECT_OK", id.HubName);
		}
		else
		{
			EtherIPLog(s, "LE_IPC_CONNECT_ERROR", id.HubName, error_code, _E(error_code));
		}
	}

	Lock(s->Lock);
	{
		// Set the results
		ReleaseThread(s->IpcConnectThread);
		s->IpcConnectThread = NULL;

		s->Ipc = ipc;

		s->LastConnectFailedTick = Tick64();
	}
	Unlock(s->Lock);

	// Hit the event to cause interrupt
	SetSockEvent(s->SockEvent);

	// Release the EtherIP object that is hold by this thread
	ReleaseEtherIPServer(s);
}