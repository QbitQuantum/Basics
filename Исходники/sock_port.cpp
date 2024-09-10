bool ENABLE_FIREWALL()
{
  BOOL couldEnable = false;
  HRESULT hr = S_OK;
  HRESULT comInit = E_FAIL;
  INetFwProfile* fwProfile = NULL;

  // Initialize COM.
#if 1
  comInit = CoInitialize( 0 );
#else
  comInit = CoInitializeEx(
              0,
              COINIT_APARTMENTTHREADED /*| COINIT_DISABLE_OLE1DDE */
              );
#endif

  // Ignore RPC_E_CHANGED_MODE; this just means that COM has already been
  // initialized with a different mode. Since we don't care what the mode is,
  // we'll just use the existing mode.
  if (comInit != RPC_E_CHANGED_MODE) {
    hr = comInit;
    if (FAILED(hr)) {
      fprintf( stderr, "CoInitializeEx failed: 0x%08lx\n", hr );
      goto error;
    }
  }

  // Retrieve the firewall profile currently in effect.
  hr = WindowsFirewallInitialize(&fwProfile);
  if (FAILED(hr)) {
    fprintf( stderr, "WindowsFirewallInitialize failed: 0x%08lx\n", hr );
    goto error;
  }

  HMODULE hm = GetModuleHandle( 0 );
  wchar_t path[512];
  if( !GetModuleFileNameW( hm, path, sizeof(path)/sizeof(wchar_t) ) ) {
    fprintf( stderr, "GetModuleFileName() failed: 0x%lx\n", GetLastError() );
    goto error;
  }

  // Add the application to the authorized application collection.
  hr = WindowsFirewallAddApp(
          fwProfile,
          path,
          L"Introduction Library User"
          );
  if (FAILED(hr)) {
    fprintf( stderr, "WindowsFirewallAddApp failed: 0x%08lx\n", hr );
    goto error;
  }

error:

  WindowsFirewallCleanup(fwProfile);

  if (SUCCEEDED(comInit)) {
    CoUninitialize();
  }

  return couldEnable != FALSE;
}