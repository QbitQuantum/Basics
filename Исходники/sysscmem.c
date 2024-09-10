INT_PTR CALLBACK PhSipMemoryDialogProc(
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
            static BOOL (WINAPI *getPhysicallyInstalledSystemMemory)(PULONGLONG) = NULL;

            PPH_LAYOUT_ITEM graphItem;
            PPH_LAYOUT_ITEM panelItem;

            PhSipInitializeMemoryDialog();

            MemoryDialog = hwndDlg;
            PhInitializeLayoutManager(&MemoryLayoutManager, hwndDlg);
            PhAddLayoutItem(&MemoryLayoutManager, GetDlgItem(hwndDlg, IDC_TOTALPHYSICAL), NULL, PH_ANCHOR_LEFT | PH_ANCHOR_TOP | PH_ANCHOR_RIGHT | PH_LAYOUT_FORCE_INVALIDATE);
            graphItem = PhAddLayoutItem(&MemoryLayoutManager, GetDlgItem(hwndDlg, IDC_GRAPH_LAYOUT), NULL, PH_ANCHOR_ALL);
            MemoryGraphMargin = graphItem->Margin;
            panelItem = PhAddLayoutItem(&MemoryLayoutManager, GetDlgItem(hwndDlg, IDC_LAYOUT), NULL, PH_ANCHOR_LEFT | PH_ANCHOR_RIGHT | PH_ANCHOR_BOTTOM);

            SendMessage(GetDlgItem(hwndDlg, IDC_TITLE), WM_SETFONT, (WPARAM)MemorySection->Parameters->LargeFont, FALSE);
            SendMessage(GetDlgItem(hwndDlg, IDC_TOTALPHYSICAL), WM_SETFONT, (WPARAM)MemorySection->Parameters->MediumFont, FALSE);

            if (!getPhysicallyInstalledSystemMemory)
                getPhysicallyInstalledSystemMemory = PhGetModuleProcAddress(L"kernel32.dll", "GetPhysicallyInstalledSystemMemory");

            InstalledMemory = 0;

            if (getPhysicallyInstalledSystemMemory && getPhysicallyInstalledSystemMemory(&InstalledMemory))
            {
                SetDlgItemText(hwndDlg, IDC_TOTALPHYSICAL,
                    PhaConcatStrings2(PhaFormatSize(InstalledMemory * 1024, -1)->Buffer, L" installed")->Buffer);
            }
            else
            {
                SetDlgItemText(hwndDlg, IDC_TOTALPHYSICAL,
                    PhaConcatStrings2(PhaFormatSize(UInt32x32To64(PhSystemBasicInformation.NumberOfPhysicalPages, PAGE_SIZE), -1)->Buffer, L" total")->Buffer);
            }

            MemoryPanel = CreateDialog(
                PhInstanceHandle,
                MAKEINTRESOURCE(IDD_SYSINFO_MEMPANEL),
                hwndDlg,
                PhSipMemoryPanelDialogProc
                );
            ShowWindow(MemoryPanel, SW_SHOW);
            PhAddLayoutItemEx(&MemoryLayoutManager, MemoryPanel, NULL, PH_ANCHOR_LEFT | PH_ANCHOR_RIGHT | PH_ANCHOR_BOTTOM, panelItem->Margin);

            CommitGraphHandle = CreateWindow(
                PH_GRAPH_CLASSNAME,
                NULL,
                WS_VISIBLE | WS_CHILD | WS_BORDER,
                0,
                0,
                3,
                3,
                MemoryDialog,
                (HMENU)IDC_COMMIT,
                PhInstanceHandle,
                NULL
                );
            Graph_SetTooltip(CommitGraphHandle, TRUE);

            PhysicalGraphHandle = CreateWindow(
                PH_GRAPH_CLASSNAME,
                NULL,
                WS_VISIBLE | WS_CHILD | WS_BORDER,
                0,
                0,
                3,
                3,
                MemoryDialog,
                (HMENU)IDC_PHYSICAL,
                PhInstanceHandle,
                NULL
                );
            Graph_SetTooltip(PhysicalGraphHandle, TRUE);

            PhSipUpdateMemoryGraphs();
            PhSipUpdateMemoryPanel();
        }
        break;
    case WM_DESTROY:
        {
            PhDeleteLayoutManager(&MemoryLayoutManager);
        }
        break;
    case WM_SIZE:
        {
            PhLayoutManagerLayout(&MemoryLayoutManager);
            PhSipLayoutMemoryGraphs();
        }
        break;
    case WM_NOTIFY:
        {
            NMHDR *header = (NMHDR *)lParam;

            if (header->hwndFrom == CommitGraphHandle)
            {
                PhSipNotifyCommitGraph(header);
            }
            else if (header->hwndFrom == PhysicalGraphHandle)
            {
                PhSipNotifyPhysicalGraph(header);
            }
        }
        break;
    }

    return FALSE;
}