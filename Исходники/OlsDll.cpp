//-----------------------------------------------------------------------------
//
// Initialize/Deinitialize Functions
//
//-----------------------------------------------------------------------------
DWORD Initialize()
{
	TCHAR dir[MAX_PATH];
	TCHAR *ptr;

	GetModuleFileName(gModule, dir, MAX_PATH);
	if((ptr = _tcsrchr(dir, '\\')) != NULL)
	{
		*ptr = '\0';
	}
	wsprintf(gDriverPath, _T("%s\\%s"), dir, gDriverFileName);

	if(IsFileExist(gDriverPath) == FALSE)
	{
		return OLS_DLL_DRIVER_NOT_FOUND;
	}

	if(IsOnNetworkDrive(gDriverPath) == TRUE)
	{
		return OLS_DLL_DRIVER_NOT_LOADED_ON_NETWORK;
	}

	if(gIsNT)
	{
		if(OpenDriver())
		{
			return OLS_DLL_NO_ERROR;
		}

		ManageDriver(OLS_DRIVER_ID, gDriverPath, OLS_DRIVER_REMOVE);
		if(!ManageDriver(OLS_DRIVER_ID, gDriverPath, OLS_DRIVER_INSTALL))
		{
			ManageDriver(OLS_DRIVER_ID, gDriverPath, OLS_DRIVER_REMOVE);
			return OLS_DLL_DRIVER_NOT_LOADED;
		}
		
		if(OpenDriver())
		{
			return OLS_DLL_NO_ERROR;
		}
		return OLS_DLL_DRIVER_NOT_LOADED;
	}
	else
	{
		gHandle = CreateFile(
			_T("\\\\.\\") OLS_DRIVER_FILE_NAME_WIN_9X,
			0, 0, NULL,	0, 
			FILE_FLAG_DELETE_ON_CLOSE,
			NULL);

		if(gHandle == INVALID_HANDLE_VALUE)
		{
			return OLS_DLL_DRIVER_NOT_LOADED;
		}
		return OLS_DLL_NO_ERROR;
	}
}