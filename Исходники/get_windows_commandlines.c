vector_t *get_windows_command_lines(void){

  vector_t *ret = talloc(sizeof(vector_t));

  HRESULT hr = 0;
  IWbemLocator         *WbemLocator  = NULL;
  IWbemServices        *WbemServices = NULL;
  IEnumWbemClassObject *EnumWbem  = NULL;

  //initializate the Windows security
  hr = CoInitializeEx(0, COINIT_MULTITHREADED);
  hr = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);

  hr = CoCreateInstance(&CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, &IID_IWbemLocator, (LPVOID *) &WbemLocator);
  if (WbemLocator == NULL)
    goto exit;

  //connect to the WMI
  hr = WbemLocator->lpVtbl->ConnectServer(WbemLocator, L"ROOT\\CIMV2", NULL, NULL, NULL, 0, NULL, NULL, &WbemServices);   
  if (WbemServices == NULL)
    goto exit;

  //Run the WQL Query
  hr = WbemServices->lpVtbl->ExecQuery(WbemServices, L"WQL", L"SELECT ProcessId,CommandLine FROM Win32_Process", WBEM_FLAG_FORWARD_ONLY, NULL, &EnumWbem);
  if (EnumWbem == NULL)
    goto exit;

  // Iterate over the enumerator
  IWbemClassObject *result = NULL;
  ULONG returnedCount = 0;

  while((hr = EnumWbem->lpVtbl->Next(EnumWbem, WBEM_INFINITE, 1, &result, &returnedCount)) == S_OK) {
    VARIANT ProcessId;
    VARIANT CommandLine;
    
    // access the properties
    hr = result->lpVtbl->Get(result, L"ProcessId", 0, &ProcessId, 0, 0);
    hr = result->lpVtbl->Get(result, L"CommandLine", 0, &CommandLine, 0, 0);            
    if (!(CommandLine.vt==VT_NULL)){
      wprintf(L"%u  %s \r\n", ProcessId.uintVal, CommandLine.bstrVal);
      
      VECTOR_push_back(ret, bstr_to_str(CommandLine.bstrVal));
    }
    
    result->lpVtbl->Release(result);
  }


 exit:
  if (EnumWbem != NULL)
    EnumWbem->lpVtbl->Release(EnumWbem);
  if (WbemServices != NULL)
    WbemServices->lpVtbl->Release(WbemServices);
  if (WbemLocator != NULL)
    WbemLocator->lpVtbl->Release(WbemLocator);

  CoUninitialize();    
  //getchar();

  return ret;
}