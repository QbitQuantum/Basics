// Start the EtherLogger Manager
void EMExec()
{
	char *host;
	char *ret;
	bool cancel_now = false;
	TOKEN_LIST *t;
	UINT port = EL_ADMIN_PORT;
	InitWinUi(_UU("EM_TITLE"), _SS("DEFAULT_FONT"), _II("DEFAULT_FONT_SIZE"));

	while (true)
	{
		ret = EmRemoteDlg();

		if (ret != NULL)
		{
			t = ParseToken(ret, ":");
			if (t->NumTokens == 1 || t->NumTokens == 2)
			{
				RPC *rpc = NULL;
				bool ok = false;
				UINT ret;
				host = t->Token[0];
				if (t->NumTokens == 2)
				{
					port = ToInt(t->Token[1]);
				}
				else
				{
					port = EL_ADMIN_PORT;
				}

				// Try without a password first
				ret = EcConnect(host, port, "", &rpc);
RETRY:
				if (ret != ERR_NO_ERROR && ret != ERR_AUTH_FAILED)
				{
					// Connection failed
					CALL(NULL, ret);
				}
				else
				{
					if (ret == ERR_NO_ERROR)
					{
						// Successful connection
						ok = true;
					}
					else
					{
						// Password required
						char *pass = SmPassword(NULL, host);
						if (pass == NULL)
						{
							// Cancel
							cancel_now = true;
						}
						else
						{
							// Retry
							ret = EcConnect(host, port, pass, &rpc);
							Free(pass);
							if (ret == ERR_NO_ERROR)
							{
								ok = true;
							}
							else
							{
								goto RETRY;
							}
						}
					}
				}

				if (ok)
				{
					// Main screen
					EMMain(rpc);

					// Disconnect
					EcDisconnect(rpc);
					cancel_now = true;
				}
				FreeToken(t);
			}
			Free(ret);
		}
		else
		{
			cancel_now = true;
		}

		if (cancel_now)
		{
			break;
		}
	}

	FreeWinUi();
}