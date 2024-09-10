	/** Install and Uninstall the service and write actions to the event
	log. If pszFullPath is given, it will be set as the path, otherwise the
	path will be retreived from the module name. The default command line
	processing calls this function with pszLogonAs and pszLogonPassword set
	to NULL. Override this function, and when bInstall is VTRUE, get the
	logon as and password if needed, and then call the base class function.
	pszLogonAs can be either a DomainName\UserName or just the UserName, in
	which case this function will prepend .\ which is required by the
	CreateService() API function. Returns VTRUE on success, VFALSE on
	failure.*/
	virtual VBOOL			Install(	VBOOL			bInstall =
															VTRUE,
										VDWORD			nStartType =
															SERVICE_AUTO_START,
										VSTRING_CONST	pszFullPath =
															NULL,
										VSTRING_CONST	pszLogonAs =
															NULL,
										VSTRING_CONST	pszLogonPassword =
															NULL,
										VBOOL			bStartAfterInstall =
															VTRUE,
										VBOOL			bSilentMode =
															VFALSE)
	{
		/* Service name should not be empty!*/
		VASSERT(m_strServiceName.IsNotEmpty())

		/* Assume failure.*/
		VBOOL bSuccess = VFALSE;

		/* Open the Service Control Manager.*/
		SC_HANDLE hSCM =
			OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);

		if ( hSCM )
		{
			if ( bInstall )
			{
				/* Verify un-installed, first (silent mode).*/
				Install(VFALSE, 0, NULL, NULL, NULL, VFALSE, VTRUE);

				/* Get this executables file path (unless given
				in pszFullPath).*/
				VString sPath;

				if ( !pszFullPath )
					sPath.GetModulePath(VFALSE, VFALSE);
				else
					sPath = pszFullPath;

				if ( sPath.IsNotEmpty() )
				{
					/* If pszLogonAs is not NULL, verify domain name is
					present, and if not, .\ is present. If neither is the
					case, we will modify the logon as to be correct.*/
					VString strLogonAs;

					if ( pszLogonAs )
					{
						/* If we find a \ assume correct DomainName\UserName
						string.*/
						if ( !VSTRCHR(pszLogonAs, VTEXT('\\')) )
						{
							/* Domain Name not given, so does the
							string already contain .\ sequence as the
							first chars?*/
							if (	!(*pszLogonAs == VTEXT('.') &&
									*(pszLogonAs + 1) == VTEXT('\\')) )
							{
								strLogonAs = VTEXT(".\\");
								strLogonAs += pszLogonAs;
								pszLogonAs = strLogonAs;
							}
						}
					}

					/* We want no error condition now.*/
					SetLastError(0);

					/* Create the service.*/
					SC_HANDLE hService =
						CreateService(	hSCM,
										m_strServiceName,
										m_strServiceName,
										SERVICE_ALL_ACCESS,
										m_Status.dwServiceType,
										nStartType,
										SERVICE_ERROR_NORMAL,
										sPath,
										NULL,
										NULL,
										NULL,
										pszLogonAs,
										pszLogonPassword);

					if (	hService ||
							GetLastError() == ERROR_SERVICE_EXISTS )
					{
						/* Make or verify registry entries to
						support event logging.*/
						bSuccess =
							(m_hEventSource)
							? VTRUE
							: Register(m_strServiceName);

						if (	hService &&
								bSuccess &&
								bStartAfterInstall )
						{
							bSuccess =
								StartService(hService, 0, NULL);

							/* If service fails to start now, un-install it.*/
							if ( !bSuccess )
							{
								/* Close handle first.*/
								CloseServiceHandle(hService);
								hService = NULL;

								/* Un-Install in silent mode.*/
								Install(	VFALSE,
											0,
											NULL,
											NULL,
											NULL,
											VFALSE,
											VTRUE);
							}
						}

						if ( hService )
							CloseServiceHandle(hService);
					}
				}

				/* Log what happened if we can.*/
				LogEvent(	(bSuccess)
							? EM_SERVICE_INSTALLED
							: EM_SERVICE_NOT_INSTALLED,
							(bSuccess)
							? VFALSE
							: VTRUE);

				/* Notify via virtual function.*/
				OnInstall(bSuccess, bSilentMode);
			}
			else
			{
				SC_HANDLE hService =
					OpenService(	hSCM,
									m_strServiceName,
									SERVICE_QUERY_STATUS | DELETE);

				if ( hService )
				{
					/* If the service is running, stop it.*/
					SERVICE_STATUS ss;

					if ( QueryServiceStatus(hService, &ss) )
					{
						if ( ss.dwCurrentState != SERVICE_STOPPED )
						{
							/* Get a handle we can use to
							stop the service.*/
							SC_HANDLE hStopService =
								OpenService(	hSCM,
												m_strServiceName,
												SERVICE_STOP);

							if ( hStopService )
							{
								SERVICE_STATUS ss;
								ControlService(	hStopService,
												SERVICE_CONTROL_STOP, &ss);

								CloseServiceHandle(hStopService);
							}
						}
					}

					bSuccess =
						(hService && DeleteService(hService))
						? VTRUE
						: VFALSE;

					CloseServiceHandle(hService);
				}
				else
					bSuccess = VTRUE;

				/* Remove registry entries on success.*/
				if ( bSuccess )
				{
					VRegistry reg;

					if ( reg.CreateKey(GetRegistryKey(), HKEY_LOCAL_MACHINE) )
						reg.DeleteSubKeyNT(m_strServiceName);
				}

				/* Log what happened if we can.*/
				LogEvent(	(bSuccess)
							? EM_SERVICE_UNINSTALLED
							: EM_SERVICE_NOT_REMOVED,
							(bSuccess)
							? VFALSE
							: VTRUE);

				/* Notify via virtual function.*/
				OnUnInstall(bSuccess, bSilentMode);
			}

			CloseServiceHandle(hSCM);
		}

		return bSuccess;
	}