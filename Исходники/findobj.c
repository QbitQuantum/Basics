static INT_PTR CALLBACK PhpFindObjectsDlgProc(
    __in HWND hwndDlg,
    __in UINT uMsg,
    __in WPARAM wParam,
    __in LPARAM lParam
    )
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            HWND lvHandle;

            PhCenterWindow(hwndDlg, GetParent(hwndDlg));
            PhFindObjectsListViewHandle = lvHandle = GetDlgItem(hwndDlg, IDC_RESULTS);

            PhInitializeLayoutManager(&WindowLayoutManager, hwndDlg);
            PhAddLayoutItem(&WindowLayoutManager, GetDlgItem(hwndDlg, IDC_FILTER),
                NULL, PH_ANCHOR_LEFT | PH_ANCHOR_TOP | PH_ANCHOR_RIGHT);
            PhAddLayoutItem(&WindowLayoutManager, GetDlgItem(hwndDlg, IDOK),
                NULL, PH_ANCHOR_TOP | PH_ANCHOR_RIGHT);
            PhAddLayoutItem(&WindowLayoutManager, lvHandle,
                NULL, PH_ANCHOR_ALL);

            MinimumSize.left = 0;
            MinimumSize.top = 0;
            MinimumSize.right = 150;
            MinimumSize.bottom = 100;
            MapDialogRect(hwndDlg, &MinimumSize);

            PhRegisterDialog(hwndDlg);

            PhLoadWindowPlacementFromSetting(L"FindObjWindowPosition", L"FindObjWindowSize", hwndDlg);

            PhSetListViewStyle(lvHandle, TRUE, TRUE);
            PhSetControlTheme(lvHandle, L"explorer");
            PhAddListViewColumn(lvHandle, 0, 0, 0, LVCFMT_LEFT, 100, L"Process");
            PhAddListViewColumn(lvHandle, 1, 1, 1, LVCFMT_LEFT, 100, L"Type");
            PhAddListViewColumn(lvHandle, 2, 2, 2, LVCFMT_LEFT, 200, L"Name");
            PhAddListViewColumn(lvHandle, 3, 3, 3, LVCFMT_LEFT, 80, L"Handle");

            PhSetExtendedListView(lvHandle);
            ExtendedListView_SetSortFast(lvHandle, TRUE);
            ExtendedListView_SetCompareFunction(lvHandle, 0, PhpObjectProcessCompareFunction);
            ExtendedListView_SetCompareFunction(lvHandle, 1, PhpObjectTypeCompareFunction);
            ExtendedListView_SetCompareFunction(lvHandle, 2, PhpObjectNameCompareFunction);
            ExtendedListView_SetCompareFunction(lvHandle, 3, PhpObjectHandleCompareFunction);
            PhLoadListViewColumnsFromSetting(L"FindObjListViewColumns", lvHandle);
        }
        break;
    case WM_DESTROY:
        {
            PhSaveWindowPlacementToSetting(L"FindObjWindowPosition", L"FindObjWindowSize", hwndDlg);
            PhSaveListViewColumnsToSetting(L"FindObjListViewColumns", PhFindObjectsListViewHandle);
        }
        break;
    case WM_SHOWWINDOW:
        {
            SetFocus(GetDlgItem(hwndDlg, IDC_FILTER));
            Edit_SetSel(GetDlgItem(hwndDlg, IDC_FILTER), 0, -1);
        }
        break;
    case WM_CLOSE:
        {
            ShowWindow(hwndDlg, SW_HIDE);
            // IMPORTANT
            // Set the result to 0 so the default dialog message
            // handler doesn't invoke IDCANCEL, which will send
            // WM_CLOSE, creating an infinite loop.
            SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, 0);
        }
        return TRUE;
    case WM_SETCURSOR:
        {
            if (SearchThreadHandle)
            {
                SetCursor(LoadCursor(NULL, IDC_WAIT));
                SetWindowLongPtr(hwndDlg, DWLP_MSGRESULT, TRUE);
                return TRUE;
            }
        }
        break;
    case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
            case IDOK:
                {
                    // Don't continue if the user requested cancellation.
                    if (SearchStop)
                        break;

                    if (!SearchThreadHandle)
                    {
                        ULONG i;

                        // Cleanup previous results.

                        ListView_DeleteAllItems(PhFindObjectsListViewHandle);

                        if (SearchResults)
                        {
                            for (i = 0; i < SearchResults->Count; i++)
                            {
                                PPHP_OBJECT_SEARCH_RESULT searchResult = SearchResults->Items[i];

                                PhDereferenceObject(searchResult->TypeName);
                                PhDereferenceObject(searchResult->Name);

                                if (searchResult->ProcessName)
                                    PhDereferenceObject(searchResult->ProcessName);

                                PhFree(searchResult);
                            }

                            PhDereferenceObject(SearchResults);
                        }

                        // Start the search.

                        SearchString = PhGetWindowText(GetDlgItem(hwndDlg, IDC_FILTER));
                        SearchResults = PhCreateList(128);
                        SearchResultsAddIndex = 0;

                        SearchThreadHandle = PhCreateThread(0, PhpFindObjectsThreadStart, NULL);

                        if (!SearchThreadHandle)
                            break;

                        SetDlgItemText(hwndDlg, IDOK, L"Cancel");

                        SetCursor(LoadCursor(NULL, IDC_WAIT));
                    }
                    else
                    {
                        SearchStop = TRUE;
                        EnableWindow(GetDlgItem(hwndDlg, IDOK), FALSE);
                    }
                }
                break;
            case IDCANCEL:
                {
                    SendMessage(hwndDlg, WM_CLOSE, 0, 0);
                }
                break;
            case ID_OBJECT_CLOSE:
                {
                    PPHP_OBJECT_SEARCH_RESULT *results;
                    ULONG numberOfResults;
                    ULONG i;

                    PhGetSelectedListViewItemParams(
                        PhFindObjectsListViewHandle,
                        &results,
                        &numberOfResults
                        );

                    if (numberOfResults != 0 && PhShowConfirmMessage(
                        hwndDlg,
                        L"close",
                        numberOfResults == 1 ? L"the selected handle" : L"the selected handles",
                        L"Closing handles may cause system instability and data corruption.",
                        FALSE
                        ))
                    {
                        for (i = 0; i < numberOfResults; i++)
                        {
                            NTSTATUS status;
                            HANDLE processHandle;

                            if (results[i]->ResultType != HandleSearchResult)
                                continue;

                            if (NT_SUCCESS(status = PhOpenProcess(
                                &processHandle,
                                PROCESS_DUP_HANDLE,
                                results[i]->ProcessId
                                )))
                            {
                                if (NT_SUCCESS(status = PhDuplicateObject(
                                    processHandle,
                                    results[i]->Handle,
                                    NULL,
                                    NULL,
                                    0,
                                    0,
                                    DUPLICATE_CLOSE_SOURCE
                                    )))
                                {
                                    PhRemoveListViewItem(PhFindObjectsListViewHandle,
                                        PhFindListViewItemByParam(PhFindObjectsListViewHandle, 0, results[i]));
                                }

                                NtClose(processHandle);
                            }

                            if (!NT_SUCCESS(status))
                            {
                                if (!PhShowContinueStatus(hwndDlg,
                                    PhaFormatString(L"Unable to close \"%s\"", results[i]->Name->Buffer)->Buffer,
                                    status,
                                    0
                                    ))
                                    break;
                            }
                        }
                    }

                    PhFree(results);
                }
                break;
            case ID_OBJECT_PROCESSPROPERTIES:
                {
                    PPHP_OBJECT_SEARCH_RESULT result =
                        PhGetSelectedListViewItemParam(PhFindObjectsListViewHandle);

                    if (result)
                    {
                        PPH_PROCESS_ITEM processItem;

                        if (processItem = PhReferenceProcessItem(result->ProcessId))
                        {
                            ProcessHacker_ShowProcessProperties(PhMainWndHandle, processItem);
                            PhDereferenceObject(processItem);
                        }
                    }
                }
                break;
            case ID_OBJECT_PROPERTIES:
                {
                    PPHP_OBJECT_SEARCH_RESULT result =
                        PhGetSelectedListViewItemParam(PhFindObjectsListViewHandle);

                    if (result)
                    {
                        if (result->ResultType == HandleSearchResult)
                        {
                            PPH_HANDLE_ITEM handleItem;

                            handleItem = PhCreateHandleItem(&result->Info);

                            handleItem->BestObjectName = handleItem->ObjectName = result->Name;
                            PhReferenceObjectEx(result->Name, 2);

                            handleItem->TypeName = result->TypeName;
                            PhReferenceObject(result->TypeName);

                            PhShowHandleProperties(
                                hwndDlg,
                                result->ProcessId,
                                handleItem
                                );
                            PhDereferenceObject(handleItem);
                        }
                        else
                        {
                            // DLL or Mapped File. Just show file properties.
                            PhShellProperties(hwndDlg, result->Name->Buffer);
                        }
                    }
                }
                break;
            case ID_OBJECT_COPY:
                {
                    PhCopyListView(PhFindObjectsListViewHandle);
                }
                break;
            }
        }
        break;
    case WM_NOTIFY:
        {
            LPNMHDR header = (LPNMHDR)lParam;

            switch (header->code)
            {
            case NM_DBLCLK:
                {
                    if (header->hwndFrom == PhFindObjectsListViewHandle)
                    {
                        SendMessage(hwndDlg, WM_COMMAND, ID_OBJECT_PROPERTIES, 0);
                    }
                }
                break;
            case LVN_KEYDOWN:
                {
                    if (header->hwndFrom == PhFindObjectsListViewHandle)
                    {
                        LPNMLVKEYDOWN keyDown = (LPNMLVKEYDOWN)header;

                        switch (keyDown->wVKey)
                        {
                        case 'C':
                            if (GetKeyState(VK_CONTROL) < 0)
                                SendMessage(hwndDlg, WM_COMMAND, ID_OBJECT_COPY, 0);
                            break;
                        case VK_DELETE:
                            SendMessage(hwndDlg, WM_COMMAND, ID_OBJECT_CLOSE, 0);
                            break;
                        }
                    }
                }
                break;
            }
        }
        break;
    case WM_CONTEXTMENU:
        {
            if ((HWND)wParam == PhFindObjectsListViewHandle)
            {
                POINT point;
                PPHP_OBJECT_SEARCH_RESULT *results;
                ULONG numberOfResults;

                point.x = (SHORT)LOWORD(lParam);
                point.y = (SHORT)HIWORD(lParam);

                if (point.x == -1 && point.y == -1)
                    PhGetListViewContextMenuPoint((HWND)wParam, &point);

                PhGetSelectedListViewItemParams(PhFindObjectsListViewHandle, &results, &numberOfResults);

                if (numberOfResults != 0)
                {
                    HMENU menu;
                    HMENU subMenu;

                    menu = LoadMenu(PhInstanceHandle, MAKEINTRESOURCE(IDR_FINDOBJ));
                    subMenu = GetSubMenu(menu, 0);

                    SetMenuDefaultItem(subMenu, ID_OBJECT_PROPERTIES, FALSE);
                    PhpInitializeFindObjMenu(
                        subMenu,
                        results,
                        numberOfResults
                        );

                    PhShowContextMenu(
                        hwndDlg,
                        PhFindObjectsListViewHandle,
                        subMenu,
                        point
                        );
                    DestroyMenu(menu);
                }

                PhFree(results);
            }
        }
        break;
    case WM_SIZE:
        {
            PhLayoutManagerLayout(&WindowLayoutManager);
        }
        break;
    case WM_SIZING:
        {
            PhResizingMinimumSize((PRECT)lParam, wParam, MinimumSize.right, MinimumSize.bottom);
        }
        break;
    case WM_PH_SEARCH_UPDATE:
        {
            HWND lvHandle;
            ULONG i;

            lvHandle = GetDlgItem(hwndDlg, IDC_RESULTS);

            ExtendedListView_SetRedraw(lvHandle, FALSE);

            PhAcquireQueuedLockExclusive(&SearchResultsLock);

            for (i = SearchResultsAddIndex; i < SearchResults->Count; i++)
            {
                PPHP_OBJECT_SEARCH_RESULT searchResult = SearchResults->Items[i];
                CLIENT_ID clientId;
                PPH_PROCESS_ITEM processItem;
                PPH_STRING clientIdName;
                INT lvItemIndex;

                clientId.UniqueProcess = searchResult->ProcessId;
                clientId.UniqueThread = NULL;

                processItem = PhReferenceProcessItem(clientId.UniqueProcess);
                clientIdName = PhGetClientIdNameEx(&clientId, processItem ? processItem->ProcessName : NULL);

                lvItemIndex = PhAddListViewItem(
                    lvHandle,
                    MAXINT,
                    clientIdName->Buffer,
                    searchResult
                    );

                PhDereferenceObject(clientIdName);

                if (processItem)
                {
                    searchResult->ProcessName = processItem->ProcessName;
                    PhReferenceObject(searchResult->ProcessName);
                    PhDereferenceObject(processItem);
                }
                else
                {
                    searchResult->ProcessName = NULL;
                }

                PhSetListViewSubItem(lvHandle, lvItemIndex, 1, searchResult->TypeName->Buffer);
                PhSetListViewSubItem(lvHandle, lvItemIndex, 2, searchResult->Name->Buffer);
                PhSetListViewSubItem(lvHandle, lvItemIndex, 3, searchResult->HandleString);
            }

            SearchResultsAddIndex = i;

            PhReleaseQueuedLockExclusive(&SearchResultsLock);

            ExtendedListView_SetRedraw(lvHandle, TRUE);
        }
        break;
    case WM_PH_SEARCH_FINISHED:
        {
            // Add any un-added items.
            SendMessage(hwndDlg, WM_PH_SEARCH_UPDATE, 0, 0);

            PhDereferenceObject(SearchString);

            NtWaitForSingleObject(SearchThreadHandle, FALSE, NULL);
            NtClose(SearchThreadHandle);
            SearchThreadHandle = NULL;
            SearchStop = FALSE;

            ExtendedListView_SortItems(GetDlgItem(hwndDlg, IDC_RESULTS));

            SetDlgItemText(hwndDlg, IDOK, L"Find");
            EnableWindow(GetDlgItem(hwndDlg, IDOK), TRUE);

            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }
        break;
    }

    return FALSE;
}