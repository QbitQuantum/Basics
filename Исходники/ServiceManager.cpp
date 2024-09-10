   void
   ServiceManager::MakeDependentOn(const String &ServiceName)
   //---------------------------------------------------------------------------//
   // DESCRIPTION:
   // Makes hMailServer dependent on RPCSS and ServiceName
   //---------------------------------------------------------------------------//
   {
      // Retrieve the handle for the local service manager.
      SC_HANDLE hSCManager;
      hSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE | SC_MANAGER_LOCK);

      // Retrieve the handle for the service.
      SC_HANDLE hService = OpenService( hSCManager, _T("hMailServer"), SERVICE_CHANGE_CONFIG );

      SC_LOCK sclLock = LockServiceDatabase(hSCManager); 

      if (sclLock == NULL)
      {
         CloseServiceHandle(hService);
         return;
      }

      int iLength = ServiceName.GetLength() + 8;
      TCHAR * lpDependent = new TCHAR[iLength];
      memset(lpDependent, 0, iLength * sizeof(TCHAR));
      _tcscpy(lpDependent, _T("RPCSS"));
      _tcscpy(lpDependent+6, ServiceName);
      
      int iRet = ChangeServiceConfig( 
         hService,        // handle of service 
         SERVICE_NO_CHANGE, // service type: no change 
         SERVICE_NO_CHANGE, // service start type no change
         SERVICE_NO_CHANGE, // error control: no change 
         NULL,            // binary path changed
         NULL,              // load order group: no change 
         NULL,              // tag ID: no change 
         lpDependent,      // dependencies: no change 
         NULL,              // account name: no change 
         NULL,              // password: no change 
         NULL);             // display name: no change


      CloseServiceHandle(hService); 
      UnlockServiceDatabase(sclLock); 

      delete [] lpDependent;
   }