	HRESULT EnableService( LPCTSTR szSvcName, BOOL fDisable )
	{
		CAutoServiceHandle m_schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if(m_schSCManager==NULL)
			return E_POINTER;

		CAutoServiceHandle schService=NULL;
		SC_LOCK sclLock; 
		LPQUERY_SERVICE_LOCK_STATUS lpqslsBuf; 
		DWORD dwBytesNeeded, dwStartType; 
		BOOL bSuccess=TRUE;

		// Need to acquire database lock before reconfiguring. 
		sclLock = LockServiceDatabase(m_schSCManager); 

		// If the database cannot be locked, report the details. 
		if (sclLock == NULL) 
		{ 
			// Exit if the database is not locked by another process. 

			if (GetLastError() != ERROR_SERVICE_DATABASE_LOCKED) 
			{
				DPRINT("Database lock failed (%d)\n", GetLastError()); 
				return E_FAIL;
			}

			// Allocate a buffer to get details about the lock. 
			lpqslsBuf = (LPQUERY_SERVICE_LOCK_STATUS) LocalAlloc( 
				LPTR, sizeof(QUERY_SERVICE_LOCK_STATUS)+256); 
			if (lpqslsBuf == NULL) 
			{
				DPRINT("LocalAlloc failed (%d)\n", GetLastError()); 
				return E_FAIL;
			}

			// Get and print the lock status information. 
			if (!QueryServiceLockStatus( 
				m_schSCManager, 
				lpqslsBuf, 
				sizeof(QUERY_SERVICE_LOCK_STATUS)+256, 
				&dwBytesNeeded) ) 
			{
				DPRINT("Query lock status failed (%d)", GetLastError()); 
				return E_FAIL;
			}

			if (lpqslsBuf->fIsLocked) 
				DPRINT("Locked by: %s, duration: %d seconds\n", 
				lpqslsBuf->lpLockOwner, 
				lpqslsBuf->dwLockDuration); 
			else 
				DPRINT("No longer locked\n"); 

			LocalFree(lpqslsBuf); 
		} 

		// The database is locked, so it is safe to make changes. 
		// Open a handle to the service. 
		schService = OpenService( 
			m_schSCManager,           // SCManager database 
			szSvcName,				// name of service 
			SERVICE_CHANGE_CONFIG); // need CHANGE access 
		if (schService == NULL) 
		{
			DPRINT("OpenService failed (%d)\n", GetLastError());
			return E_FAIL;
		}

		dwStartType = (fDisable) ? SERVICE_DISABLED : SERVICE_DEMAND_START; 

		// Make the changes. 

		if (! ChangeServiceConfig( 
			schService,        // handle of service 
			SERVICE_NO_CHANGE, // service type: no change 
			dwStartType,       // change service start type 
			SERVICE_NO_CHANGE, // error control: no change 
			NULL,              // binary path: no change 
			NULL,              // load order group: no change 
			NULL,              // tag ID: no change 
			NULL,              // dependencies: no change 
			NULL,              // account name: no change 
			NULL,              // password: no change 
			NULL) )            // display name: no change
		{
			DPRINT("ChangeServiceConfig failed (%d)\n", GetLastError()); 
			bSuccess = FALSE;
		}
		else 
			DPRINT("ChangeServiceConfig succeeded.\n"); 

		// Release the database lock. 
		UnlockServiceDatabase(sclLock); 
		return bSuccess ? S_OK : E_FAIL;
	}