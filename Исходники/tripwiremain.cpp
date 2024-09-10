///////////////////////////////////////////////////////////////////////////////
// main
///////////////////////////////////////////////////////////////////////////////
int __cdecl _tmain( int argc, const TCHAR* argv[ ], const TCHAR* envp[ ] )
{

    if (TimeBombExploded())
        return 8;

    int ret = 0;

    cTWInit twInit;
    

    try 
    {
        // set unexpected and terminate handlers
        // Note: we do this before Init() in case it attempts to call these handlers
        // TODO: move this into the Init() routine
        EXCEPTION_NAMESPACE set_terminate(tw_terminate_handler);
        EXCEPTION_NAMESPACE set_unexpected(tw_unexpected_handler);

        // Initialization
        //
        twInit.Init( argv[0] );
        TSS_Dependency( cTripwire );

        // set up the debug output
        cDebug::SetDebugLevel( cDebug::D_DEBUG/*D_DETAIL*//*D_NEVER*/ );
        

        // first, get the right mode...
        std::auto_ptr<iTWMode> pMode(cTWCmdLine::GetMode(argc, argv));
        if(! pMode.get())
        {
            // no valid mode passed; GetMode will display an appropriate string (include usage statement)
            ret = 8;
            goto exit;
        }

        // if version was requested, output version string and exit
        if (pMode.get()->GetModeID() == cTWCmdLine::MODE_VERSION)
        {
            TCOUT << TSS_GetString( cTW, tw::STR_VERSION_LONG) << std::endl;
            ret = 0;
            goto exit;
        }
        
        // process the command line
        cCmdLineParser cmdLine;
        pMode->InitCmdLineParser(cmdLine);
        try
        {
            cmdLine.Parse(argc, argv);
        }
        catch( eError& e )
        {
            cTWUtil::PrintErrorMsg(e);
            TCERR << TSS_GetString( cTW, tw::STR_GET_HELP) << std::endl;
            
            ret = 8;
            goto exit;
        }

        TSTRING commandLine = util_GetWholeCmdLine( argc, argv );

        #if IS_UNIX
        // erase the command line
        // TODO: it might be a good idea to move this to cTWUtil
        int i;
        for (i = 1; i < argc; ++i)
            memset((char*)argv[i], 0, strlen(argv[i])*sizeof(TCHAR));
        #endif

        cCmdLineIter iter(cmdLine);
        if (iter.SeekToArg(cTWCmdLine::HELP))
        {
            TCOUT << TSS_GetString( cTripwire, tripwire::STR_TRIPWIRE_VERSION) << std::endl;
            TCOUT << TSS_GetString( cTW, tw::STR_VERSION) << std::endl;
            //
            //Since --help was passed, exit after emitting a mode-specific usage statement.
            TCOUT << pMode->GetModeUsage();
            ret = 8;
            goto exit;
        }

        if (iter.SeekToArg(cTWCmdLine::VERBOSE))
        {
            TCOUT << TSS_GetString( cTW, tw::STR_VERSION) << std::endl;
        }

        // open up the config file, possibly using the passed in path
        cConfigFile config;
        TSTRING strConfigFile;
        cErrorReporter errorReporter;

        if( pMode->GetModeID() != cTWCmdLine::MODE_HELP )
        {
            try
            {
                //open cfg file
                cTWUtil::OpenConfigFile(config, cmdLine, cTWCmdLine::CFG_FILE, errorReporter, strConfigFile);
            }
            catch (eError& error)
            {
                TSTRING extra;
                extra += TSS_GetString( cTW, tw::STR_NEWLINE);
                extra += TSS_GetString( cTW, tw::STR_ERR_TWCFG_CANT_READ);

                cTWUtil::PrintErrorMsg( error, extra );
                ret = 8;
                goto exit;
            }
        }

        // ok, now we can initialize the mode object and have it execute
        pMode->SetCmdLine( commandLine );

        pMode->SetConfigFile( strConfigFile );

        if(! pMode->Init(config, cmdLine))
        {
            TCERR << TSS_GetString( cTW, tw::STR_GET_HELP) << std::endl;
            ret = 8;
            goto exit;
        }

        ret = pMode->Execute(&twInit.errorQueue);

    }//end try block

    catch (eError& error)
    {
        cTWUtil::PrintErrorMsg(error);
        ASSERT(false);
        ret = 8;
    }

    catch (std::bad_alloc e)
    {
        // Note: We use fputs rather than TCERR as it will probably require the
        // least amount of memory to do its thing.  If we ran out of memory we
        // need to do everything we can to get this string out to the user.
        fputs("*** Fatal exception: Out of memory\n", stderr);
        fputs("*** Exiting...\n", stderr);
        ret = 8;
    }

    catch (std::exception e)
    {
        TCERR << _T("*** Fatal exception: ");
        std::cerr << e.what() << std::endl;
        TCERR << _T("*** Exiting...\n");
        ret = 8;
    }

    /*
    catch (...)
    {
        TCERR << _T("*** Fatal exception occurred.\n");
        TCERR << _T("*** Exiting...\n");
        ret = 8;
    }
    */

exit:


    // print out the max memory usage...
/*
#ifdef _DEBUG
    TCOUT << _T("Maximum memory footprint = ") << gMaxAlloc << std::endl;
#endif
*/

    
    return ret;

} //end MAIN