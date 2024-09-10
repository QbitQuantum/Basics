BOOL CALLBACK DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    static bool isOleInitialized = false;
        
    switch (fdwReason) {
    case DLL_PROCESS_ATTACH:
        {
            isOleInitialized = OleInitialize(0) ? true : false;

			hmodAvcodec = LoadLibrary(L".\\plugins\\VideoSourcePlugin\\avcodec-57.dll");
			
			hmodAvformat = LoadLibrary(L".\\plugins\\VideoSourcePlugin\\avformat-57.dll");
	
			hmodMediaProcessSDK = LoadLibrary(L".\\plugins\\VideoSourcePlugin\\MediaProcessSDK.dll");
            // main plugin dll
            hmodVspPlugin = LoadLibrary(L".\\plugins\\VideoSourcePlugin\\VideoSourcePluginFFmpeg.dll"); 
			
            if (hmodVspPlugin != NULL) {
                InternalLoadPlugin = (LOADPLUGIN_PROC)GetProcAddress(hmodVspPlugin, "LoadPlugin");
                InternalUnloadPlugin = (UNLOADPLUGIN_PROC)GetProcAddress(hmodVspPlugin, "UnloadPlugin");
                InternalOnStartStream = (ONSTARTSTREAM_PROC)GetProcAddress(hmodVspPlugin, "OnStartStream");
                InternalOnStopStream = (ONSTOPSTREAM_PROC)GetProcAddress(hmodVspPlugin, "OnStopStream");
                InternalGetPluginName = (GETPLUGINNAME_PROC)GetProcAddress(hmodVspPlugin, "GetPluginName");
                InternalGetPluginDescription = (GETPLUGINDESCRIPTION_PROC)GetProcAddress(hmodVspPlugin, "GetPluginDescription");
            }
            break;
        }
    case DLL_PROCESS_DETACH:
        {
            if (isOleInitialized) {
                OleUninitialize();
            }

			if (hmodVspPlugin) FreeLibrary(hmodVspPlugin);
			if (hmodMediaProcessSDK) FreeLibrary(hmodMediaProcessSDK);
			
			if (hmodAvformat) FreeLibrary(hmodAvformat);
			if (hmodAvcodec) FreeLibrary(hmodAvcodec);
            break;
        }
    }
    return TRUE;
}