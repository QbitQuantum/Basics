static INT_PTR WINAPI DevNotifyWndProc(
    HWND hWnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
    )
{
    LRESULT retval = 1;
    static HDEVNOTIFY hDeviceNotify;
    DEV_BROADCAST_HDR *arrival;
    DEV_BROADCAST_VOLUME *volume;

    switch (message)
    {
    case WM_CREATE:
        if (!DoRegisterDeviceInterface(
            GUID_DEVINTERFACE_DISK,
            hWnd,
            &hDeviceNotify))
        {
            perror("DoRegisterDeviceInterfaceToHwnd");
            ExitThread(1);
        }

        break;

    case WM_DEVICECHANGE:
    {
        DEV_BROADCAST_DEVICEINTERFACE *b = (DEV_BROADCAST_DEVICEINTERFACE *) lParam;

        switch (wParam)
        {
        case DBT_DEVICEARRIVAL:
            arrival = (DEV_BROADCAST_HDR *) lParam;
            LogDebug("DBT_DEVICEARRIVAL: type %d", arrival->dbch_devicetype);
            if (arrival->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                // New volume mounted.
                volume = (DEV_BROADCAST_VOLUME *) lParam;
                LogDebug("mask: 0x%x", volume->dbcv_unitmask);
                // Each bit corresponds to disk letter for the newly mounted volume.
                g_NewVolumeBitmask = volume->dbcv_unitmask;
                goto close;
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            LogDebug("DBT_DEVICEREMOVECOMPLETE");
            break;
        case DBT_DEVNODES_CHANGED:
            LogDebug("DBT_DEVNODES_CHANGED");
            break;
        default:
            LogWarning("Unknown device change: %d", wParam);
            break;
        }
    }
        break;

    close:
    case WM_CLOSE:
        if (!UnregisterDeviceNotification(hDeviceNotify))
        {
            perror("UnregisterDeviceNotification");
        }
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        // Send all other messages on to the default windows handler.
        retval = DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return retval;
}