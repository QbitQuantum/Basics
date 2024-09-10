int _tmain(int argc, TCHAR * argv[])
{
	TCHAR *currentPassword = _tcsdup(argv[1]);
	TCHAR *preferPassword = argv[argc > 2 ? 2 : 1];

	BOOL quit = FALSE;
	int err = 1;

	do
	{
		TCHAR *uuid = NULL;

		if (UuidCreateToString(&uuid))
		{
			NET_API_STATUS nStatus = NetUserChangePassword(NULL, NULL, currentPassword, uuid);
			if (nStatus == NERR_Success)
			{
				free(currentPassword);
				currentPassword = _tcsdup(uuid);
				_ftprintf(stdout, _T("pwd %s\n"), uuid);
				nStatus = NetUserChangePassword(NULL, NULL, currentPassword, preferPassword);
				if (nStatus == NERR_Success)
				{
					quit = TRUE;
					err = 0;
				}
			}
			else
			{
				quit = TRUE;
			}

			RpcStringFree(&uuid);
		}
		else
		{
			quit = TRUE;
		}
	} while (!quit);

	free(currentPassword);

	return err;
};