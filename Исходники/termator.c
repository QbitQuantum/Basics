static INT_PTR CALLBACK PhpProcessTerminatorDlgProc(
    _In_ HWND hwndDlg,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    )
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            PPH_PROCESS_ITEM processItem = (PPH_PROCESS_ITEM)lParam;
            PPH_STRING title;
            HWND lvHandle;
            HIMAGELIST imageList;
            ULONG i;

            PhCenterWindow(hwndDlg, GetParent(hwndDlg));

            title = PhFormatString(
                L"Terminator - %s (%u)",
                processItem->ProcessName->Buffer,
                (ULONG)processItem->ProcessId
                );
            SetWindowText(hwndDlg, title->Buffer);
            PhDereferenceObject(title);

            SetProp(hwndDlg, L"ProcessItem", (HANDLE)processItem);

            lvHandle = GetDlgItem(hwndDlg, IDC_TERMINATOR_LIST);
            PhAddListViewColumn(lvHandle, 0, 0, 0, LVCFMT_LEFT, 70, L"ID");
            PhAddListViewColumn(lvHandle, 1, 1, 1, LVCFMT_LEFT, 280, L"Description");
            ListView_SetExtendedListViewStyleEx(lvHandle, LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_INFOTIP | LVS_EX_LABELTIP | LVS_EX_CHECKBOXES, -1);
            PhSetControlTheme(lvHandle, L"explorer");

            imageList = ImageList_Create(16, 16, ILC_COLOR32, 0, 0);
            ImageList_SetImageCount(imageList, 2);
            PhSetImageListBitmap(imageList, CROSS_INDEX, PhInstanceHandle, MAKEINTRESOURCE(IDB_CROSS));
            PhSetImageListBitmap(imageList, TICK_INDEX, PhInstanceHandle, MAKEINTRESOURCE(IDB_TICK));

            for (i = 0; i < sizeof(PhTerminatorTests) / sizeof(TEST_ITEM); i++)
            {
                INT itemIndex;
                BOOLEAN check;

                itemIndex = PhAddListViewItem(
                    lvHandle,
                    MAXINT,
                    PhTerminatorTests[i].Id,
                    &PhTerminatorTests[i]
                    );
                PhSetListViewSubItem(lvHandle, itemIndex, 1, PhTerminatorTests[i].Description);
                PhSetListViewItemImageIndex(lvHandle, itemIndex, -1);

                check = TRUE;

                if (WSTR_EQUAL(PhTerminatorTests[i].Id, L"TT4") || WSTR_EQUAL(PhTerminatorTests[i].Id, L"M1"))
                    check = FALSE;

                ListView_SetCheckState(lvHandle, itemIndex, check);
            }

            ListView_SetImageList(lvHandle, imageList, LVSIL_SMALL);

            SetDlgItemText(
                hwndDlg,
                IDC_TERMINATOR_TEXT,
                L"Double-click a termination method or click Run Selected."
                );
        }
        break;
    case WM_DESTROY:
        {
            RemoveProp(hwndDlg, L"ProcessItem");
        }
        break;
    case WM_COMMAND:
        {
            INT id = LOWORD(wParam);

            switch (id)
            {
            case IDCANCEL: // Esc and X button to close
            case IDOK:
                EndDialog(hwndDlg, IDOK);
                break;
            case IDC_RUNSELECTED:
                {
                    if (PhShowConfirmMessage(hwndDlg, L"run", L"the selected terminator tests", NULL, FALSE))
                    {
                        HWND lvHandle;
                        ULONG i;

                        lvHandle = GetDlgItem(hwndDlg, IDC_TERMINATOR_LIST);

                        for (i = 0; i < sizeof(PhTerminatorTests) / sizeof(TEST_ITEM); i++)
                        {
                            if (ListView_GetCheckState(lvHandle, i))
                            {
                                if (PhpRunTerminatorTest(
                                    hwndDlg,
                                    i
                                    ))
                                    break;
                            }
                        }
                    }
                }
                break;
            }
        }
        break;
    case WM_NOTIFY:
        {
            LPNMHDR header = (LPNMHDR)lParam;

            if (header->hwndFrom == GetDlgItem(hwndDlg, IDC_TERMINATOR_LIST))
            {
                if (header->code == NM_DBLCLK)
                {
                    LPNMITEMACTIVATE itemActivate = (LPNMITEMACTIVATE)header;

                    if (itemActivate->iItem != -1)
                    {
                        if (PhShowConfirmMessage(hwndDlg, L"run", L"the selected test", NULL, FALSE))
                        {
                            PhpRunTerminatorTest(
                                hwndDlg,
                                itemActivate->iItem
                                );
                        }
                    }
                }
                else if (header->code == LVN_ITEMCHANGED)
                {
                    ULONG i;
                    BOOLEAN oneSelected;

                    oneSelected = FALSE;

                    for (i = 0; i < sizeof(PhTerminatorTests) / sizeof(TEST_ITEM); i++)
                    {
                        if (ListView_GetCheckState(header->hwndFrom, i))
                        {
                            oneSelected = TRUE;
                            break;
                        }
                    }

                    EnableWindow(GetDlgItem(hwndDlg, IDC_RUNSELECTED), oneSelected);
                }
            }
        }
        break;
    }

    return FALSE;
}