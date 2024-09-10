INT_PTR CALLBACK BtrfsDeviceResize::DeviceResizeDlgProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    try {
        switch (uMsg) {
            case WM_INITDIALOG:
            {
                win_handle h;
                WCHAR s[255];
                wstring t, u;

                EnableThemeDialogTexture(hwndDlg, ETDT_ENABLETAB);

                GetDlgItemTextW(hwndDlg, IDC_RESIZE_DEVICE_ID, s, sizeof(s) / sizeof(WCHAR));
                wstring_sprintf(t, s, dev_id);
                SetDlgItemTextW(hwndDlg, IDC_RESIZE_DEVICE_ID, t.c_str());

                h = CreateFileW(fn.c_str(), FILE_TRAVERSE | FILE_READ_ATTRIBUTES, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                                OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT, nullptr);

                if (h != INVALID_HANDLE_VALUE) {
                    NTSTATUS Status;
                    IO_STATUS_BLOCK iosb;
                    btrfs_device *devices, *bd;
                    ULONG devsize;
                    bool found = false;
                    HWND slider;

                    devsize = 1024;
                    devices = (btrfs_device*)malloc(devsize);

                    while (true) {
                        Status = NtFsControlFile(h, nullptr, nullptr, nullptr, &iosb, FSCTL_BTRFS_GET_DEVICES, nullptr, 0, devices, devsize);
                        if (Status == STATUS_BUFFER_OVERFLOW) {
                            devsize += 1024;

                            free(devices);
                            devices = (btrfs_device*)malloc(devsize);
                        } else
                            break;
                    }

                    if (!NT_SUCCESS(Status)) {
                        free(devices);
                        return false;
                    }

                    bd = devices;

                    while (true) {
                        if (bd->dev_id == dev_id) {
                            memcpy(&dev_info, bd, sizeof(btrfs_device));
                            found = true;
                            break;
                        }

                        if (bd->next_entry > 0)
                            bd = (btrfs_device*)((uint8_t*)bd + bd->next_entry);
                        else
                            break;
                    }

                    if (!found) {
                        free(devices);
                        return false;
                    }

                    free(devices);

                    GetDlgItemTextW(hwndDlg, IDC_RESIZE_CURSIZE, s, sizeof(s) / sizeof(WCHAR));
                    format_size(dev_info.size, u, true);
                    wstring_sprintf(t, s, u.c_str());
                    SetDlgItemTextW(hwndDlg, IDC_RESIZE_CURSIZE, t.c_str());

                    new_size = dev_info.size;

                    GetDlgItemTextW(hwndDlg, IDC_RESIZE_NEWSIZE, new_size_text, sizeof(new_size_text) / sizeof(WCHAR));
                    wstring_sprintf(t, new_size_text, u.c_str());
                    SetDlgItemTextW(hwndDlg, IDC_RESIZE_NEWSIZE, t.c_str());

                    slider = GetDlgItem(hwndDlg, IDC_RESIZE_SLIDER);
                    SendMessageW(slider, TBM_SETRANGEMIN, false, 0);
                    SendMessageW(slider, TBM_SETRANGEMAX, false, (LPARAM)(dev_info.max_size / 1048576));
                    SendMessageW(slider, TBM_SETPOS, true, (LPARAM)(new_size / 1048576));
                } else
                    return false;

                break;
            }

            case WM_COMMAND:
                switch (HIWORD(wParam)) {
                    case BN_CLICKED:
                        switch (LOWORD(wParam)) {
                            case IDOK:
                                do_resize(hwndDlg);
                                return true;

                            case IDCANCEL:
                                EndDialog(hwndDlg, 0);
                                return true;
                        }
                    break;
                }
            break;

            case WM_HSCROLL:
            {
                wstring t, u;

                new_size = UInt32x32To64(SendMessageW(GetDlgItem(hwndDlg, IDC_RESIZE_SLIDER), TBM_GETPOS, 0, 0), 1048576);

                format_size(new_size, u, true);
                wstring_sprintf(t, new_size_text, u.c_str());
                SetDlgItemTextW(hwndDlg, IDC_RESIZE_NEWSIZE, t.c_str());

                EnableWindow(GetDlgItem(hwndDlg, IDOK), new_size > 0 ? true : false);

                break;
            }
        }
    } catch (const exception& e) {
        error_message(hwndDlg, e.what());
    }

    return false;
}