INT_PTR CALLBACK DiskDriveOptionsDlgProc(
    _In_ HWND hwndDlg,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    )
{
    PDV_DISK_OPTIONS_CONTEXT context = NULL;

    if (uMsg == WM_INITDIALOG)
    {
        context = (PDV_DISK_OPTIONS_CONTEXT)PhAllocate(sizeof(DV_DISK_OPTIONS_CONTEXT));
        memset(context, 0, sizeof(DV_DISK_OPTIONS_CONTEXT));

        SetProp(hwndDlg, L"Context", (HANDLE)context);
    }
    else
    {
        context = (PDV_DISK_OPTIONS_CONTEXT)GetProp(hwndDlg, L"Context");

        if (uMsg == WM_DESTROY)
        {
            if (context->OptionsChanged)
                DiskDrivesSaveList();

            FreeListViewDiskDriveEntries(context);

            RemoveProp(hwndDlg, L"Context");
            PhFree(context);
        }
    }

    if (context == NULL)
        return FALSE;

    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            // Center the property sheet.
            PhCenterWindow(GetParent(hwndDlg), GetParent(GetParent(hwndDlg)));
            // Hide the OK button.
            ShowWindow(GetDlgItem(GetParent(hwndDlg), IDOK), SW_HIDE);
            // Set the Cancel button text.
            Button_SetText(GetDlgItem(GetParent(hwndDlg), IDCANCEL), L"Close");

            context->ListViewHandle = GetDlgItem(hwndDlg, IDC_DISKDRIVE_LISTVIEW);
            PhSetListViewStyle(context->ListViewHandle, FALSE, TRUE);
            ListView_SetExtendedListViewStyleEx(context->ListViewHandle, LVS_EX_CHECKBOXES, LVS_EX_CHECKBOXES);
            PhSetControlTheme(context->ListViewHandle, L"explorer");
            PhAddListViewColumn(context->ListViewHandle, 0, 0, 0, LVCFMT_LEFT, 350, L"Disk Drives");
            PhSetExtendedListView(context->ListViewHandle);
           
            if (WindowsVersion >= WINDOWS_VISTA)
            {
                ListView_EnableGroupView(context->ListViewHandle, TRUE);
                AddListViewGroup(context->ListViewHandle, 0, L"Connected");
                AddListViewGroup(context->ListViewHandle, 1, L"Disconnected");
            }

            FindDiskDrives(context);

            context->OptionsChanged = FALSE;

            EnableThemeDialogTexture(hwndDlg, ETDT_ENABLETAB);
        }
        break;
    case WM_NOTIFY:
        {
            LPNMHDR header = (LPNMHDR)lParam;

            if (header->code == LVN_ITEMCHANGED)
            {
                LPNM_LISTVIEW listView = (LPNM_LISTVIEW)lParam;

                if (context->EnumeratingDisks)
                    break;

                if (listView->uChanged & LVIF_STATE)
                {
                    switch (listView->uNewState & LVIS_STATEIMAGEMASK)
                    {
                    case 0x2000: // checked
                        {
                            PDV_DISK_ID param = (PDV_DISK_ID)listView->lParam;

                            if (!FindDiskEntry(param, FALSE))
                            {
                                PDV_DISK_ENTRY entry;

                                entry = CreateDiskEntry(param);
                                entry->UserReference = TRUE;
                            }

                            context->OptionsChanged = TRUE;
                        }
                        break;
                    case 0x1000: // unchecked
                        {
                            PDV_DISK_ID param = (PDV_DISK_ID)listView->lParam;

                            FindDiskEntry(param, TRUE);

                            context->OptionsChanged = TRUE;
                        }
                        break;
                    }
                }
            }
            else if (header->code == NM_RCLICK)
            {
                PDV_DISK_ID param;
                PPH_STRING deviceInstance;

                if (param = PhGetSelectedListViewItemParam(context->ListViewHandle))
                {
                    if (deviceInstance = FindDiskDeviceInstance(param->DevicePath))
                    {
                        ShowDeviceMenu(hwndDlg, deviceInstance);
                        PhDereferenceObject(deviceInstance);
                    }
                }
            }
        }
        break;
    }

    return FALSE;
}