/**
\brief Loads plugins from a specified directory.
\param pluginDir The directory to load plugins from.
*/
void pluginload(const char* pluginDir)
{
    //load new plugins
    wchar_t currentDir[deflen] = L"";
    GetCurrentDirectoryW(deflen, currentDir);
    SetCurrentDirectoryW(StringUtils::Utf8ToUtf16(pluginDir).c_str());
    char searchName[deflen] = "";
#ifdef _WIN64
    sprintf(searchName, "%s\\*.dp64", pluginDir);
#else
    sprintf(searchName, "%s\\*.dp32", pluginDir);
#endif // _WIN64
    WIN32_FIND_DATAW foundData;
    HANDLE hSearch = FindFirstFileW(StringUtils::Utf8ToUtf16(searchName).c_str(), &foundData);
    if(hSearch == INVALID_HANDLE_VALUE)
    {
        SetCurrentDirectoryW(currentDir);
        return;
    }
    PLUG_DATA pluginData;
    do
    {
        //set plugin data
        pluginData.initStruct.pluginHandle = curPluginHandle;
        char szPluginPath[MAX_PATH] = "";
        sprintf_s(szPluginPath, "%s\\%s", pluginDir, StringUtils::Utf16ToUtf8(foundData.cFileName).c_str());
        pluginData.hPlugin = LoadLibraryW(StringUtils::Utf8ToUtf16(szPluginPath).c_str()); //load the plugin library
        if(!pluginData.hPlugin)
        {
            dprintf("[PLUGIN] Failed to load plugin: %s\n", StringUtils::Utf16ToUtf8(foundData.cFileName).c_str());
            continue;
        }
        pluginData.pluginit = (PLUGINIT)GetProcAddress(pluginData.hPlugin, "pluginit");
        if(!pluginData.pluginit)
        {
            dprintf("[PLUGIN] Export \"pluginit\" not found in plugin: %s\n", StringUtils::Utf16ToUtf8(foundData.cFileName).c_str());
            FreeLibrary(pluginData.hPlugin);
            continue;
        }
        pluginData.plugstop = (PLUGSTOP)GetProcAddress(pluginData.hPlugin, "plugstop");
        pluginData.plugsetup = (PLUGSETUP)GetProcAddress(pluginData.hPlugin, "plugsetup");
        //auto-register callbacks for certain export names
        CBPLUGIN cbPlugin;
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBALLEVENTS");
        if(cbPlugin)
        {
            pluginregistercallback(curPluginHandle, CB_INITDEBUG, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_STOPDEBUG, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_CREATEPROCESS, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_EXITPROCESS, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_CREATETHREAD, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_EXITTHREAD, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_SYSTEMBREAKPOINT, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_LOADDLL, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_UNLOADDLL, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_OUTPUTDEBUGSTRING, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_EXCEPTION, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_BREAKPOINT, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_PAUSEDEBUG, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_RESUMEDEBUG, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_STEPPED, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_ATTACH, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_DETACH, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_DEBUGEVENT, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_MENUENTRY, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_WINEVENT, cbPlugin);
            pluginregistercallback(curPluginHandle, CB_WINEVENTGLOBAL, cbPlugin);
        }
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBINITDEBUG");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_INITDEBUG, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBSTOPDEBUG");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_STOPDEBUG, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBCREATEPROCESS");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_CREATEPROCESS, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBEXITPROCESS");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_EXITPROCESS, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBCREATETHREAD");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_CREATETHREAD, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBEXITTHREAD");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_EXITTHREAD, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBSYSTEMBREAKPOINT");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_SYSTEMBREAKPOINT, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBLOADDLL");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_LOADDLL, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBUNLOADDLL");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_UNLOADDLL, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBOUTPUTDEBUGSTRING");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_OUTPUTDEBUGSTRING, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBEXCEPTION");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_EXCEPTION, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBBREAKPOINT");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_BREAKPOINT, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBPAUSEDEBUG");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_PAUSEDEBUG, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBRESUMEDEBUG");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_RESUMEDEBUG, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBSTEPPED");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_STEPPED, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBATTACH");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_ATTACH, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBDETACH");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_DETACH, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBDEBUGEVENT");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_DEBUGEVENT, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBMENUENTRY");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_MENUENTRY, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBWINEVENT");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_WINEVENT, cbPlugin);
        cbPlugin = (CBPLUGIN)GetProcAddress(pluginData.hPlugin, "CBWINEVENTGLOBAL");
        if(cbPlugin)
            pluginregistercallback(curPluginHandle, CB_WINEVENTGLOBAL, cbPlugin);
        //init plugin
        //TODO: handle exceptions
        if(!pluginData.pluginit(&pluginData.initStruct))
        {
            dprintf("[PLUGIN] pluginit failed for plugin: %s\n", foundData.cFileName);
            FreeLibrary(pluginData.hPlugin);
            continue;
        }
        else if(pluginData.initStruct.sdkVersion < PLUG_SDKVERSION) //the plugin SDK is not compatible
        {
            dprintf("[PLUGIN] %s is incompatible with this SDK version\n", pluginData.initStruct.pluginName);
            FreeLibrary(pluginData.hPlugin);
            continue;
        }
        else
            dprintf("[PLUGIN] %s v%d Loaded!\n", pluginData.initStruct.pluginName, pluginData.initStruct.pluginVersion);
        //add plugin menu
        int hNewMenu = GuiMenuAdd(GUI_PLUGIN_MENU, pluginData.initStruct.pluginName);
        if(hNewMenu == -1)
        {
            dprintf("[PLUGIN] GuiMenuAdd(GUI_PLUGIN_MENU) failed for plugin: %s\n", pluginData.initStruct.pluginName);
            pluginData.hMenu = -1;
        }
        else
        {
            PLUG_MENU newMenu;
            newMenu.hEntryMenu = hNewMenu;
            newMenu.hEntryPlugin = -1;
            newMenu.pluginHandle = pluginData.initStruct.pluginHandle;
            pluginMenuList.push_back(newMenu);
            pluginData.hMenu = newMenu.hEntryMenu;
        }
        //add disasm plugin menu
        hNewMenu = GuiMenuAdd(GUI_DISASM_MENU, pluginData.initStruct.pluginName);
        if(hNewMenu == -1)
        {
            dprintf("[PLUGIN] GuiMenuAdd(GUI_DISASM_MENU) failed for plugin: %s\n", pluginData.initStruct.pluginName);
            pluginData.hMenu = -1;
        }
        else
        {
            PLUG_MENU newMenu;
            newMenu.hEntryMenu = hNewMenu;
            newMenu.hEntryPlugin = -1;
            newMenu.pluginHandle = pluginData.initStruct.pluginHandle;
            pluginMenuList.push_back(newMenu);
            pluginData.hMenuDisasm = newMenu.hEntryMenu;
        }
        //add dump plugin menu
        hNewMenu = GuiMenuAdd(GUI_DUMP_MENU, pluginData.initStruct.pluginName);
        if(hNewMenu == -1)
        {
            dprintf("[PLUGIN] GuiMenuAdd(GUI_DUMP_MENU) failed for plugin: %s\n", pluginData.initStruct.pluginName);
            pluginData.hMenu = -1;
        }
        else
        {
            PLUG_MENU newMenu;
            newMenu.hEntryMenu = hNewMenu;
            newMenu.hEntryPlugin = -1;
            newMenu.pluginHandle = pluginData.initStruct.pluginHandle;
            pluginMenuList.push_back(newMenu);
            pluginData.hMenuDump = newMenu.hEntryMenu;
        }
        //add stack plugin menu
        hNewMenu = GuiMenuAdd(GUI_STACK_MENU, pluginData.initStruct.pluginName);
        if(hNewMenu == -1)
        {
            dprintf("[PLUGIN] GuiMenuAdd(GUI_STACK_MENU) failed for plugin: %s\n", pluginData.initStruct.pluginName);
            pluginData.hMenu = -1;
        }
        else
        {
            PLUG_MENU newMenu;
            newMenu.hEntryMenu = hNewMenu;
            newMenu.hEntryPlugin = -1;
            newMenu.pluginHandle = pluginData.initStruct.pluginHandle;
            pluginMenuList.push_back(newMenu);
            pluginData.hMenuStack = newMenu.hEntryMenu;
        }
        pluginList.push_back(pluginData);
        //setup plugin
        if(pluginData.plugsetup)
        {
            PLUG_SETUPSTRUCT setupStruct;
            setupStruct.hwndDlg = GuiGetWindowHandle();
            setupStruct.hMenu = pluginData.hMenu;
            setupStruct.hMenuDisasm = pluginData.hMenuDisasm;
            setupStruct.hMenuDump = pluginData.hMenuDump;
            setupStruct.hMenuStack = pluginData.hMenuStack;
            pluginData.plugsetup(&setupStruct);
        }
        curPluginHandle++;
    }
    while(FindNextFileW(hSearch, &foundData));
    SetCurrentDirectoryW(currentDir);
}