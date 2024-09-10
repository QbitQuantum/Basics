/////////////////////////////////////////////////////////////////////////
//  MAIN
//////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    String pegasusHome;
    Boolean shutdownOption = false;
    Boolean debugOutputOption = false;

//l10n
// Set Message loading to process locale
MessageLoader::_useProcessLocale = true;
//l10n

//l10n
#if defined(PEGASUS_OS_AIX) && defined(PEGASUS_HAS_MESSAGES)
setlocale(LC_ALL, "");
#endif

#ifndef PEGASUS_OS_TYPE_WINDOWS
    //
    // Get environment variables:
    //
#if defined(PEGASUS_OS_AIX) && defined(PEGASUS_USE_RELEASE_DIRS)
    pegasusHome = AIX_RELEASE_PEGASUS_HOME;
#elif defined(PEGASUS_OS_PASE) && defined(PEGASUS_USE_RELEASE_DIRS)
    pegasusHome = PASE_PROD_HOME;
#elif !defined(PEGASUS_USE_RELEASE_DIRS)
    const char* tmp = getenv("PEGASUS_HOME");

    if (tmp)
    {
        pegasusHome = tmp;
    }
#endif

    FileSystem::translateSlashes(pegasusHome);
#else

    // windows only
    char exeDir[MAX_PATH];
    HMODULE hExe = GetModuleHandle(NULL);
    GetModuleFileName(hExe, exeDir, sizeof(exeDir));
    *strrchr(exeDir, '\\') = '\0';
    pegasusHome = String(exeDir);

#endif

        // Get help, version, and shutdown options

        for (int i = 1; i < argc; )
        {
            const char* arg = argv[i];
            if(String::equal(arg,"--help"))
            {
                    PrintHelp(argv[0]);
                    exit(0);
            }
            else if(String::equal(arg,"--version"))
            {
                cout << _cimListenerProcess->getVersion() << endl;
                exit(0);
            }
            // Check for -option
            else if (*arg == '-')
            {
                // Get the option
                const char* option = arg + 1;

                //
                // Check to see if user asked for the version (-v option):
                //
                if (*option == OPTION_VERSION &&
                    strlen(option) == 1)
                {
                    cout << _cimListenerProcess->getVersion() << endl;
                    exit(0);
                }
                //
                // Check to see if user asked for help (-h option):
                //
                else if (*option == OPTION_HELP &&
                        (strlen(option) == 1))
                {
                    PrintHelp(argv[0]);
                    exit(0);
                }
#if !defined(PEGASUS_USE_RELEASE_DIRS)
                else if (*option == OPTION_HOME &&
                        (strlen(option) == 1))
                {
                    if (i + 1 < argc)
                    {
                        pegasusHome.assign(argv[i + 1]);
                    }
                    else
                    {
                        String opt(option);
                        MessageLoaderParms parms(
                                "src.Server.cimserver.MISSING_ARGUMENT",
                                         "Missing argument for option -$0",
                                         opt);
                        cout << MessageLoader::getMessage(parms) << endl;
                        exit(0);
                    }

                    memmove(&argv[i], &argv[i + 2],
                            (argc-i-1) * sizeof(char*));
                    argc -= 2;
                }
#endif
                //
                // Check to see if user asked for debug output (-X option):
                //
                else if (*option == OPTION_DEBUGOUTPUT &&
                        (strlen(option) == 1))
                {
                    MessageLoaderParms parms(
                        "src.Server.cimserver.UNSUPPORTED_DEBUG_OPTION",
                        "Unsupported debug output option is enabled.");
                    cout << MessageLoader::getMessage(parms) << endl;

                    debugOutputOption = true;

#if defined(PEGASUS_OS_HPUX)
                    System::bindVerbose = true;
#endif

                    // remove the option from the command line
                    memmove(&argv[i], &argv[i + 1], (argc-i) * sizeof(char*));
                    argc--;
                }
                //
                // Check to see if user asked for shutdown (-s option):
                //
                else if (*option == OPTION_SHUTDOWN &&
                        (strlen(option) == 1))
                {
                    //
                    // Check to see if shutdown has already been specified:
                    //
                    if (shutdownOption)
                    {
                        MessageLoaderParms parms(
                           "DynListener.cimlistener.DUPLICATE_SHUTDOWN_OPTION",
                           "Duplicate shutdown option specified.");

                        cout << MessageLoader::getMessage(parms) << endl;
                        exit(0);
                    }

                    shutdownOption = true;

                    // remove the option from the command line
                    memmove(&argv[i], &argv[i + 1], (argc-i) * sizeof(char*));
                    argc--;
                }
                else
                    i++;
            }
            else
                i++;
        }

    //
    // Set the value for pegasusHome property
    //
    DynamicListenerConfig::setListenerHome(pegasusHome);

    //
    // Do the plaform specific run
    //

    return _cimListenerProcess->platform_run(
        argc, argv, shutdownOption, debugOutputOption);
}