/***************************************************************************************
 *  Method:
 *
 *
 *  Purpose:
 *
 *
 *  Parameters: 
 *
 *
 *  Return value:
 *
 *
 *  Notes:
 *
 ***************************************************************************************/
STDAPI DllRegisterServer()
{    
    HRESULT hr = S_OK;
    char  rcModule[_MAX_PATH];  
    const COCLASS_REGISTER *pCoClass;   

    
    DllUnregisterServer();
    GetModuleFileNameA( GetModuleInst(), rcModule, NumItems( rcModule ) );

    // for each item in the coclass list, register it
    for ( pCoClass = g_CoClasses; (SUCCEEDED( hr ) && (pCoClass->pClsid != NULL)); pCoClass++ )
    {
        // register the class with default values
        hr = REGUTIL::RegisterCOMClass( *pCoClass->pClsid, 
                                        g_szCoclassDesc, 
                                        g_szProgIDPrefix,
                                        g_iVersion, 
                                        pCoClass->szProgID, 
                                        g_szThreadingModel, 
                                        rcModule );                 
    } // for


    if ( FAILED( hr ) )
        DllUnregisterServer();
    
       
    return hr;
    
} // DllRegisterServer