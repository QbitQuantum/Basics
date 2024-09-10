bool WMIVideoInfo::_initializeWMI()
{
   //// Set security levels 
   //hr = CoInitializeSecurity(
   //   NULL, 
   //   -1,                          // COM authentication
   //   NULL,                        // Authentication services
   //   NULL,                        // Reserved
   //   RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
   //   RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
   //   NULL,                        // Authentication info
   //   EOAC_NONE,                   // Additional capabilities 
   //   NULL                         // Reserved
   //   );

   //if( FAILED( hr ) )
   //{
   //   Con::errorf( "WMIVideoInfo: Failed to initialize com security." );
   //   return false;
   //}

   // Obtain the locator to WMI 
   HRESULT hr = CoCreateInstance(
      CLSID_WbemLocator,             
      0, 
      CLSCTX_INPROC_SERVER, 
      IID_IWbemLocator, 
      (void**)&mLocator
      );

   if( FAILED( hr ) )
   {
      Con::errorf( "WMIVideoInfo: Failed to create instance of IID_IWbemLocator." );
      return false;
   }

   // Connect to the root\cimv2 namespace with
   // the current user and obtain pointer pSvc
   // to make IWbemServices calls.
   hr = mLocator->ConnectServer(
      BSTR(L"ROOT\\CIMV2"), // Object path of WMI namespace
      NULL,                    // User name. NULL = current user
      NULL,                    // User password. NULL = current
      0,                       // Locale. NULL indicates current
      NULL,                    // Security flags.
      0,                       // Authority (e.g. Kerberos)
      0,                       // Context object 
      &mServices               // pointer to IWbemServices proxy
      );

   if( FAILED( hr ) )
   {
      Con::errorf( "WMIVideoInfo: Connect server failed." );
      return false;
   }


   // Set security levels on the proxy 
   hr = CoSetProxyBlanket(
      mServices,                   // Indicates the proxy to set
      RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
      RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
      NULL,                        // Server principal name 
      RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
      RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
      NULL,                        // client identity
      EOAC_NONE                    // proxy capabilities 
      );

   if( FAILED( hr ) )
   {
      Con::errorf( "WMIVideoInfo: CoSetProxyBlanket failed" );
      return false;
   }

   return true;
}