INT_PTR CALLBACK
ToolsPageWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
        {
            hToolsPage     = hDlg;
            hToolsListCtrl = GetDlgItem(hToolsPage, IDC_TOOLS_LIST);

            //
            // Initialize the styles.
            //
            DWORD dwStyle = ListView_GetExtendedListViewStyle(hToolsListCtrl);
            ListView_SetExtendedListViewStyle(hToolsListCtrl, dwStyle | LVS_EX_FULLROWSELECT);
            SetWindowTheme(hToolsListCtrl, L"Explorer", NULL);

            //
            // Initialize the application page's controls.
            //
            LVCOLUMN column = {};

            // First column : Tool's name.
            column.mask = LVCF_TEXT | LVCF_WIDTH;
            column.pszText = LoadResourceString(hInst, IDS_TOOLS_COLUMN_NAME);
            column.cx = 150;
            ListView_InsertColumn(hToolsListCtrl, 0, &column);
            MemFree(column.pszText);

            // Second column : Whether the tool is a standard one or not.
            column.mask = LVCF_TEXT | LVCF_WIDTH;
            column.pszText = LoadResourceString(hInst, IDS_TOOLS_COLUMN_STANDARD);
            column.cx = 60;
            ListView_InsertColumn(hToolsListCtrl, 1, &column);
            MemFree(column.pszText);

            // Third column : Description.
            column.mask = LVCF_TEXT | LVCF_WIDTH;
            column.pszText = LoadResourceString(hInst, IDS_TOOLS_COLUMN_DESCR);
            column.cx = 500;
            ListView_InsertColumn(hToolsListCtrl, 2, &column);
            MemFree(column.pszText);

            //
            // Populate and sort the list.
            //
            FillListView();
            ListView_Sort(hToolsListCtrl, 0);

            // Force an update in case of an empty list (giving focus on it when empty won't emit a LVN_ITEMCHANGED message).
            Update_States(-1 /* Wrong index to initialize all the controls with their default state (i.e. disabled) */);

            PropSheet_UnChanged(GetParent(hToolsPage), hToolsPage);

            return TRUE;
        }

        case WM_DESTROY:
        {
            LVITEM lvitem = {};
            lvitem.mask  = LVIF_PARAM;
            lvitem.iItem = -1; // From the beginning.

            while ((lvitem.iItem = ListView_GetNextItem(hToolsListCtrl, lvitem.iItem, LVNI_ALL)) != -1)
            {
                // ListView_Update();   // Updates a list-view item.
                // ListView_FindItem(); // peut être intéressant pour faire de la recherche itérative à partir du nom (ou partie du...) de l'item.

                ListView_GetItem(hToolsListCtrl, &lvitem);

                delete reinterpret_cast<TOOL*>(lvitem.lParam);
                lvitem.lParam = NULL;
            }
            ListView_DeleteAllItems(hToolsListCtrl);

            return 0;
        }

        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case IDC_BTN_RUN:
                {
                    RunSelectedTool();
                    return TRUE;
                }

                case IDC_CBX_TOOLS_ADVOPT:
                {
                    Update_States(ListView_GetSelectionMark(hToolsListCtrl));
                    return TRUE;
                }

                default:
                    return FALSE;
            }
            return FALSE;
        }

        case WM_NOTIFY:
        {
            if (((LPNMHDR)lParam)->hwndFrom == hToolsListCtrl)
            {
                switch (((LPNMHDR)lParam)->code)
                {
                    case LVN_ITEMCHANGED:
                    {
                        if ( (((LPNMLISTVIEW)lParam)->uChanged  & LVIF_STATE) && /* The state has changed */
                             (((LPNMLISTVIEW)lParam)->uNewState & LVIS_SELECTED) /* The item has been (de)selected */ )
                        {
                            Update_States(((LPNMLISTVIEW)lParam)->iItem);
                        }

                        return TRUE;
                    }

                    case NM_DBLCLK:
                    case NM_RDBLCLK:
                    {
                        RunSelectedTool();
                        return TRUE;
                    }

                    case LVN_COLUMNCLICK:
                    {
                        int iSortingColumn = ((LPNMLISTVIEW)lParam)->iSubItem;

                        ListView_SortEx(hToolsListCtrl, iSortingColumn, iToolsPageSortedColumn);
                        iToolsPageSortedColumn = iSortingColumn;

                        return TRUE;
                    }

                    default:
                        break;
                }
            }
            else
            {
                switch (((LPNMHDR)lParam)->code)
                {
                    case PSN_APPLY:
                    {
                        // Since there are nothing to modify, applying modifications
                        // cannot return any error.
                        SetWindowLongPtr(hToolsPage, DWLP_MSGRESULT, PSNRET_NOERROR);
                        PropSheet_UnChanged(GetParent(hToolsPage), hToolsPage);
                        return TRUE;
                    }

                    case PSN_HELP:
                    {
                        MessageBoxW(hToolsPage, L"Help not implemented yet!", L"Help", MB_ICONINFORMATION | MB_OK);
                        return TRUE;
                    }

                    case PSN_KILLACTIVE: // Is going to lose activation.
                    {
                        // Changes are always valid of course.
                        SetWindowLongPtr(hToolsPage, DWLP_MSGRESULT, FALSE);
                        return TRUE;
                    }

                    case PSN_QUERYCANCEL:
                    {
                        // Allows cancellation since there are nothing to cancel...
                        SetWindowLongPtr(hToolsPage, DWLP_MSGRESULT, FALSE);
                        return TRUE;
                    }

                    case PSN_QUERYINITIALFOCUS:
                    {
                        // Give the focus on and select the first item.
                        ListView_SetItemState(hToolsListCtrl, 0, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);

                        SetWindowLongPtr(hToolsPage, DWLP_MSGRESULT, (LONG_PTR)hToolsListCtrl);
                        return TRUE;
                    }

                    //
                    // DO NOT TOUCH THESE NEXT MESSAGES, THEY ARE OK LIKE THIS...
                    //
                    case PSN_RESET: // Perform final cleaning, called before WM_DESTROY.
                        return TRUE;

                    case PSN_SETACTIVE: // Is going to gain activation.
                    {
                        SetWindowLongPtr(hToolsPage, DWLP_MSGRESULT, 0);
                        return TRUE;
                    }

                    default:
                        break;
                }
            }

            return FALSE;
        }

        default:
            return FALSE;
    }

    // return FALSE;
}