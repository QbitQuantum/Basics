int __cdecl _tmain(int argc, const TCHAR** argv)
{
    int ret = 0;

    if (CheckEpoch())
        return 1;

    try
    {
        // set unexpected and terminate handlers
        // Note: we do this before Init() in case it attempts to call these handlers
        // TODO: move this into the Init() routine
        EXCEPTION_NAMESPACE set_terminate(tw_terminate_handler);
        EXCEPTION_NAMESPACE set_unexpected(tw_unexpected_handler);

        //cTWInit twInit( argv[0] );
        SiggenInit();

        cDebug::SetDebugLevel(cDebug::D_DETAIL);
        cSiggenCmdLine siggen;

        // first, process the command line
        if (argc < 2)
        {
            TCOUT << TSS_GetString(cSiggen, siggen::STR_SIGGEN_VERSION) << std::endl;
            TCOUT << TSS_GetString(cTW, tw::STR_VERSION) << std::endl;
            TCOUT << TSS_GetString(cTW, tw::STR_GET_HELP) << std::endl;

            ret = 1;
            goto exit;
        }

        //
        // Display the version info...
        // this is quick and dirty ... just the way I like it :-) -- mdb
        //
        if (_tcscmp(argv[1], _T("--version")) == 0)
        {
            TCOUT << TSS_GetString(cTW, tw::STR_VERSION_LONG) << std::endl;
            ret = 0;
            goto exit;
        }


        cCmdLineParser cmdLine;
        siggen.InitCmdLineParser(cmdLine);
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

        cCmdLineIter iter(cmdLine);
        if (iter.SeekToArg(cSiggenCmdLine::HELP))
        {
            TCOUT << TSS_GetString(cSiggen, siggen::STR_SIGGEN_VERSION) << std::endl;
            TCOUT << TSS_GetString(cTW, tw::STR_VERSION) << std::endl;
            TCOUT << TSS_GetString(cSiggen, siggen::STR_SIGGEN_USAGE) << std::endl;
            ret = 1;
            goto exit;
        }

        if (!siggen.Init(cmdLine))
        {
            TCOUT << TSS_GetString(cSiggen, siggen::STR_SIGGEN_VERSION) << std::endl;
            TCOUT << TSS_GetString(cTW, tw::STR_VERSION) << std::endl;
            TCOUT << TSS_GetString(cSiggen, siggen::STR_SIGGEN_USAGE) << std::endl;
            ret = 1;
            goto exit;
        }
        ret = siggen.Execute();

    } //end try block
    catch (eError& error)
    {
        cErrorReporter::PrintErrorMsg(error);
        ASSERT(false);
    }

exit:

    return ret;
} //end MAIN