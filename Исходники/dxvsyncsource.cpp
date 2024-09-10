int DxVsyncSource::vsyncThread(void* context)
{
    DxVsyncSource* me = reinterpret_cast<DxVsyncSource*>(context);

    SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);

    D3DKMT_OPENADAPTERFROMHDC openAdapterParams = {};
    HMONITOR lastMonitor = nullptr;
    DEVMODEA monitorMode;
    monitorMode.dmSize = sizeof(monitorMode);

    while (SDL_AtomicGet(&me->m_Stopping) == 0) {
        D3DKMT_WAITFORVERTICALBLANKEVENT waitForVblankEventParams;
        NTSTATUS status;

        // If the monitor has changed from last time, open the new adapter
        HMONITOR currentMonitor = MonitorFromWindow(me->m_Window, MONITOR_DEFAULTTONEAREST);
        if (currentMonitor != lastMonitor) {
            MONITORINFOEXA monitorInfo = {};
            monitorInfo.cbSize = sizeof(monitorInfo);
            if (!GetMonitorInfoA(currentMonitor, &monitorInfo)) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "GetMonitorInfo() failed: %d",
                             GetLastError());
                SDL_Delay(10);
                continue;
            }

            if (!EnumDisplaySettingsA(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS, &monitorMode)) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "EnumDisplaySettings() failed: %d",
                             GetLastError());
                SDL_Delay(10);
                continue;
            }

            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                        "Monitor changed: %s %d Hz",
                        monitorInfo.szDevice,
                        monitorMode.dmDisplayFrequency);

            if (openAdapterParams.hAdapter != 0) {
                D3DKMT_CLOSEADAPTER closeAdapterParams = {};
                closeAdapterParams.hAdapter = openAdapterParams.hAdapter;
                me->m_D3DKMTCloseAdapter(&closeAdapterParams);
            }

            openAdapterParams.hDc = CreateDCA(nullptr, monitorInfo.szDevice, nullptr, nullptr);
            if (!openAdapterParams.hDc) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "CreateDC() failed: %d",
                             GetLastError());
                SDL_Delay(10);
                continue;
            }

            status = me->m_D3DKMTOpenAdapterFromHdc(&openAdapterParams);
            DeleteDC(openAdapterParams.hDc);

            if (status != STATUS_SUCCESS) {
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "D3DKMTOpenAdapterFromHdc() failed: %x",
                             status);
                SDL_Delay(10);
                continue;
            }

            lastMonitor = currentMonitor;
        }

        waitForVblankEventParams.hAdapter = openAdapterParams.hAdapter;
        waitForVblankEventParams.hDevice = 0;
        waitForVblankEventParams.VidPnSourceId = openAdapterParams.VidPnSourceId;

        status = me->m_D3DKMTWaitForVerticalBlankEvent(&waitForVblankEventParams);
        if (status != STATUS_SUCCESS) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "D3DKMTWaitForVerticalBlankEvent() failed: %x",
                         status);
            SDL_Delay(10);
            continue;
        }

        me->m_Pacer->vsyncCallback(1000 / me->m_DisplayFps);
    }

    if (openAdapterParams.hAdapter != 0) {
        D3DKMT_CLOSEADAPTER closeAdapterParams = {};
        closeAdapterParams.hAdapter = openAdapterParams.hAdapter;
        me->m_D3DKMTCloseAdapter(&closeAdapterParams);
    }

    return 0;
}