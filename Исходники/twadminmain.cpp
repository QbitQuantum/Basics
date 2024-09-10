int __cdecl _tmain(int argc, const TCHAR* argv[], const TCHAR* envp[])
{


    int ret = 0;

    if (CheckEpoch())
        return 1;

    cTWInit twInit;

    try
    {
        // set unexpected and terminate handlers
        // Note: we do this before Init() in case it attempts to call these handlers
        // TODO: move this into the Init() routine
        EXCEPTION_NAMESPACE set_terminate(tw_terminate_handler);
        EXCEPTION_NAMESPACE set_unexpected(tw_unexpected_handler);

        twInit.Init(argv[0]);
        TSS_Dependency(cTWAdmin);

        // set up the debug output
        cDebug::SetDebugLevel(cDebug::D_DEBUG);


        // first, get the right mode...
        TW_UNIQUE_PTR<iTWAMode> pMode(cTWAdminCmdLine::GetMode(argc, argv));
        if (!pMode.get())
        {
            // no valid mode passed; GetMode will display an appropriate string (include usage statement)
            ret = 1;
            goto exit;
        }

        // if version was requested, output version string and exit
        if (pMode.get()->GetModeID() == cTWAdminCmdLine::MODE_VERSION)
        {
            TCOUT << TSS_GetString(cTW, tw::STR_VERSION_LONG) << std::endl;
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
        catch (eError& e)
        {
            cTWUtil::PrintErrorMsg(e);
            TCERR << TSS_GetString(cTW, tw::STR_GET_HELP) << std::endl;

            ret = 1;
            goto exit;
        }

        // erase the command line
        // TODO: it might be a good idea to move this to cTWUtil
        int i;
        for (i = 1; i < argc; ++i)
            memset((char*)argv[i], 0, strlen(argv[i]) * sizeof(TCHAR));

        cCmdLineIter iter(cmdLine);
        if (iter.SeekToArg(cTWAdminCmdLine::HELP))
        {
            TCOUT << TSS_GetString(cTWAdmin, twadmin::STR_TWADMIN_VERSION) << std::endl;
            TCOUT << TSS_GetString(cTW, tw::STR_VERSION) << std::endl;
            //Output a mode specific usage statement
            TCOUT << pMode->GetModeUsage();
            ret = 1;
            goto exit;
        }

        if (iter.SeekToArg(cTWAdminCmdLine::VERBOSE))
        {
            TCERR << TSS_GetString(cTW, tw::STR_VERSION) << std::endl;
        }

        // open up the config file, possibly using the passed in path
        cConfigFile      config;
        bool             configFileOpened = false;
        cErrorBucketNull errorNull; // don't spit errors to the user

        if (pMode->GetModeID() != cTWAdminCmdLine::MODE_GENERATE_KEYS &&
            pMode->GetModeID() != cTWAdminCmdLine::MODE_CHANGE_PASSPHRASES &&
            pMode->GetModeID() != cTWAdminCmdLine::MODE_CREATE_CONFIG &&
            pMode->GetModeID() != cTWAdminCmdLine::MODE_PRINT_CONFIG &&
            pMode->GetModeID() != cTWAdminCmdLine::MODE_HELP)
        {
            try
            {
                //open cfg file
                TSTRING cfgPath;
                cTWUtil::OpenConfigFile(config, cmdLine, cTWAdminCmdLine::CFG_FILE, errorNull, cfgPath);
                pMode->SetCfgFilePath(cfgPath);
                configFileOpened = true;
            }
            catch (eError& error)
            {
                TSTRING extra;
                extra += TSS_GetString(cTW, tw::STR_NEWLINE);
                extra += TSS_GetString(cTWAdmin, twadmin::STR_ERR2_CONFIG_OPEN);
                cTWUtil::PrintErrorMsg(error, extra);
                ret = 1;
                goto exit;
            }
        }

        // ok, now we can initialize the mode object and have it execute
        if (!pMode->Init(configFileOpened ? &config : NULL, cmdLine))
        {
            TCERR << TSS_GetString(cTW, tw::STR_GET_HELP) << std::endl;
            ret = 1;
            goto exit;
        }

        ret = pMode->Execute(&twInit.errorQueue);
    } //end try block

    catch (eError& error)
    {
        cTWUtil::PrintErrorMsg(error);
        ASSERT(false);
        ret = 1;
    }

    catch (std::bad_alloc& e)
    {
        TCERR << _T("*** Fatal exception: Out of memory ");
        TCERR << _T("*** Exiting...\n");
        ret = 1;
    }

    catch (std::exception& e)
    {
        TCERR << _T("*** Fatal exception: ");
        std::cerr << e.what() << std::endl;
        TCERR << _T("*** Exiting...\n");
        ret = 1;
    }

    /*
    catch (...)
    {
        TCERR << _T("*** Fatal exception occurred.\n");
        TCERR << _T("*** Exiting...\n");
        ret = 1;
    }
    */

exit:


    return ret;
}