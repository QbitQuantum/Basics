INT_PTR CALLBACK EtpWsWatchDlgProc(
    _In_ HWND hwndDlg,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    )
{
    PWS_WATCH_CONTEXT context;

    if (uMsg == WM_INITDIALOG)
    {
        context = (PWS_WATCH_CONTEXT)lParam;
        SetProp(hwndDlg, L"Context", (HANDLE)context);
    }
    else
    {
        context = (PWS_WATCH_CONTEXT)GetProp(hwndDlg, L"Context");

        if (uMsg == WM_DESTROY)
            RemoveProp(hwndDlg, L"Context");
    }

    if (!context)
        return FALSE;

    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            HWND lvHandle;

            PhCenterWindow(hwndDlg, GetParent(hwndDlg));

            context->WindowHandle = hwndDlg;
            context->ListViewHandle = lvHandle = GetDlgItem(hwndDlg, IDC_LIST);

            PhSetListViewStyle(lvHandle, FALSE, TRUE);
            PhSetControlTheme(lvHandle, L"explorer");
            PhAddListViewColumn(lvHandle, 0, 0, 0, LVCFMT_LEFT, 340, L"Instruction");
            PhAddListViewColumn(lvHandle, 1, 1, 1, LVCFMT_LEFT, 80, L"Count");
            PhSetExtendedListView(lvHandle);
            ExtendedListView_SetSort(lvHandle, 1, DescendingSortOrder);

            context->Hashtable = PhCreateSimpleHashtable(64);
            context->BufferSize = 0x2000;
            context->Buffer = PhAllocate(context->BufferSize);

            PhInitializeQueuedLock(&context->ResultListLock);
            context->SymbolProvider = PhCreateSymbolProvider(context->ProcessItem->ProcessId);
            PhLoadSymbolProviderOptions(context->SymbolProvider);

            if (!context->SymbolProvider || !context->SymbolProvider->IsRealHandle)
            {
                PhShowError(hwndDlg, L"Unable to open the process.");
                EndDialog(hwndDlg, IDCANCEL);
                break;
            }

            context->ProcessHandle = context->SymbolProvider->ProcessHandle;

            // Load symbols for both process and kernel modules.
            context->LoadingSymbolsForProcessId = context->ProcessItem->ProcessId;
            PhEnumGenericModules(
                NULL,
                context->ProcessHandle,
                0,
                EnumGenericModulesCallback,
                context
                );
            context->LoadingSymbolsForProcessId = SYSTEM_PROCESS_ID;
            PhEnumGenericModules(
                SYSTEM_PROCESS_ID,
                NULL,
                0,
                EnumGenericModulesCallback,
                context
                );

            context->Enabled = EtpUpdateWsWatch(hwndDlg, context);

            if (context->Enabled)
            {
                // WS Watch is already enabled for the process. Enable updating.
                EnableWindow(GetDlgItem(hwndDlg, IDC_ENABLE), FALSE);
                ShowWindow(GetDlgItem(hwndDlg, IDC_WSWATCHENABLED), SW_SHOW);
                SetTimer(hwndDlg, 1, 1000, NULL);
            }
            else
            {
                // WS Watch has not yet been enabled for the process.
            }
        }
        break;
    case WM_DESTROY:
        {
            context->Destroying = TRUE;

            PhDereferenceObject(context->Hashtable);

            if (context->Buffer)
            {
                PhFree(context->Buffer);
                context->Buffer = NULL;
            }
        }
        break;
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDCANCEL:
            case IDOK:
                EndDialog(hwndDlg, IDOK);
                break;
            case IDC_ENABLE:
                {
                    NTSTATUS status;
                    HANDLE processHandle;

                    if (NT_SUCCESS(status = PhOpenProcess(
                        &processHandle,
                        PROCESS_SET_INFORMATION,
                        context->ProcessItem->ProcessId
                        )))
                    {
                        status = NtSetInformationProcess(
                            processHandle,
                            ProcessWorkingSetWatchEx,
                            NULL,
                            0
                            );
                        NtClose(processHandle);
                    }

                    if (NT_SUCCESS(status))
                    {
                        EnableWindow(GetDlgItem(hwndDlg, IDC_ENABLE), FALSE);
                        ShowWindow(GetDlgItem(hwndDlg, IDC_WSWATCHENABLED), SW_SHOW);
                        SetTimer(hwndDlg, 1, 1000, NULL);
                    }
                    else
                    {
                        PhShowStatus(hwndDlg, L"Unable to enable WS watch", status, 0);
                    }
                }
                break;
            }
        }
        break;
    case WM_NOTIFY:
        {
            PhHandleListViewNotifyForCopy(lParam, context->ListViewHandle);
        }
        break;
    case WM_TIMER:
        {
            switch (wParam)
            {
            case 1:
                {
                    EtpUpdateWsWatch(hwndDlg, context);
                }
                break;
            }
        }
        break;
    }

    return FALSE;
}