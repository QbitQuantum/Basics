/*****************************************************************************
 wmain

*****************************************************************************/
DWORD
__cdecl
wmain(
    int     argc,
    LPWSTR  argv[]
    )
{
    HRESULT                 hr = S_OK;

    HCERTSTORE              hStore = NULL;
    PCCERT_CONTEXT          pCert = NULL;
    PCCERT_CONTEXT          pStoreCert = NULL;

    char                    szStoreProvider[ 256 ] = { "TestExt" };

    // Store provider name
    LPWSTR pwszStoreProvider = NULL;
    // Store name
    LPWSTR pwszStoreName = L"TestStoreName";

    LPWSTR pwszCertPath = NULL;


    int i;

    //
    // options
    //

    for( i=1; i<argc; i++ )
    {
        if ( lstrcmpW (argv[i], L"/?") == 0 ||
             lstrcmpW (argv[i], L"-?") == 0 ) 
        {
            Usage( L"SampleStoreProvider.exe" );
            goto CleanUp;
        }

        if( *argv[i] != L'-' )
            break;

        if ( lstrcmpW (argv[i], L"-s") == 0 )
        {
            if( i+1 >= argc )
            {
                hr = E_INVALIDARG;
                
                goto CleanUp;
            }

            pwszStoreName = argv[++i];
        }
        else
        if ( lstrcmpW (argv[i], L"-p") == 0 )
        {
            if( i+1 >= argc )
            {
                hr = E_INVALIDARG;
                
                goto CleanUp;
            }

            pwszStoreProvider = argv[++i];
        }

    }

    if( i >= argc )
    {
        hr = E_INVALIDARG;
        
        goto CleanUp;
    }

    pwszCertPath = argv[i++];

    // Load the certificate from the file passed in as cmd line parameter;    
    if (!CryptQueryObject(
                                CERT_QUERY_OBJECT_FILE,         //dwObjectType 
                                pwszCertPath,                   //pvObject
                                CERT_QUERY_CONTENT_FLAG_CERT,   //dwExpectedContentTypeFlags
                                CERT_QUERY_FORMAT_FLAG_ALL,     //dwExpectedFormatTypeFlags 
                                0,                              //dwFlags
                                0,                              //pdwMsgAndCertEncodingType 
                                0,                              //pdwContentType 
                                0,                              //pdwFormatType 
                                0,                              //phCertStore
                                0,                              //phMsg 
                                (const void**)&pCert            //ppvContext
                                ))
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        
        goto CleanUp;
    }

    // Open the store using the sample provider name
    if( NULL != pwszStoreProvider )
    {
        if( 1 < WideCharToMultiByte(
                                CP_ACP, 
                                WC_ERR_INVALID_CHARS, 
                                pwszStoreProvider,
                                -1, 
                                szStoreProvider, 
                                sizeof(szStoreProvider),
                                NULL,    
                                NULL
                                ))
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            
            goto CleanUp;
        }
    }

    hStore = CertOpenStore(
                                szStoreProvider,        // lpszStoreProvider
                                X509_ASN_ENCODING,      // dwMsgAndCertEncodingType
                                NULL,                   // hCryptProv
                                0,                      // dwFlags (will create it if does not exists)
                                (void*)pwszStoreName);  // pvPara
    if (hStore == NULL)
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        
        goto CleanUp;
    }

    // Add a certificate to store
    if(!CertAddCertificateContextToStore(
                                hStore,                             // hCertStore
                                pCert,                              // pCertContext
                                CERT_STORE_ADD_REPLACE_EXISTING,    // dwAddDisposition
                                NULL                                // ppStoreContext
                                ))
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        
        goto CleanUp;
    }


    pStoreCert = CertFindCertificateInStore(
                                hStore,                             // hCertStore
                                X509_ASN_ENCODING,                  // dwCertEncodingType
                                0,                                  // dwFindFlags
                                CERT_FIND_EXISTING,                 // dwFindType        
                                pCert,                              // pvFindPara
                                NULL                                // pPrevCertContext
                                );
    if (pStoreCert == NULL)
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        
        goto CleanUp;
    }

    hr = S_OK;

CleanUp:

    if( NULL != pCert )
        CertFreeCertificateContext(pCert);
    
    if( NULL != pStoreCert )
        CertFreeCertificateContext(pStoreCert);

    if( NULL != hStore )
        CertCloseStore(hStore, 0);

    if( FAILED( hr ))
    {
        ReportError( NULL, hr  );
    }

    return (DWORD)hr;
}