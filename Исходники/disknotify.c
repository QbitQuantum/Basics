LRESULT CALLBACK MainWndDevicesSubclassProc(
    _In_ HWND hWnd,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam,
    _In_ UINT_PTR uIdSubclass,
    _In_ ULONG_PTR dwRefData
    )
{
    // The IOCTL_MOUNTMGR_CHANGE_NOTIFY callback would have been preferred but doesn't work from non-elevated processes?

    switch (uMsg)
    {
    case WM_DEVICECHANGE:
        {
            switch (wParam)
            {
            case DBT_DEVICEARRIVAL: // Drive letter added
            case DBT_DEVICEREMOVECOMPLETE: // Drive letter removed
                {
                    DEV_BROADCAST_HDR* deviceBroadcast = (DEV_BROADCAST_HDR*)lParam;

                    if (deviceBroadcast->dbch_devicetype == DBT_DEVTYP_VOLUME)
                    {
                        //DEV_BROADCAST_VOLUME* deviceVolume = (DEV_BROADCAST_VOLUME*)deviceBroadcast;

                        PhAcquireQueuedLockShared(&DiskDrivesListLock);

                        for (ULONG i = 0; i < DiskDrivesList->Count; i++)
                        {
                            PDV_DISK_ENTRY entry;

                            entry = PhReferenceObjectSafe(DiskDrivesList->Items[i]);

                            if (!entry)
                                continue;

                            // Reset the DiskIndexName so we can re-query the device letter on the next interval update.
                            PhClearReference(&entry->DiskIndexName);

                            PhDereferenceObjectDeferDelete(entry);
                        }

                        PhReleaseQueuedLockShared(&DiskDrivesListLock);
                    }
                }
            }

            goto DefaultWndProc;
        }
        break;
    }

    return DefSubclassProc(hWnd, uMsg, wParam, lParam);

DefaultWndProc:
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}