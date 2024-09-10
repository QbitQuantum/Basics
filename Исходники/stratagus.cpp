/**
**  The main program: initialise, parse options and arguments.
**
**  @param argc  Number of arguments.
**  @param argv  Vector of arguments.
*/
int stratagusMain(int argc, char **argv)
{
#ifdef REDIRECT_OUTPUT
    RedirectOutput();
#endif
#ifdef USE_BEOS
    //  Parse arguments for BeOS
    beos_init(argc, argv);
#endif

    //  Setup some defaults.
#ifndef MAC_BUNDLE
    StratagusLibPath = ".";
#else
    freopen("/tmp/stdout.txt", "w", stdout);
    freopen("/tmp/stderr.txt", "w", stderr);
    // Look for the specified data set inside the application bundle
    // This should be a subdir of the Resources directory
    CFURLRef pluginRef = CFBundleCopyResourceURL(CFBundleGetMainBundle(),
                         CFSTR(MAC_BUNDLE_DATADIR), NULL, NULL);
    CFStringRef macPath = CFURLCopyFileSystemPath(pluginRef,  kCFURLPOSIXPathStyle);
    const char *pathPtr = CFStringGetCStringPtr(macPath, CFStringGetSystemEncoding());
    Assert(pathPtr);
    StratagusLibPath = pathPtr;
#endif

    Parameters &parameters = Parameters::Instance;
    parameters.SetDefaultValues();
    parameters.SetLocalPlayerNameFromEnv();

    if (argc > 0) {
        parameters.applicationName = argv[0];
    }

    // FIXME: Parse options before or after scripts?
    ParseCommandLine(argc, argv, parameters);
    // Init the random number generator.
    InitSyncRand();

    makedir(parameters.GetUserDirectory().c_str(), 0777);

    // Init Lua and register lua functions!
    InitLua();
    LuaRegisterModules();

    // Initialise AI module
    InitAiModule();

    LoadCcl(parameters.luaStartFilename);

    PrintHeader();
    PrintLicense();

    // Setup video display
    InitVideo();

    // Setup sound card
    if (!InitSound()) {
        InitMusic();
    }

#ifndef DEBUG           // For debug it's better not to have:
    srand(time(NULL));  // Random counter = random each start
#endif

    //  Show title screens.
    SetDefaultTextColors(FontYellow, FontWhite);
    LoadFonts();
    SetClipping(0, 0, Video.Width - 1, Video.Height - 1);
    Video.ClearScreen();
    ShowTitleScreens();

    // Init player data
    ThisPlayer = NULL;
    //Don't clear the Players strucure as it would erase the allowed units.
    // memset(Players, 0, sizeof(Players));
    NumPlayers = 0;

    UnitManager.Init(); // Units memory management
    PreMenuSetup();     // Load everything needed for menus

    MenuLoop();

    Exit(0);
    return 0;
}