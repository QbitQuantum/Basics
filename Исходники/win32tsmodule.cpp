// @pymethod object|win32ts|WTSQueryUserConfig|Returns user configuration
// @rdesc The type of the returned value is dependent on the config class requested
static PyObject *PyWTSQueryUserConfig(PyObject *self, PyObject *args, PyObject *kwargs)
{
	static char *keywords[]={"ServerName","UserName","WTSConfigClass",NULL};
	WCHAR *ServerName=NULL, *UserName=NULL;
	PyObject *obServerName, *obUserName, *ret=NULL;
	WTS_CONFIG_CLASS WTSConfigClass;
	LPWSTR buf=NULL;
	DWORD bufsize=0;

	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "OOk:WTSQueryUserConfig", keywords,
		&obServerName,	// @pyparm <o PyUnicode>|ServerName||Name ot terminal server
		&obUserName,	// @pyparm <o PyUnicode>|UserName||Name of user
		&WTSConfigClass))	// @pyparm int|ConfigClass||Type of information to be returned, win32ts.WTSUserConfig*
		return NULL;
	if (PyWinObject_AsWCHAR(obServerName, &ServerName, TRUE)
		&&PyWinObject_AsWCHAR(obUserName, &UserName, FALSE))
		if (!WTSQueryUserConfig(ServerName, UserName, WTSConfigClass, &buf, &bufsize))
			PyWin_SetAPIError("WTSQueryUserConfig");
		else
			switch(WTSConfigClass){
				// @flagh ConfigClass|Returned value
				case WTSUserConfigInitialProgram:				// @flag WTSUserConfigInitialProgram|Unicode string, program to be run when user logs on
				case WTSUserConfigWorkingDirectory:				// @flag WTSUserConfigWorkingDirectory|Unicode string, working dir for initial program
				case WTSUserConfigModemCallbackPhoneNumber:		// @flag WTSUserConfigModemCallbackPhoneNumber|Unicode string
				case WTSUserConfigTerminalServerProfilePath:	// @flag WTSUserConfigTerminalServerProfilePath|Unicode string
				case WTSUserConfigTerminalServerHomeDir:		// @flag WTSUserConfigTerminalServerHomeDir|Unicode string
				case WTSUserConfigTerminalServerHomeDirDrive:	// @flag WTSUserConfigTerminalServerHomeDirDrive|Unicode string
					ret=PyWinObject_FromWCHAR(buf);
					break;
				case WTSUserConfigfInheritInitialProgram:		// @flag WTSUserConfigfInheritInitialProgram|Int
				case WTSUserConfigfAllowLogonTerminalServer:	// @flag WTSUserConfigfAllowLogonTerminalServer|Int, 1 if user can log on thru Terminal Service
				case WTSUserConfigTimeoutSettingsConnections:	// @flag WTSUserConfigTimeoutSettingsConnections |Int, max connection time (ms)
				case WTSUserConfigTimeoutSettingsDisconnections:// @flag WTSUserConfigTimeoutSettingsDisconnections|Int
				case WTSUserConfigTimeoutSettingsIdle:			// @flag WTSUserConfigTimeoutSettingsIdle|Int, max idle time (ms)
				case WTSUserConfigfDeviceClientDrives:			// @flag WTSUserConfigfDeviceClientDrives|Int
				case WTSUserConfigfDeviceClientPrinters:		// @flag WTSUserConfigfDeviceClientPrinters|Int
				case WTSUserConfigfDeviceClientDefaultPrinter:	// @flag WTSUserConfigfDeviceClientDefaultPrinter|Int
				case WTSUserConfigBrokenTimeoutSettings:		// @flag WTSUserConfigBrokenTimeoutSettings|Int
				case WTSUserConfigReconnectSettings:			// @flag WTSUserConfigReconnectSettings|Int
				case WTSUserConfigModemCallbackSettings:		// @flag WTSUserConfigModemCallbackSettings|Int
				case WTSUserConfigShadowingSettings:			// @flag WTSUserConfigShadowingSettings|Int, indicates if user's session my be monitored
				case WTSUserConfigfTerminalServerRemoteHomeDir:	// @flag WTSUserConfigfTerminalServerRemoteHomeDir|Int,
					ret=PyLong_FromUnsignedLong(*(DWORD *)buf);
					break;
				default:
					PyErr_SetString(PyExc_NotImplementedError,"Config class not supported yet");
			}

	PyWinObject_FreeWCHAR(ServerName);
	PyWinObject_FreeWCHAR(UserName);
	if (buf)
		WTSFreeMemory(buf);
	return ret;
}