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
    HRESULT                     hr = S_OK;

    BOOL                        fSign = TRUE;        

    LPCWSTR                     pwszInputFile = NULL;
    LPCWSTR                     pwszOutputFile = NULL;

    BYTE                        *pbInput = NULL;
    DWORD                       cbInput = 0;    
    BYTE                        *pbOutput = NULL;
    DWORD                       cbOutput = 0;

    CERT_CHAIN_PARA             ChainPara         = {0};
    CERT_CHAIN_POLICY_PARA      ChainPolicy       = {0};
    CERT_CHAIN_POLICY_STATUS    PolicyStatus      = {0};
    PCCERT_CHAIN_CONTEXT        pChain = NULL;

    PCCERT_CONTEXT              pSignerCert = NULL;
    HCERTSTORE                  hStoreHandle = NULL;

    LPCWSTR                     pwszStoreName = L"MY";  // by default
    LPCWSTR                     pwszCName = L"Test";    // by default

    LPCWSTR                     wszHashAlgName = L"SHA1";

    int                         i;

    //
    // options
    //

    for( i=1; i<argc; i++ )
    {
        if ( lstrcmpW (argv[i], L"/?") == 0 ||
             lstrcmpW (argv[i], L"-?") == 0 ) 
        {
            Usage( L"cms_sign.exe" );
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
        if ( lstrcmpW (argv[i], L"-n") == 0 )
        {
            if( i+1 >= argc )
            {
                hr = E_INVALIDARG;
                goto CleanUp;
            }

            pwszCName = argv[++i];
        }
        else
        if ( lstrcmpW (argv[i], L"-a") == 0 )
        {
            if( i+1 >= argc )
            {
                hr = E_INVALIDARG;
                goto CleanUp;
            }

            wszHashAlgName = argv[++i];
        }
    }

    if( 0 == lstrcmpW (argv[i], L"SIGN"))
    {
        if( i+2 >= argc )
        {
            hr = E_INVALIDARG;
            goto CleanUp;
        }

        fSign = TRUE;
        pwszInputFile = argv[++i];
        pwszOutputFile = argv[++i];
    }
    else
    if( 0 == lstrcmpW (argv[i], L"VERIFY"))
    {
        if( i+1 >= argc )
        {
            hr = E_INVALIDARG;
            goto CleanUp;
        }

        fSign = FALSE;
        pwszInputFile = argv[++i];
    }
    else
    {
        hr = E_INVALIDARG;
        goto CleanUp;
    }

    if( i != argc-1 )
    {
        hr = E_INVALIDARG;
        goto CleanUp;
    }

    //-------------------------------------------------------------------
    // Open the certificate store to be searched.

    hStoreHandle = CertOpenStore(
                           CERT_STORE_PROV_SYSTEM,          // the store provider type
                           0,                               // the encoding type is not needed
                           NULL,                            // use the default HCRYPTPROV
                           CERT_SYSTEM_STORE_CURRENT_USER,  // set the store location in a 
                                                            //  registry location
                           pwszStoreName
                           );                               // the store name 

    if( NULL == hStoreHandle )
    {
        hr = HRESULT_FROM_WIN32( GetLastError() );
        goto CleanUp;
    }

    //
    // Load file
    // 

    hr = HrLoadFile(
                                            pwszInputFile,
                                            &pbInput,
                                            &cbInput
                                            );
    if( FAILED(hr) )
    {
        wprintf( L"Unable to read file: %s\n", pwszInputFile );
        goto CleanUp;
    }


    if( fSign )
    {
        //-------------------------------------------------------------------
        // Sign Message

        PCCRYPT_OID_INFO pOidInfo = NULL;
        CRYPT_SIGN_MESSAGE_PARA  SigParams = {0};

        // Create the MessageArray and the MessageSizeArray.
        const BYTE* MessageArray[] = {pbInput};
        DWORD MessageSizeArray[] = {cbInput};

        //
        // Get a certificate that has the specified Subject Name
        //

        pSignerCert = CertFindCertificateInStore(
                               hStoreHandle,
                               X509_ASN_ENCODING ,        // Use X509_ASN_ENCODING
                               0,                         // No dwFlags needed
                               CERT_FIND_SUBJECT_STR,     // Find a certificate with a
                                                          //  subject that matches the 
                                                          //  string in the next parameter
                               pwszCName,                 // The Unicode string to be found
                                                          //  in a certificate's subject
                               NULL);                     // NULL for the first call to the
                                                          //  function; In all subsequent
                                                          //  calls, it is the last pointer
                                                          //  returned by the function
        if( NULL == pSignerCert )
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto CleanUp;
        }

        //
        // Build a chain in order to include certs to the message
        //

        if( !CertGetCertificateChain(
                                    NULL,                  // use the default chain engine
                                    pSignerCert,           // pointer to the end certificate
                                    NULL,                  // use the default time
                                    NULL,                  // search no additional stores
                                    &ChainPara,            // use AND logic and enhanced key usage 
                                                           //  as indicated in the ChainPara 
                                                           //  data structure
                                    CERT_CHAIN_REVOCATION_CHECK_END_CERT,
                                    NULL,                  // currently reserved
                                    &pChain ))             // return a pointer to the chain created
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto CleanUp;
        }

        //
        // Verify that the chain complies with Base policy
        //

        ChainPolicy.cbSize = sizeof(CERT_CHAIN_POLICY_PARA);
        ChainPolicy.dwFlags = 0;

        PolicyStatus.cbSize = sizeof(CERT_CHAIN_POLICY_STATUS);

        ChainPolicy.pvExtraPolicyPara = NULL;
        if (!CertVerifyCertificateChainPolicy(
                                        CERT_CHAIN_POLICY_BASE,
                                        pChain,
                                        &ChainPolicy,
                                        &PolicyStatus))
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto CleanUp;
        }

        if( PolicyStatus.dwError != S_OK ) 
        {
            ReportError( L"Base Policy Chain Status Failure:", PolicyStatus.dwError  );
            hr = PolicyStatus.dwError;
        }

        // Initialize the signature structure.
        SigParams.cbSize = sizeof(SigParams);
        SigParams.dwMsgEncodingType = X509_ASN_ENCODING | PKCS_7_ASN_ENCODING;
        SigParams.pSigningCert = pSignerCert;
        SigParams.cAuthAttr = 0;
        SigParams.dwInnerContentType = 0;
        SigParams.cMsgCrl = 0;
        SigParams.cUnauthAttr = 0;
        SigParams.dwFlags = 0;
        SigParams.pvHashAuxInfo = NULL;
        SigParams.rgAuthAttr = NULL;

        //
        // Addd max of 8 certs to the message
        //

        PCCERT_CONTEXT   rgpMsgCert[8] = {NULL};
        SigParams.rgpMsgCert = rgpMsgCert;
        for( SigParams.cMsgCert=0; SigParams.cMsgCert<pChain->rgpChain[0]->cElement && SigParams.cMsgCert<8; SigParams.cMsgCert++ )
        {
            rgpMsgCert[SigParams.cMsgCert] = pChain->rgpChain[0]->rgpElement[SigParams.cMsgCert]->pCertContext;
        }

        //
        // Find OID
        //

        pOidInfo = CryptFindOIDInfo(
                                    CRYPT_OID_INFO_NAME_KEY,
                                    (void*)wszHashAlgName,
                                    CRYPT_HASH_ALG_OID_GROUP_ID
                                    );

        if( NULL == pOidInfo )
        {
            hr = CRYPT_E_UNKNOWN_ALGO;
            goto CleanUp;
        }

        SigParams.HashAlgorithm.pszObjId = (LPSTR)pOidInfo->pszOID;


        // First, get the size of the signed BLOB.
        if( !CryptSignMessage(
                                &SigParams,
                                FALSE,
                                1,
                                MessageArray,
                                &cbInput,
                                NULL,
                                &cbOutput ))
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto CleanUp;
        }

        // Allocate memory for the signed BLOB.
        pbOutput = (BYTE*)LocalAlloc( LPTR, cbOutput );
        if( NULL == pbOutput )
        {
            hr = HRESULT_FROM_WIN32( ERROR_OUTOFMEMORY );
            goto CleanUp;
        }

        // Get the signed message BLOB.
        if( !CryptSignMessage(
                                &SigParams,
                                FALSE,
                                1,
                                MessageArray,
                                MessageSizeArray,
                                pbOutput,
                                &cbOutput ))
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto CleanUp;
        }

        hr = HrSaveFile(
                                    pwszOutputFile,
                                    pbOutput,
                                    cbOutput
                                    );
        if( FAILED(hr) )
        {
            wprintf( L"Unable to save file: %s\n", pwszOutputFile );
            goto CleanUp;
        }

        wprintf( L"Successfully signed message using CryptSignMessage.\n");
    }
    else
    {
        //-------------------------------------------------------------------
        // Verify signed message

        CRYPT_VERIFY_MESSAGE_PARA   VerifyParams = {0};

        VerifyParams.cbSize = sizeof(VerifyParams);
        VerifyParams.dwMsgAndCertEncodingType = X509_ASN_ENCODING | PKCS_7_ASN_ENCODING;
        VerifyParams.hCryptProv = 0;
        VerifyParams.pfnGetSignerCertificate = NULL;
        VerifyParams.pvGetArg = NULL;

        // First, call CryptVerifyMessageSignature to get the length 
        // of the buffer needed to hold the decoded message.
        if( !CryptVerifyMessageSignature(
                                        &VerifyParams,
                                        0,
                                        pbInput,
                                        cbInput,
                                        NULL,
                                        &cbOutput,
                                        NULL))
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto CleanUp;
        }

        pbOutput = (BYTE*)LocalAlloc( LPTR, cbOutput );
        if( NULL == pbOutput )
        {
            hr = HRESULT_FROM_WIN32( ERROR_OUTOFMEMORY );
            goto CleanUp;
        }

        //---------------------------------------------------------------
        // Call CryptVerifyMessageSignature again to verify the signature
        // and, if successful, copy the decoded message into the buffer. 
        if( !CryptVerifyMessageSignature(
                                        &VerifyParams,
                                        0,
                                        pbInput,
                                        cbInput,
                                        pbOutput,
                                        &cbOutput,
                                        &pSignerCert))
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto CleanUp;
        }

        wprintf( L"Successfully verified signed message using CryptVerifyMessageSignature.\n");

        //
        // Build a chain in order to verify certificate trust
        //

        //
        // Instruction :   Create a certificate store from the CMS message and provide as a parameter to 
        //                 CertGetCertificateChain. This will ensure that all additional certificates from
		//                 the CMS message are used in chain building
        //                 Otherwise chain will be build using the local stores only.
        // 

        if( !CertGetCertificateChain(
                                    NULL,                  // use the default chain engine
                                    pSignerCert,           // pointer to the end certificate
                                    NULL,                  // use the default time
                                    NULL,                  // search no additional stores
                                    &ChainPara,            // use AND logic and enhanced key usage 
                                                           //  as indicated in the ChainPara 
                                                           //  data structure
                                    CERT_CHAIN_REVOCATION_CHECK_CHAIN_EXCLUDE_ROOT,
                                    NULL,                  // currently reserved
                                    &pChain ))             // return a pointer to the chain created
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto CleanUp;
        }

        //
        // Verify that the chain complies with Base policy
        //

        ChainPolicy.cbSize = sizeof(CERT_CHAIN_POLICY_PARA);
        ChainPolicy.dwFlags = 0;

        PolicyStatus.cbSize = sizeof(CERT_CHAIN_POLICY_STATUS);

        ChainPolicy.pvExtraPolicyPara = NULL;
        if (!CertVerifyCertificateChainPolicy(
                                        CERT_CHAIN_POLICY_BASE,
                                        pChain,
                                        &ChainPolicy,
                                        &PolicyStatus))
        {
            hr = HRESULT_FROM_WIN32( GetLastError() );
            goto CleanUp;
        }

        if( PolicyStatus.dwError != S_OK ) 
        {
            ReportError( L"Base Policy Chain Status Failure:", PolicyStatus.dwError  );
            hr = PolicyStatus.dwError;
        }
    }

    hr = S_OK;

    //-------------------------------------------------------------------
    // Clean up memory.

CleanUp:

    if( NULL != pbInput )
    {
        LocalFree(pbInput);
    }

    if( NULL != pbOutput )
    {
        LocalFree(pbOutput);
    }

    if( NULL != pChain )
    {
        CertFreeCertificateChain(pChain);
    }

    if( NULL != pSignerCert )
    {
        CertFreeCertificateContext(pSignerCert);
    }

    if( NULL != hStoreHandle)
    {
        CertCloseStore( hStoreHandle, 0 );
    }

    if( FAILED( hr ))
    {
        ReportError( NULL, hr  );
    }

    return (DWORD)hr;
} // End of main