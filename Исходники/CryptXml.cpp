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
    HRESULT         hr = S_FALSE;
    int             i=0;
    LPCWSTR         wszFile = NULL;

    SIGN_PARA       Para = {0};

    Para.wszCanonicalizationMethod = wszURI_CANONICALIZATION_EXSLUSIVE_C14N;
    Para.wszHashAlgName = BCRYPT_SHA1_ALGORITHM;

    //
    // Options
    //

    for( i=1; i<argc; i++ )
    {
        if ( 0 == lstrcmpW (argv[i], L"/?") ||
             0 == lstrcmpW (argv[i], L"-?") ) 
        {
            Usage();
            goto CleanUp;
        }

        if( *argv[i] != L'-' )
            break;

        if ( 0 == lstrcmpW (argv[i], L"-kv") )
        {
            Para.fKV = TRUE;
        }
        else
        if ( 0 == lstrcmpW (argv[i], L"-cm") )
        {
            if( i+1 >= argc )
            {
                goto InvalidCommandLine;
            }

            Para.wszCanonicalizationMethod = argv[++i];
        }
        else
        if ( 0 == lstrcmpW (argv[i], L"-h") )
        {
            if( i+1 >= argc )
            {
                goto InvalidCommandLine;
            }

            Para.wszHashAlgName = argv[++i];
        }
        else
        if ( 0 == lstrcmpW (argv[i], L"-n") )
        {
            if( i+1 >= argc )
            {
                goto InvalidCommandLine;
            }

            Para.wszSubject = argv[++i];
        }
        else
        if ( 0 == lstrcmpW (argv[i], L"-kid") )
        {
            if( i+1 >= argc )
            {
                goto InvalidCommandLine;
            }

            Para.wszKeyInfoId = argv[++i];
        }
        else
        if ( 0 == lstrcmpW (argv[i], L"-sid") )
        {
            if( i+1 >= argc )
            {
                goto InvalidCommandLine;
            }

            Para.wszSignatureId = argv[++i];
        }
    }

    //
    // Commands
    //

    if( i >= argc )
    {
        goto InvalidCommandLine;
    }

    if( 0 == lstrcmpW( argv[i], WSZ_CMD_VERIFY ))
    {
        i++;
        if( i >= argc )
        {
            goto InvalidCommandLine;
        }

        wszFile = argv[i];

        hr = HrVerify( 
                                        wszFile 
                                        );

        if( FAILED(hr) )
        {
            goto CleanUp;
        }
    }
    else
    if( 0 == lstrcmpW( argv[i], WSZ_CMD_SIGN ))
    {
        i++;
        if( i+1 >= argc )
        {
            goto InvalidCommandLine;
        }

        wszFile = argv[i++];

        if( L'#' != *argv[i] )
        {
            if( i+2 >= argc )
            {
                goto InvalidCommandLine;
            }

            Para.wszFileIn  = argv[i++];
            Para.wszSignatureLocation = argv[i++];
        }
        
        if( i >= argc )
        {
            goto InvalidCommandLine;
        }

        // The rest of the command line must be {#Reference| [File] }

        hr = HrSign( 
                                        wszFile, 
                                        &Para, 
                                        (ULONG)(argc-i),
                                        &argv[i]
                                        );
        if( FAILED(hr) )
        {
            goto CleanUp;
        }
    }
    else
    {
        goto InvalidCommandLine;
    }

    //
    // End
    //

    hr = S_OK;
    goto CleanUp;

InvalidCommandLine:

    wprintf( L"ERROR: Invalid command line.\r\n" );

CleanUp:

    if( FAILED(hr) )
    {
        wprintf( L"ERROR: 0x%08x\r\n", hr );
    }

    return 0;
}