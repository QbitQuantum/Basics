STDAPI
AMovieDllRegisterServer2( BOOL bRegister )
{
  HRESULT hr = NOERROR;

  DbgLog((LOG_TRACE, 2, TEXT("AMovieDllRegisterServer2()")));

  // get file name (where g_hInst is the
  // instance handle of the filter dll)
  //
  WCHAR achFileName[MAX_PATH];

  // WIN95 doesn't support GetModuleFileNameW
  //
  {
    char achTemp[MAX_PATH];

    DbgLog((LOG_TRACE, 2, TEXT("- get module file name")));

    // g_hInst handle is set in our dll entry point. Make sure
    // DllEntryPoint in dllentry.cpp is called
    ASSERT(g_hInst != 0);

    if( 0 == GetModuleFileNameA( g_hInst
                              , achTemp
                              , sizeof(achTemp) ) )
    {
      // we've failed!
      DWORD dwerr = GetLastError();
      return AmHresultFromWin32(dwerr);
    }

    MultiByteToWideChar( CP_ACP
                       , 0L
                       , achTemp
                       , lstrlenA(achTemp) + 1
                       , achFileName
                       , NUMELMS(achFileName) );
  }

  //
  // first registering, register all OLE servers
  //
  if( bRegister )
  {
    DbgLog((LOG_TRACE, 2, TEXT("- register OLE Servers")));
    hr = RegisterAllServers( achFileName, TRUE );
  }

  //
  // next, register/unregister all filters
  //

  if( SUCCEEDED(hr) )
  {
    // init is ref counted so call just in case
    // we're being called cold.
    //
    DbgLog((LOG_TRACE, 2, TEXT("- CoInitialize")));
    hr = CoInitialize( (LPVOID)NULL );
    ASSERT( SUCCEEDED(hr) );

    // get hold of IFilterMapper2
    //
    DbgLog((LOG_TRACE, 2, TEXT("- obtain IFilterMapper2")));
    IFilterMapper2 *pIFM2 = 0;
    IFilterMapper *pIFM = 0;
    hr = CoCreateInstance( CLSID_FilterMapper2
                         , NULL
                         , CLSCTX_INPROC_SERVER
                         , IID_IFilterMapper2
                         , (void **)&pIFM2       );
    if(FAILED(hr))
    {
        DbgLog((LOG_TRACE, 2, TEXT("- trying IFilterMapper instead")));

        hr = CoCreateInstance(
            CLSID_FilterMapper,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_IFilterMapper,
            (void **)&pIFM);
    }
    if( SUCCEEDED(hr) )
    {
      // scan through array of CFactoryTemplates
      // registering servers and filters.
      //
      DbgLog((LOG_TRACE, 2, TEXT("- register Filters")));
      for( int i = 0; i < g_cTemplates; i++ )
      {
        // get i'th template
        //
        const CFactoryTemplate *pT = &g_Templates[i];

        if( NULL != pT->m_pAMovieSetup_Filter )
        {
          DbgLog((LOG_TRACE, 2, TEXT("- - register %ls"), (LPCWSTR)pT->m_Name ));

          if(pIFM2)
          {
              hr = AMovieSetupRegisterFilter2( pT->m_pAMovieSetup_Filter, pIFM2, bRegister );
          }
          else
          {
              hr = AMovieSetupRegisterFilter( pT->m_pAMovieSetup_Filter, pIFM, bRegister );
          }
        }

        // check final error for this pass
        // and break loop if we failed
        //
        if( FAILED(hr) )
          break;
      }

      // release interface
      //
      if(pIFM2)
          pIFM2->Release();
      else
          pIFM->Release();

    }

    // and clear up
    //
    CoFreeUnusedLibraries();
    CoUninitialize();
  }

  //
  // if unregistering, unregister all OLE servers
  //
  if( SUCCEEDED(hr) && !bRegister )
  {
    DbgLog((LOG_TRACE, 2, TEXT("- register OLE Servers")));
    hr = RegisterAllServers( achFileName, FALSE );
  }

  DbgLog((LOG_TRACE, 2, TEXT("- return %0x"), hr));
  return hr;
}