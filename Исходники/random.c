/* This is the slowpoll function which gathers up network/hard drive
   performance data for the random pool */
BOOL SlowPoll (void)
{
	static int isWorkstation = -1;
	static int cbPerfData = 0x10000;
	HANDLE hDevice;
	LPBYTE lpBuffer;
	DWORD dwSize, status;
	LPWSTR lpszLanW, lpszLanS;
	int nDrive;

	/* Find out whether this is an NT server or workstation if necessary */
	if (isWorkstation == -1)
	{
		HKEY hKey;

		if (RegOpenKeyEx (HKEY_LOCAL_MACHINE,
		       L"SYSTEM\\CurrentControlSet\\Control\\ProductOptions",
				  0, KEY_READ, &hKey) == ERROR_SUCCESS)
		{
			wchar_t szValue[32];
			dwSize = sizeof (szValue);

			isWorkstation = TRUE;
			status = RegQueryValueEx (hKey, L"ProductType", 0, NULL,
						  (LPBYTE) szValue, &dwSize);

			if (status == ERROR_SUCCESS && _wcsicmp (szValue, L"WinNT"))
				/* Note: There are (at least) three cases for
				   ProductType: WinNT = NT Workstation,
				   ServerNT = NT Server, LanmanNT = NT Server
				   acting as a Domain Controller */
				isWorkstation = FALSE;

			RegCloseKey (hKey);
		}
	}
	/* Initialize the NetAPI32 function pointers if necessary */
	if (hNetAPI32 == NULL)
	{
		/* Obtain a handle to the module containing the Lan Manager
		   functions */
		wchar_t dllPath[MAX_PATH];
		if (GetSystemDirectory (dllPath, MAX_PATH))
		{
			StringCbCatW(dllPath, sizeof(dllPath), L"\\NETAPI32.DLL");
		}
		else
			StringCbCopyW(dllPath, sizeof(dllPath), L"C:\\Windows\\System32\\NETAPI32.DLL");

		hNetAPI32 = LoadLibrary (dllPath);
		if (hNetAPI32 != NULL)
		{
			/* Now get pointers to the functions */
			pNetStatisticsGet = (NETSTATISTICSGET) GetProcAddress (hNetAPI32,
							"NetStatisticsGet");
			pNetApiBufferSize = (NETAPIBUFFERSIZE) GetProcAddress (hNetAPI32,
							"NetApiBufferSize");
			pNetApiBufferFree = (NETAPIBUFFERFREE) GetProcAddress (hNetAPI32,
							"NetApiBufferFree");

			/* Make sure we got valid pointers for every NetAPI32
			   function */
			if (pNetStatisticsGet == NULL ||
			    pNetApiBufferSize == NULL ||
			    pNetApiBufferFree == NULL)
			{
				/* Free the library reference and reset the
				   static handle */
				FreeLibrary (hNetAPI32);
				hNetAPI32 = NULL;
			}
		}
	}

	/* Get network statistics.  Note: Both NT Workstation and NT Server
	   by default will be running both the workstation and server
	   services.  The heuristic below is probably useful though on the
	   assumption that the majority of the network traffic will be via
	   the appropriate service */
	lpszLanW = (LPWSTR) WIDE ("LanmanWorkstation");
	lpszLanS = (LPWSTR) WIDE ("LanmanServer");
	if (hNetAPI32 &&
	    pNetStatisticsGet (NULL,
			       isWorkstation ? lpszLanW : lpszLanS,
			       0, 0, &lpBuffer) == 0)
	{
		pNetApiBufferSize (lpBuffer, &dwSize);
		RandaddBuf ((unsigned char *) lpBuffer, dwSize);
		pNetApiBufferFree (lpBuffer);
	}

	/* Get disk I/O statistics for all the hard drives */
	for (nDrive = 0;; nDrive++)
	{
		DISK_PERFORMANCE diskPerformance;
		wchar_t szDevice[24];

		/* Check whether we can access this device */
		StringCbPrintfW (szDevice, sizeof(szDevice), L"\\\\.\\PhysicalDrive%d", nDrive);
		hDevice = CreateFile (szDevice, 0, FILE_SHARE_READ | FILE_SHARE_WRITE,
				      NULL, OPEN_EXISTING, 0, NULL);
		if (hDevice == INVALID_HANDLE_VALUE)
			break;


		/* Note: This only works if you have turned on the disk
		   performance counters with 'diskperf -y'.  These counters
		   are off by default */
		if (DeviceIoControl (hDevice, IOCTL_DISK_PERFORMANCE, NULL, 0,
				&diskPerformance, sizeof (DISK_PERFORMANCE),
				     &dwSize, NULL))
		{
			RandaddBuf ((unsigned char *) &diskPerformance, dwSize);
		}
		CloseHandle (hDevice);
	}

	// CryptoAPI: We always have a valid CryptoAPI context when we arrive here but
	//            we keep the check for clarity purpose
	if ( !CryptoAPIAvailable )
		return FALSE;
	if (CryptGenRandom (hCryptProv, sizeof (buffer), buffer)) 
	{
		RandaddBuf (buffer, sizeof (buffer));

		burn(buffer, sizeof (buffer));
		Randmix();
		return TRUE;
	}
	else
	{
		/* return error in case CryptGenRandom fails */
		CryptoAPILastError = GetLastError ();		
		return FALSE;
	}
}