INT_PTR CALLBACK
ServicesPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    UNREFERENCED_PARAMETER(wParam);

    switch (message)
    {
        case WM_INITDIALOG:
        {
            hServicesPage     = hDlg;
            hServicesListCtrl = GetDlgItem(hServicesPage, IDC_SERVICES_LIST);

            //
            // Correctly display message strings.
            //
            LPCWSTR szOSVendor = (bIsWindows ? IDS_MICROSOFT : IDS_REACTOS);

            size_t itemLength = 0;
            LPWSTR szItem = NULL, szNewItem = NULL;

            itemLength = GetWindowTextLength(GetDlgItem(hServicesPage, IDC_STATIC_SERVICES_WARNING)) + 1;
            szItem     = (LPWSTR)MemAlloc(0, itemLength * sizeof(WCHAR));
            GetDlgItemText(hServicesPage, IDC_STATIC_SERVICES_WARNING, szItem, (int)itemLength);
            szNewItem  = FormatString(szItem, szOSVendor);
            SetDlgItemText(hServicesPage, IDC_STATIC_SERVICES_WARNING, szNewItem);
            MemFree(szNewItem);
            MemFree(szItem);

            itemLength = GetWindowTextLength(GetDlgItem(hServicesPage, IDC_CBX_SERVICES_MASK_PROPRIETARY_SVCS)) + 1;
            szItem     = (LPWSTR)MemAlloc(0, itemLength * sizeof(WCHAR));
            GetDlgItemText(hServicesPage, IDC_CBX_SERVICES_MASK_PROPRIETARY_SVCS, szItem, (int)itemLength);
            szNewItem  = FormatString(szItem, szOSVendor);
            SetDlgItemText(hServicesPage, IDC_CBX_SERVICES_MASK_PROPRIETARY_SVCS, szNewItem);
            MemFree(szNewItem);
            MemFree(szItem);

            //
            // Initialize the styles.
            //
            DWORD dwStyle = ListView_GetExtendedListViewStyle(hServicesListCtrl);
            ListView_SetExtendedListViewStyle(hServicesListCtrl, dwStyle | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
            SetWindowTheme(hServicesListCtrl, L"Explorer", NULL);

            //
            // Initialize the application page's controls.
            //
            LVCOLUMN column = {};

            // First column : Service's name.
            column.mask = LVCF_TEXT | LVCF_WIDTH;
            column.pszText = LoadResourceString(hInst, IDS_SERVICES_COLUMN_SERVICE);
            column.cx = 150;
            ListView_InsertColumn(hServicesListCtrl, 0, &column);
            MemFree(column.pszText);

            // Second column : Whether the service is required or not.
            column.mask = LVCF_TEXT | LVCF_WIDTH;
            column.pszText = LoadResourceString(hInst, IDS_SERVICES_COLUMN_REQ);
            column.cx = 60;
            ListView_InsertColumn(hServicesListCtrl, 1, &column);
            MemFree(column.pszText);

            // Third column : Service's vendor.
            column.mask = LVCF_TEXT | LVCF_WIDTH;
            column.pszText = LoadResourceString(hInst, IDS_SERVICES_COLUMN_VENDOR);
            column.cx = 150;
            ListView_InsertColumn(hServicesListCtrl, 2, &column);
            MemFree(column.pszText);

            // Fourth column : Service's status.
            column.mask = LVCF_TEXT | LVCF_WIDTH;
            column.pszText = LoadResourceString(hInst, IDS_SERVICES_COLUMN_STATUS);
            column.cx = 60;
            ListView_InsertColumn(hServicesListCtrl, 3, &column);
            MemFree(column.pszText);

            // Fifth column : Service's disabled date.
            column.mask = LVCF_TEXT | LVCF_WIDTH;
            column.pszText = LoadResourceString(hInst, IDS_SERVICES_COLUMN_DATEDISABLED);
            column.cx = 120;
            ListView_InsertColumn(hServicesListCtrl, 4, &column);
            MemFree(column.pszText);

            //
            // Populate and sort the list.
            //
            GetServices();
            ListView_Sort(hServicesListCtrl, 0);
            Update_Btn_States(hDlg);

            // Select the first item.
            ListView_SetItemState(hServicesListCtrl, 0, LVIS_SELECTED, LVIS_SELECTED);

            return TRUE;
        }

        case WM_DESTROY:
        {
            ClearServicesList();
            userModificationsList.RemoveAll();
            return 0;
        }

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDC_BTN_SERVICES_ACTIVATE:
                {
                    BOOL bAreThereModifs = FALSE;

                    int index = -1; // From the beginning.
                    while ((index = ListView_GetNextItem(hServicesListCtrl, index, LVNI_ALL)) != -1)
                    {
                        bAreThereModifs = ValidateItem(index, TRUE, FALSE) || bAreThereModifs; // The order is verrrrrry important !!!!
                    }

                    if (bAreThereModifs)
                    {
                        Update_Btn_States(hDlg);
                        PropSheet_Changed(GetParent(hServicesPage), hServicesPage);
                    }

                    return TRUE;
                }

                case IDC_BTN_SERVICES_DEACTIVATE:
                {
                    BOOL bAreThereModifs = FALSE;

                    int index = -1; // From the beginning.
                    while ((index = ListView_GetNextItem(hServicesListCtrl, index, LVNI_ALL)) != -1)
                    {
                        bAreThereModifs = ValidateItem(index, FALSE, FALSE) || bAreThereModifs; // The order is verrrrrry important !!!!
                    }

                    if (bAreThereModifs)
                    {
                        Update_Btn_States(hDlg);
                        PropSheet_Changed(GetParent(hServicesPage), hServicesPage);
                    }

                    return TRUE;
                }

                case IDC_CBX_SERVICES_MASK_PROPRIETARY_SVCS:
                {
                    bMaskProprietarySvcs = !bMaskProprietarySvcs;
                    GetServices(bMaskProprietarySvcs);
                    Update_Btn_States(hDlg);

                    return TRUE;
                }

                default:
                    return FALSE;
            }
            return FALSE;
        }

        case UM_CHECKSTATECHANGE:
        {
            BOOL bNewCheckState = !!((ListView_GetCheckState(hServicesListCtrl, int(lParam)) + 1) % 2);

            if (ValidateItem(/*reinterpret_cast<int>*/ int(lParam), bNewCheckState, !HideEssentialServiceWarning()))
            {
                Update_Btn_States(hDlg);
                PropSheet_Changed(GetParent(hServicesPage), hServicesPage);
            }

            return TRUE;
        }

        case WM_NOTIFY:
        {
            if (reinterpret_cast<LPNMHDR>(lParam)->hwndFrom == hServicesListCtrl)
            {
                switch (reinterpret_cast<LPNMHDR>(lParam)->code)
                {
                    case NM_CLICK:
                    case NM_RCLICK:
                    {
                        DWORD         dwpos = GetMessagePos();
                        LVHITTESTINFO ht    = {};
                        ht.pt.x = GET_X_LPARAM(dwpos);
                        ht.pt.y = GET_Y_LPARAM(dwpos);
                        MapWindowPoints(HWND_DESKTOP /*NULL*/, hServicesListCtrl, &ht.pt, 1);

                        /*
                         * We use ListView_SubItemHitTest(...) and not ListView_HitTest(...)
                         * because ListView_HitTest(...) returns bad flags when one clicks
                         * on a sub-item different from 0. The flags then contain LVHT_ONITEMSTATEICON
                         * which must not be obviously present in this case.
                         */
                        ListView_SubItemHitTest(hServicesListCtrl, &ht);

                        if (LVHT_ONITEMSTATEICON & ht.flags)
                        {
                            PostMessage(hDlg, UM_CHECKSTATECHANGE, 0, (LPARAM)ht.iItem);

                            // Disable default behaviour. Needed for the UM_CHECKSTATECHANGE
                            // custom notification to work as expected.
                            SetWindowLongPtr(hDlg, DWLP_MSGRESULT, TRUE);
                        }

                        return TRUE;
                    }

                    case NM_DBLCLK:
                    case NM_RDBLCLK:
                    {
                        // We deactivate double-clicks.
                        SetWindowLongPtr(hDlg, DWLP_MSGRESULT, TRUE);
                        return TRUE;
                    }

                    case LVN_KEYDOWN:
                    {
                        if (reinterpret_cast<LPNMLVKEYDOWN>(lParam)->wVKey == VK_SPACE)
                        {
                            int iItem = ListView_GetSelectionMark(hServicesListCtrl);
                            PostMessage(hDlg, UM_CHECKSTATECHANGE, 0, (LPARAM)iItem);

                            // Disable default behaviour. Needed for the UM_CHECKSTATECHANGE
                            // custom notification to work as expected.
                            SetWindowLongPtr(hDlg, DWLP_MSGRESULT, TRUE);
                        }

                        return TRUE;
                    }

                    case LVN_COLUMNCLICK:
                    {
                        int iSortingColumn = reinterpret_cast<LPNMLISTVIEW>(lParam)->iSubItem;

                        ListView_SortEx(hServicesListCtrl, iSortingColumn, iSortedColumn);
                        iSortedColumn = iSortingColumn;

                        return TRUE;
                    }
                }
            }
            else
            {
                switch (reinterpret_cast<LPNMHDR>(lParam)->code)
                {
                    case PSN_APPLY:
                    {
                        // Try to apply the modifications to the system.
                        MessageBox(NULL, _T("In Services page: PSN_APPLY"), _T("Info"), MB_ICONINFORMATION);

                        /*
                        //
                        // Move this away...
                        //
                        int iRetVal = MessageBox(NULL, _T("Would you really want to modify the configuration of your system ?"), _T("Warning"), MB_ICONWARNING | MB_YESNOCANCEL);

                        if (iRetVal == IDYES /\* modifications are OK *\/)
                            SetWindowLongPtr(hServicesPage, DWLP_MSGRESULT, PSNRET_NOERROR);
                        else if (iRetVal == IDNO /\* modifications are not OK *\/)
                            SetWindowLongPtr(hServicesPage, DWLP_MSGRESULT, PSNRET_NOERROR);
                        else // if (iRetVal == IDCANCEL) // There was an error...
                            SetWindowLongPtr(hServicesPage, DWLP_MSGRESULT, PSNRET_INVALID);
                        */

                        //
                        // We modify the services which are stored in the user modification list.
                        //

                        // 1- Open the Service Control Manager for modifications.
                        SC_HANDLE hSCManager = OpenSCManagerW(NULL, NULL, SC_MANAGER_ALL_ACCESS);
                        if (hSCManager != NULL)
                        {
                            LPCWSTR svcName;

                            for (POSITION it = userModificationsList.GetHeadPosition(); it; userModificationsList.GetNext(it))
                            {
                                svcName = userModificationsList.GetAt(it);

                                // 2- Retrieve a handle to the service.
                                SC_HANDLE hService = OpenServiceW(hSCManager, svcName, SERVICE_QUERY_CONFIG | SERVICE_CHANGE_CONFIG);
                                if (hService == NULL)
                                {
                                    // TODO : Show a message box.
                                    continue;
                                }

                                DWORD dwBytesNeeded = 0;
                                QueryServiceConfigW(hService, NULL, 0, &dwBytesNeeded);
                                // if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)

                                LPQUERY_SERVICE_CONFIG lpServiceConfig = (LPQUERY_SERVICE_CONFIG)MemAlloc(0, dwBytesNeeded);
                                if (!lpServiceConfig)
                                {
                                    CloseServiceHandle(hService);
                                    continue; // TODO ? Show a message box...
                                }
                                QueryServiceConfigW(hService, lpServiceConfig, dwBytesNeeded, &dwBytesNeeded);

                                if (lpServiceConfig->dwStartType == SERVICE_DISABLED) // We have a disabled service which is becoming to be enabled.
                                {
                                    // 3a- Retrive the properties of the disabled service from the registry.
                                    RegistryDisabledServiceItemParams params = {};

                                    QUERY_REGISTRY_KEYS_TABLE KeysQueryTable[2] = {};
                                    KeysQueryTable[0].QueryRoutine = GetRegistryKeyedDisabledServicesQueryRoutine;
                                    KeysQueryTable[0].EntryContext = &params;
                                    RegQueryRegistryKeys(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Shared Tools\\MSConfig\\services", KeysQueryTable, (PVOID)svcName);

                                    if (bIsWindows && bIsPreVistaOSVersion && !params.bIsPresent)
                                    {
                                        QUERY_REGISTRY_VALUES_TABLE ValuesQueryTable[2] = {};
                                        ValuesQueryTable[0].QueryRoutine = GetRegistryValuedDisabledServicesQueryRoutine;
                                        ValuesQueryTable[0].EntryContext = &params;
                                        RegQueryRegistryValues(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Shared Tools\\MSConfig\\services", ValuesQueryTable, (PVOID)svcName);
                                    }

                                    if (params.bIsPresent)
                                    {
                                        // 4a- Modify the service.
                                        ChangeServiceConfigW(hService, SERVICE_NO_CHANGE, params.dwStartType, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

                                        // 5a- Remove the registry entry of the service.
                                        if (params.bIsKeyed)
                                        {
                                            CAtlStringW serviceRegKey(L"SOFTWARE\\Microsoft\\Shared Tools\\MSConfig\\services\\");
                                            serviceRegKey += svcName;
                                            RegDeleteKeyW(HKEY_LOCAL_MACHINE, serviceRegKey);

                                            /***** HACK for Windows < Vista (e.g. 2000, Xp, 2003...) *****/
                                            //
                                            // Delete also the valued-entry of the service.
                                            //
                                            if (bIsWindows && bIsPreVistaOSVersion)
                                            {
                                                HKEY hSubKey = NULL;
                                                if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Shared Tools\\MSConfig\\services", 0, KEY_SET_VALUE /*KEY_READ*/, &hSubKey) == ERROR_SUCCESS)
                                                {
                                                    RegDeleteValue(hSubKey, svcName);
                                                    RegCloseKey(hSubKey);
                                                }
                                            }
                                            /*************************************************************/
                                        }
                                        else
                                        {
                                            HKEY hSubKey = NULL;
                                            if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Shared Tools\\MSConfig\\services", 0, KEY_SET_VALUE /*KEY_READ*/, &hSubKey) == ERROR_SUCCESS)
                                            {
                                                RegDeleteValue(hSubKey, svcName);
                                                RegCloseKey(hSubKey);
                                            }
                                        }

                                        ////////// HACKHACKHACKHACKHACKHACKHACKHACKHACKHACKHACK ///////////
                                        // userModificationsList.RemoveAt(it);
                                    }
                                    else
                                    {
                                        // Ohoh !! We have a very big problem.
                                        MessageBox(NULL, _T("WTF ??"), _T("FATAL ERROR !!!!"), MB_ICONERROR);
                                    }
                                }
                                else // We have an enabled service which is becoming to be disabled.
                                {
                                    // 3b- Retrieve the local time of disabling.
                                    SYSTEMTIME disableDate = {};
                                    GetLocalTime(&disableDate);

                                    // 4b- Modify the service.
                                    ChangeServiceConfigW(hService, SERVICE_NO_CHANGE, SERVICE_DISABLED, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

                                    // 5b- Register the service into the registry.
                                    CAtlStringW serviceRegKey(L"SOFTWARE\\Microsoft\\Shared Tools\\MSConfig\\services\\");
                                    serviceRegKey += svcName;
                                    HKEY hSubKey = NULL;
                                    if (RegCreateKeyEx(HKEY_LOCAL_MACHINE, serviceRegKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_SET_VALUE, NULL, &hSubKey, NULL) == ERROR_SUCCESS)
                                    {
                                        RegSetDWORDValue(hSubKey, NULL, svcName, FALSE, lpServiceConfig->dwStartType);

                                    #if 1 // DisableDate
                                        RegSetDWORDValue(hSubKey, NULL, L"DAY"   , FALSE, disableDate.wDay   );
                                        RegSetDWORDValue(hSubKey, NULL, L"HOUR"  , FALSE, disableDate.wHour  );
                                        RegSetDWORDValue(hSubKey, NULL, L"MINUTE", FALSE, disableDate.wMinute);
                                        RegSetDWORDValue(hSubKey, NULL, L"MONTH" , FALSE, disableDate.wMonth );
                                        RegSetDWORDValue(hSubKey, NULL, L"SECOND", FALSE, disableDate.wSecond);
                                        RegSetDWORDValue(hSubKey, NULL, L"YEAR"  , FALSE, disableDate.wYear  );
                                    #endif

                                        RegCloseKey(hSubKey);
                                    }

                                    /***** HACK for Windows < Vista (e.g. 2000, Xp, 2003...) *****/
                                    //
                                    // Save also a valued-entry for the service.
                                    //
                                    if (bIsWindows && bIsPreVistaOSVersion)
                                    {
                                        RegSetDWORDValue(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Shared Tools\\MSConfig\\services", svcName, TRUE, lpServiceConfig->dwStartType);
                                    }
                                    /*************************************************************/

                                    ////////// HACKHACKHACKHACKHACKHACKHACKHACKHACKHACKHACK ///////////
                                    // userModificationsList.RemoveAt(it);
                                }

                                MemFree(lpServiceConfig);
                                CloseServiceHandle(hService);
                            }

                            //////////// HACK HACK !!!! ////////////
                            userModificationsList.RemoveAll();
                            ////////////////////////////////////////

                            CloseServiceHandle(hSCManager);


                            //// PropSheet_UnChanged(GetParent(hServicesPage), hServicesPage); ////
                            PropSheet_CancelToClose(GetParent(hDlg));

                            /* Modifications are OK */
                            SetWindowLongPtr(hServicesPage, DWLP_MSGRESULT, PSNRET_NOERROR);
                        }
                        else
                        {
                            MessageBox(hDlg, _T("Impossible to open the SC manager..."), _T("Error"), MB_ICONERROR);

                            // There was an error...
                            SetWindowLongPtr(hServicesPage, DWLP_MSGRESULT, PSNRET_INVALID);
                        }

                        GetServices(bMaskProprietarySvcs);
                        Update_Btn_States(hDlg);

                        return TRUE;
                    }

                    case PSN_HELP:
                    {
                        MessageBox(hServicesPage, _T("Help not implemented yet!"), _T("Help"), MB_ICONINFORMATION | MB_OK);
                        return TRUE;
                    }

                    case PSN_KILLACTIVE: // Is going to lose activation.
                    {
                        // Changes are always valid of course.
                        SetWindowLongPtr(hServicesPage, DWLP_MSGRESULT, FALSE);
                        return TRUE;
                    }

                    case PSN_QUERYCANCEL:
                    {
                        // RefreshStartupList();

                        // Allows cancellation.
                        SetWindowLongPtr(hServicesPage, DWLP_MSGRESULT, FALSE);

                        return TRUE;
                    }

                    case PSN_QUERYINITIALFOCUS:
                    {
                        // Give the focus on and select the first item.
                        ListView_SetItemState(hServicesListCtrl, 0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);

                        SetWindowLongPtr(hServicesPage, DWLP_MSGRESULT, (LONG_PTR)hServicesListCtrl);
                        return TRUE;
                    }

                    //
                    // DO NOT TOUCH THESE NEXT MESSAGES, THEY ARE OK LIKE THIS...
                    //
                    case PSN_RESET: // Perform final cleaning, called before WM_DESTROY.
                        return TRUE;

                    case PSN_SETACTIVE: // Is going to gain activation.
                    {
                        SetWindowLongPtr(hServicesPage, DWLP_MSGRESULT, 0);
                        return TRUE;
                    }

                    default:
                        break;
                }
            }
        }

        default:
            return FALSE;
    }

    return FALSE;
}