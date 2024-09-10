// Main process
void MainNM()
{
	UINT port;
	char hostname[MAX_HOST_NAME_LEN + 1];
	char *tmp =
		RemoteDlg(NULL, NM_SETTING_REG_KEY, ICO_ROUTER,
		_UU("NM_TITLE"), _UU("NM_CONNECT_TITLE"), NULL);
	TOKEN_LIST *t;

	Zero(hostname, sizeof(hostname));

	if (tmp == NULL)
	{
		return;
	}

	t = ParseToken(tmp, ":");
	port = DEFAULT_NAT_ADMIN_PORT;

	if (t->NumTokens >= 2)
	{
		UINT i = ToInt(t->Token[1]);
		if (i != 0)
		{
			port = i;
		}
	}
	if (t->NumTokens >= 1)
	{
		RPC *rpc;
		StrCpy(hostname, sizeof(hostname), t->Token[0]);

		// Connection
		Trim(hostname);

		if (StrLen(hostname) != 0)
		{
			rpc = NmConnect(hostname, port);
			if (rpc != NULL)
			{
				// Connected
				NmMainDlg(rpc);
				NatAdminDisconnect(rpc);
			}
		}
	}

	FreeToken(t);

	Free(tmp);
}