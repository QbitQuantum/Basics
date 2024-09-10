BOOL COledbDatabase::Open(HWND hWnd, LPCTSTR pstrConnectionString, LPCTSTR pstrUser, LPCTSTR pstrPassword, long iType)
{
   HRESULT Hr;

   Close();

   if( (iType & DB_OPEN_PROMPTDIALOG) != 0 ) 
   {
      // Initialize from Data Links UI

      CComPtr<IDBPromptInitialize> spPrompt;
      Hr = spPrompt.CoCreateInstance(CLSID_DataLinks);
      if( FAILED(Hr) ) return _Error(Hr);

      if( hWnd == NULL ) hWnd = ::GetActiveWindow();
      if( hWnd == NULL ) hWnd = ::GetDesktopWindow();

      Hr = spPrompt->PromptDataSource(
         NULL,                             // pUnkOuter
         hWnd,                             // hWndParent
         DBPROMPTOPTIONS_PROPERTYSHEET,    // dwPromptOptions
         0,                                // cSourceTypeFilter
         NULL,                             // rgSourceTypeFilter
         NULL,                             // pwszszzProviderFilter
         IID_IDBInitialize,                // riid
         (LPUNKNOWN*) &m_spInit);          // ppDataSource
      if( Hr == S_FALSE ) Hr = MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, ERROR_CANCELLED);  // The user clicked cancel
      if( FAILED(Hr) ) return _Error(Hr);
   }
   else 
   {
      TCHAR szPrefix[] = _T("Provider=");
      ::lstrcpyn(szPrefix, pstrConnectionString, (sizeof(szPrefix) / sizeof(TCHAR)));
      if( ::lstrcmpi(szPrefix, _T("Provider=")) == 0 ) 
      {
         // Connect using OLE DB connection string

         CComPtr<IDataInitialize> spDataInit;
         Hr = spDataInit.CoCreateInstance(CLSID_MSDAINITIALIZE);
         if( FAILED(Hr) ) return _Error(Hr);

         USES_CONVERSION;
         Hr = spDataInit->GetDataSource(NULL, CLSCTX_INPROC_SERVER, T2OLE((LPTSTR)pstrConnectionString), IID_IDBInitialize, (LPUNKNOWN*)&m_spInit);
         if( FAILED(Hr) ) return _Error(Hr);
      }
      else 
      {
         // Initialize from ODBC DSN information

         Hr = m_spInit.CoCreateInstance(L"MSDASQL");
         if( FAILED(Hr) ) return _Error(Hr);

         DBPROPSET PropSet;
         const ULONG nMaxProps = 4;
         DBPROP Prop[nMaxProps];
         ULONG iProp = 0;

         // Initialize common property options.
         ULONG i;
         for( i = 0; i < nMaxProps; i++ ) {
            ::VariantInit(&Prop[i].vValue);
            Prop[i].dwOptions = DBPROPOPTIONS_REQUIRED;
            Prop[i].colid = DB_NULLID;
         }

         // Level of prompting that will be done to complete the connection process
         Prop[iProp].dwPropertyID = DBPROP_INIT_PROMPT;
         Prop[iProp].vValue.vt = VT_I2;
         Prop[iProp].vValue.iVal = DBPROMPT_NOPROMPT;    
         iProp++;
         // Data source name--see the sample source included with the OLE DB SDK.
         Prop[iProp].dwPropertyID = DBPROP_INIT_DATASOURCE;   
         Prop[iProp].vValue.vt = VT_BSTR;
         Prop[iProp].vValue.bstrVal = T2BSTR(pstrConnectionString);
         iProp++;
         if( pstrUser ) {
            // User ID
            Prop[iProp].dwPropertyID = DBPROP_AUTH_USERID;
            Prop[iProp].vValue.vt = VT_BSTR;
            Prop[iProp].vValue.bstrVal = T2BSTR(pstrUser);
            iProp++;
         }
         if( pstrPassword ) {
            // Password
            Prop[iProp].dwPropertyID = DBPROP_AUTH_PASSWORD;
            Prop[iProp].vValue.vt = VT_BSTR;
            Prop[iProp].vValue.bstrVal = T2BSTR(pstrPassword);
            iProp++;
         }

         // Prepare properties
         PropSet.guidPropertySet = DBPROPSET_DBINIT;
         PropSet.cProperties = iProp;
         PropSet.rgProperties = Prop;
         // Set initialization properties.
         CComQIPtr<IDBProperties> spProperties = m_spInit;
         Hr = spProperties->SetProperties(1, &PropSet);
      
         // Before we check if it failed, clean up
         for( i = 0; i < nMaxProps; i++ ) ::VariantClear(&Prop[i].vValue);
      
         // Did SetProperties() fail?
         if( FAILED(Hr) ) return _Error(Hr);
      }
   }

   return Connect();
}