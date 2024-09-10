bool CWinSystemWin32::UpdateResolutionsInternal()
{

    DISPLAY_DEVICEW ddAdapter;
    ZeroMemory(&ddAdapter, sizeof(ddAdapter));
    ddAdapter.cb = sizeof(ddAdapter);
    DWORD adapter = 0;

    while (EnumDisplayDevicesW(NULL, adapter, &ddAdapter, 0))
    {
        // Exclude displays that are not part of the windows desktop. Using them is too different: no windows,
        // direct access with GDI CreateDC() or DirectDraw for example. So it may be possible to play video, but GUI?
        if (!(ddAdapter.StateFlags & DISPLAY_DEVICE_MIRRORING_DRIVER) && (ddAdapter.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP))
        {
            DISPLAY_DEVICEW ddMon;
            ZeroMemory(&ddMon, sizeof(ddMon));
            ddMon.cb = sizeof(ddMon);
            bool foundScreen = false;
            DWORD screen = 0;

            // Just look for the first active output, we're actually only interested in the information at the adapter level.
            while (EnumDisplayDevicesW(ddAdapter.DeviceName, screen, &ddMon, 0))
            {
                if (ddMon.StateFlags & (DISPLAY_DEVICE_ACTIVE | DISPLAY_DEVICE_ATTACHED))
                {
                    foundScreen = true;
                    break;
                }
                ZeroMemory(&ddMon, sizeof(ddMon));
                ddMon.cb = sizeof(ddMon);
                screen++;
            }
            // Remoting returns no screens. Handle with a dummy screen.
            if (!foundScreen && screen == 0)
            {
                lstrcpyW(ddMon.DeviceString, L"Dummy Monitor"); // safe: large static array
                foundScreen = true;
            }

            if (foundScreen)
            {
                std::string monitorStr, adapterStr;
                g_charsetConverter.wToUTF8(ddMon.DeviceString, monitorStr);
                g_charsetConverter.wToUTF8(ddAdapter.DeviceString, adapterStr);
                CLog::Log(LOGNOTICE, "Found screen: %s on %s, adapter %d.", monitorStr.c_str(), adapterStr.c_str(), adapter);

                // get information about the display's current position and display mode
                //! @todo for Windows 7/Server 2008 and up, Microsoft recommends QueryDisplayConfig() instead, the API used by the control panel.
                DEVMODEW dm;
                ZeroMemory(&dm, sizeof(dm));
                dm.dmSize = sizeof(dm);
                if (EnumDisplaySettingsExW(ddAdapter.DeviceName, ENUM_CURRENT_SETTINGS, &dm, 0) == FALSE)
                    EnumDisplaySettingsExW(ddAdapter.DeviceName, ENUM_REGISTRY_SETTINGS, &dm, 0);

                // get the monitor handle and workspace
                HMONITOR hm = 0;
                POINT pt = { dm.dmPosition.x, dm.dmPosition.y };
                hm = MonitorFromPoint(pt, MONITOR_DEFAULTTONULL);

                MONITOR_DETAILS md = {};

                md.MonitorNameW = ddMon.DeviceString;
                md.CardNameW = ddAdapter.DeviceString;
                md.DeviceNameW = ddAdapter.DeviceName;

                // width x height @ x,y - bpp - refresh rate
                // note that refresh rate information is not available on Win9x
                md.ScreenWidth = dm.dmPelsWidth;
                md.ScreenHeight = dm.dmPelsHeight;
                md.hMonitor = hm;
                md.RefreshRate = dm.dmDisplayFrequency;
                md.Bpp = dm.dmBitsPerPel;
                md.Interlaced = (dm.dmDisplayFlags & DM_INTERLACED) ? true : false;

                m_MonitorsInfo.push_back(md);

                // Careful, some adapters don't end up in the vector (mirroring, no active output, etc.)
                if (ddAdapter.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
                    m_nPrimary = m_MonitorsInfo.size() -1;

            }
        }
        ZeroMemory(&ddAdapter, sizeof(ddAdapter));
        ddAdapter.cb = sizeof(ddAdapter);
        adapter++;
    }
    return 0;
}