extern "C" DLL_EXPORT const char* _dbg_dbginit()
{
    if(!EngineCheckStructAlignment(UE_STRUCT_TITAN_ENGINE_CONTEXT, sizeof(TITAN_ENGINE_CONTEXT_t)))
        return "Invalid TITAN_ENGINE_CONTEXT_t alignment!";
    if(sizeof(TITAN_ENGINE_CONTEXT_t) != sizeof(REGISTERCONTEXT))
        return "Invalid REGISTERCONTEXT alignment!";
    dputs("Initializing wait objects...");
    waitinitialize();
    dputs("Initializing debugger...");
    dbginit();
    dputs("Initializing debugger functions...");
    dbgfunctionsinit();
    dputs("Setting JSON memory management functions...");
    json_set_alloc_funcs(json_malloc, json_free);
    dputs("Initializing capstone...");
    Capstone::GlobalInitialize();
    dputs("Initializing Yara...");
    if(yr_initialize() != ERROR_SUCCESS)
        return "Failed to initialize Yara!";
    dputs("Getting directory information...");
    wchar_t wszDir[deflen] = L"";
    if(!GetModuleFileNameW(hInst, wszDir, deflen))
        return "GetModuleFileNameW failed!";
    char dir[deflen] = "";
    strcpy_s(dir, StringUtils::Utf16ToUtf8(wszDir).c_str());
    int len = (int)strlen(dir);
    while(dir[len] != '\\')
        len--;
    dir[len] = 0;
    strcpy_s(alloctrace, dir);
    strcat_s(alloctrace, "\\alloctrace.txt");
    DeleteFileW(StringUtils::Utf8ToUtf16(alloctrace).c_str());
    setalloctrace(alloctrace);
    strcpy_s(dbbasepath, dir); //debug directory
    strcat_s(dbbasepath, "\\db");
    CreateDirectoryW(StringUtils::Utf8ToUtf16(dbbasepath).c_str(), 0); //create database directory
    char szLocalSymbolPath[MAX_PATH] = "";
    strcpy_s(szLocalSymbolPath, dir);
    strcat_s(szLocalSymbolPath, "\\symbols");

    char cachePath[MAX_SETTING_SIZE];
    if(!BridgeSettingGet("Symbols", "CachePath", cachePath) || !*cachePath)
    {
        strcpy_s(szSymbolCachePath, szLocalSymbolPath);
        BridgeSettingSet("Symbols", "CachePath", ".\\symbols");
    }
    else
    {
        if (_strnicmp(cachePath, ".\\", 2) == 0)
        {
            strncpy_s(szSymbolCachePath, dir, _TRUNCATE);
            strncat_s(szSymbolCachePath, cachePath + 1, _TRUNCATE);
        }
        else
        {
            // Trim the buffer to fit inside MAX_PATH
            strncpy_s(szSymbolCachePath, cachePath, _TRUNCATE);
        }

        if(strstr(szSymbolCachePath, "http://") || strstr(szSymbolCachePath, "https://"))
        {
            if(Script::Gui::MessageYesNo("It is strongly discouraged to use symbol servers in your path directly (use the store option instead).\n\nDo you want me to fix this?"))
            {
                strcpy_s(szSymbolCachePath, szLocalSymbolPath);
                BridgeSettingSet("Symbols", "CachePath", ".\\symbols");
            }
        }
    }
    dputs(szSymbolCachePath);
    SetCurrentDirectoryW(StringUtils::Utf8ToUtf16(dir).c_str());
    dputs("Allocating message stack...");
    gMsgStack = MsgAllocStack();
    if(!gMsgStack)
        return "Could not allocate message stack!";
    dputs("Initializing global script variables...");
    varinit();
    dputs("Registering debugger commands...");
    registercommands();
    dputs("Starting command loop...");
    hCommandLoopThread = CreateThread(0, 0, DbgCommandLoopThread, 0, 0, 0);
    char plugindir[deflen] = "";
    strcpy_s(plugindir, dir);
    strcat_s(plugindir, "\\plugins");
    CreateDirectoryW(StringUtils::Utf8ToUtf16(plugindir).c_str(), 0);
    dputs("Loading plugins...");
    pluginload(plugindir);
    dputs("Handling command line...");
    //handle command line
    int argc = 0;
    wchar_t** argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if(argc == 2) //we have an argument
    {
        String str = "init \"";
        str += StringUtils::Utf16ToUtf8(argv[1]);
        str += "\"";
        DbgCmdExec(str.c_str());
    }
    else if(argc == 5) //4 arguments (JIT)
    {
        if(_wcsicmp(argv[1], L"-a") == 0 && !_wcsicmp(argv[3], L"-e"))
        {
            String str = "attach .";
            str += StringUtils::Utf16ToUtf8(argv[2]);
            str += ", .";
            str += StringUtils::Utf16ToUtf8(argv[4]);
            DbgCmdExec(str.c_str());
        }
    }
    LocalFree(argv);
    dputs("Initialization successful!");
    bIsStopped = false;
    return nullptr;
}