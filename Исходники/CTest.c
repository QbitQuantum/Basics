int T_CTEST_EXPORT2
initArgs( int argc, const char* const argv[], ArgHandlerPtr argHandler, void *context)
{
    int                i;
    int                argSkip = 0;

    VERBOSITY = FALSE;
    ERR_MSG = TRUE;

    ARGV_0=argv[0];

    for( i=1; i<argc; i++)
    {
        if ( argv[i][0] == '/' )
        {
            /* We don't run the tests here. */
            continue;
        }
        else if ((strcmp( argv[i], "-a") == 0) || (strcmp(argv[i],"-all") == 0))
        {
            /* We don't run the tests here. */
            continue;
        }
        else if (strcmp( argv[i], "-v" )==0 || strcmp( argv[i], "-verbose")==0)
        {
            VERBOSITY = TRUE;
        }
        else if (strcmp( argv[i], "-l" )==0 )
        {
            /* doList = TRUE; */
        }
        else if (strcmp( argv[i], "-e1") == 0)
        {
            QUICK = -1;
        }
        else if (strcmp( argv[i], "-e") ==0)
        {
            QUICK = 0;
        }
        else if (strcmp( argv[i], "-w") ==0)
        {
            WARN_ON_MISSING_DATA = TRUE;
        }
        else if (strcmp( argv[i], "-m") ==0)
        {
            UErrorCode errorCode = U_ZERO_ERROR;
            if (i+1 < argc) {
                char *endPtr = NULL;
                i++;
                MINIMUM_MEMORY_SIZE_FAILURE = (size_t)strtol(argv[i], &endPtr, 10);
                if (endPtr == argv[i]) {
                    printf("Can't parse %s\n", argv[i]);
                    help(argv[0]);
                    return 0;
                }
                if (*endPtr == '-') {
                    char *maxPtr = endPtr+1;
                    endPtr = NULL;
                    MAXIMUM_MEMORY_SIZE_FAILURE = (size_t)strtol(maxPtr, &endPtr, 10);
                    if (endPtr == argv[i]) {
                        printf("Can't parse %s\n", argv[i]);
                        help(argv[0]);
                        return 0;
                    }
                }
            }
            /* Use the default value */
            u_setMemoryFunctions(NULL, ctest_libMalloc, ctest_libRealloc, ctest_libFree, &errorCode);
            if (U_FAILURE(errorCode)) {
                printf("u_setMemoryFunctions returned %s\n", u_errorName(errorCode));
                return 0;
            }
        }
        else if(strcmp( argv[i], "-n") == 0 || strcmp( argv[i], "-no_err_msg") == 0)
        {
            ERR_MSG = FALSE;
        }
        else if (strcmp( argv[i], "-r") == 0)
        {
            if (!REPEAT_TESTS_INIT) {
                REPEAT_TESTS++;
            }
        }
        else if (strcmp( argv[i], "-x") == 0)
        {
          if(++i>=argc) {
            printf("* Error: '-x' option requires an argument. usage: '-x outfile.xml'.\n");
            return 0;
          }
          if(ctest_xml_setFileName(argv[i])) { /* set the name */
            return 0;
          }
        }
        else if (strcmp( argv[i], "-t_info") == 0) {
            ICU_TRACE = UTRACE_INFO;
        }
        else if (strcmp( argv[i], "-t_error") == 0) {
            ICU_TRACE = UTRACE_ERROR;
        }
        else if (strcmp( argv[i], "-t_warn") == 0) {
            ICU_TRACE = UTRACE_WARNING;
        }
        else if (strcmp( argv[i], "-t_verbose") == 0) {
            ICU_TRACE = UTRACE_VERBOSE;
        }
        else if (strcmp( argv[i], "-t_oc") == 0) {
            ICU_TRACE = UTRACE_OPEN_CLOSE;
        }
        else if (strcmp( argv[i], "-h" )==0 || strcmp( argv[i], "--help" )==0)
        {
            help( argv[0] );
            return 0;
        }
        else if (argHandler != NULL && (argSkip = argHandler(i, argc, argv, context)) > 0)
        {
            i += argSkip - 1;
        }
        else
        {
            printf("* unknown option: %s\n", argv[i]);
            help( argv[0] );
            return 0;
        }
    }
    if (ICU_TRACE != UTRACE_OFF) {
        utrace_setFunctions(NULL, TraceEntry, TraceExit, TraceData);
        utrace_setLevel(ICU_TRACE);
    }

    return 1; /* total error count */
}