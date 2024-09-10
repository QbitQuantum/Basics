unsigned int __stdcall MyThreadFunction(void*) {
    EGraphicsApi graphicsApi = EGraphicsApi::D3D11;
    if (!LoadRenderApiImpl(graphicsApi)) {
        s_running.store(false);
        return 1;
    }

    // Init time
    QueryPerformanceFrequency(&s_perfFreq);
    QueryPerformanceCounter(&s_lastTime);

    GameInfo gameInfo;
    ZeroMemory(&gameInfo, sizeof(gameInfo));
    gameInfo.graphicsApi = graphicsApi;
    gameInfo.imguiState = ImGui::GetCurrentContext();
    //heapArea = new HeapArea(512 * 1024 * 1024);
    //memory::SimpleArena arena(heapArea);
    //gameInfo.allocator = &arena;
    gameInfo.CalculateDeltaTime = CalculateDeltaTime;
    gameInfo.gfxFuncs = g_renderApi;
    gameInfo.config = &s_config;
    gameInfo.controls = &s_controls;
    gameInfo.CreateThread = slCreateThread;
    gameInfo.reloadOnSave = true;

    // Hardware info
    {
        SYSTEM_INFO sysinfo;
        GetSystemInfo(&sysinfo);
        s_hardware.numLogicalThreads = (uint32_t) sysinfo.dwNumberOfProcessors;
    }
    
    gameInfo.hardware = &s_hardware;

    // ENet
    if (enet_initialize() != 0)
    {
        s_running.store(false);
        return 1;
    }

    // Main loop
    while (s_running.load())
    {
        // Check if graphics API change was requested
        if (gameInfo.graphicsApi != graphicsApi) {
            if (LoadRenderApiImpl(gameInfo.graphicsApi)) {
                graphicsApi = gameInfo.graphicsApi;
                g_renderApi = gameInfo.gfxFuncs;
            } else {
                gameInfo.graphicsApi = graphicsApi;
                gameInfo.gfxFuncs = g_renderApi;
            }
        }

#ifdef _DEBUG
        {
            // Reload DLL
            FILETIME NewDLLWriteTime = Win32GetLastWriteTime((char*)s_dllName);

            // If the .DLL is being written to, the last write time may change multiple times
            // So we need to add a cooldown
            LARGE_INTEGER currentTime;
            QueryPerformanceCounter(&currentTime);

            if (CompareFileTime(&NewDLLWriteTime, &s_gameFuncs.DLLLastWriteTime) != 0
                && (currentTime.QuadPart - s_lastDLLLoadTime.QuadPart) / s_perfFreq.QuadPart >= 1) {

                if (s_gameFuncs.dll) {
                    FreeLibrary(s_gameFuncs.dll);
                }

                s_gameFuncs = LoadGameFuncs();
                g_LogInfo("Reloaded DLL.");
            } else {
                // Ignore changes
                s_gameFuncs.DLLLastWriteTime = NewDLLWriteTime;
            }
        }
#endif

        // Reload Lua
        if (gameInfo.reloadOnSave) {
            DWORD obj = WaitForSingleObject(hDirectoryChange, 0);
            if (obj == WAIT_OBJECT_0) {
                if (!FindNextChangeNotification(hDirectoryChange)) {
                    g_LogInfo("Error: FindNextChangeNotification failed.");
                }
                
                // TODO: Change only of lua files changed (or make separate lua directory)
                LARGE_INTEGER currentTime;
                static LARGE_INTEGER s_lastLuaLoadTime;
                QueryPerformanceCounter(&currentTime);

                if ((currentTime.QuadPart - s_lastLuaLoadTime.QuadPart) / s_perfFreq.QuadPart >= 1) {
                    s_lastLuaLoadTime = currentTime;
                    gameInfo.reloadLua = true;
                }
            }
        }

        ParseMessages();

        g_renderApi->ImGuiNewFrame();
        s_controls.BeginFrame();

        s_gameFuncs.UpdateGame(&gameInfo);

        s_controls.EndFrame();

        // Rendering
        g_renderApi->Render();
    }

    s_gameFuncs.DestroyGame(&gameInfo);
    g_renderApi->Destroy();
    ImGui::Shutdown();
    g_renderApi = nullptr;

    //delete heapArea;

    enet_deinitialize();

    return 0;
}