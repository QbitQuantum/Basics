INT_PTR CALLBACK PvpPeResourcesDlgProc(
    _In_ HWND hwndDlg,
    _In_ UINT uMsg,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
    )
{
    LPPROPSHEETPAGE propSheetPage;
    PPV_PROPPAGECONTEXT propPageContext;

    if (!PvPropPageDlgProcHeader(hwndDlg, uMsg, lParam, &propSheetPage, &propPageContext))
        return FALSE;

    switch (uMsg)
    {
    case WM_INITDIALOG:
        {
            HWND lvHandle;
            PH_MAPPED_IMAGE_RESOURCES resources;
            PH_IMAGE_RESOURCE_ENTRY entry;
            ULONG count = 0;
            ULONG i;
            INT lvItemIndex;

            lvHandle = GetDlgItem(hwndDlg, IDC_LIST);
            PhSetListViewStyle(lvHandle, TRUE, TRUE);
            PhSetControlTheme(lvHandle, L"explorer");
            PhAddListViewColumn(lvHandle, 0, 0, 0, LVCFMT_LEFT, 40, L"#");
            PhAddListViewColumn(lvHandle, 1, 1, 1, LVCFMT_LEFT, 150, L"Type");
            PhAddListViewColumn(lvHandle, 2, 2, 2, LVCFMT_LEFT, 80, L"Name");
            PhAddListViewColumn(lvHandle, 3, 3, 3, LVCFMT_LEFT, 100, L"Size");
            PhAddListViewColumn(lvHandle, 4, 4, 4, LVCFMT_LEFT, 100, L"Language");
            PhSetExtendedListView(lvHandle);
            PhLoadListViewColumnsFromSetting(L"ImageResourcesListViewColumns", lvHandle);

            if (NT_SUCCESS(PhGetMappedImageResources(&resources, &PvMappedImage)))
            {
                for (i = 0; i < resources.NumberOfEntries; i++)
                {
                    PVOID string;
                    WCHAR number[PH_INT32_STR_LEN_1];

                    entry = resources.ResourceEntries[i];

                    PhPrintUInt64(number, ++count);
                    lvItemIndex = PhAddListViewItem(lvHandle, MAXINT, number, NULL);

                    if (IS_INTRESOURCE(entry.Type))
                    {
                        PhSetListViewSubItem(lvHandle, lvItemIndex, PVE_RESOURCES_COLUMN_INDEX_TYPE, PvpGetResourceTypeString(entry.Type));
                    }
                    else
                    {
                        PIMAGE_RESOURCE_DIR_STRING_U resourceString = (PIMAGE_RESOURCE_DIR_STRING_U)entry.Type;

                        string = PhAllocateCopy(resourceString->NameString, resourceString->Length * sizeof(WCHAR));

                        PhSetListViewSubItem(lvHandle, lvItemIndex, PVE_RESOURCES_COLUMN_INDEX_TYPE, string);
                        PhFree(string);
                    }

                    if (IS_INTRESOURCE(entry.Name))
                    {
                        PhPrintUInt32(number, (ULONG)entry.Name);
                        PhSetListViewSubItem(lvHandle, lvItemIndex, PVE_RESOURCES_COLUMN_INDEX_NAME, number);
                    }
                    else
                    {
                        PIMAGE_RESOURCE_DIR_STRING_U resourceString = (PIMAGE_RESOURCE_DIR_STRING_U)entry.Name;

                        string = PhAllocateCopy(resourceString->NameString, resourceString->Length * sizeof(WCHAR));

                        PhSetListViewSubItem(lvHandle, lvItemIndex, PVE_RESOURCES_COLUMN_INDEX_NAME, string);
                        PhFree(string);
                    }

                    if (IS_INTRESOURCE(entry.Language))
                    {
                        WCHAR name[LOCALE_NAME_MAX_LENGTH];

                        PhPrintUInt32(number, (ULONG)entry.Language);

                        if (LCIDToLocaleName((ULONG)entry.Language, name, LOCALE_NAME_MAX_LENGTH, LOCALE_ALLOW_NEUTRAL_NAMES))
                            PhSetListViewSubItem(lvHandle, lvItemIndex, PVE_RESOURCES_COLUMN_INDEX_LCID, PhaFormatString(L"%s (%s)", number, name)->Buffer);
                        else
                            PhSetListViewSubItem(lvHandle, lvItemIndex, PVE_RESOURCES_COLUMN_INDEX_LCID, number);
                    }
                    else
                    {
                        PIMAGE_RESOURCE_DIR_STRING_U resourceString = (PIMAGE_RESOURCE_DIR_STRING_U)entry.Language;

                        string = PhAllocateCopy(resourceString->NameString, resourceString->Length * sizeof(WCHAR));

                        PhSetListViewSubItem(lvHandle, lvItemIndex, PVE_RESOURCES_COLUMN_INDEX_LCID, string);
                        PhFree(string);
                    }

                    PhSetListViewSubItem(lvHandle, lvItemIndex, PVE_RESOURCES_COLUMN_INDEX_SIZE, PhaFormatSize(entry.Size, -1)->Buffer);
                }

                PhFree(resources.ResourceEntries);
            }

            ExtendedListView_SortItems(lvHandle);
            
            EnableThemeDialogTexture(hwndDlg, ETDT_ENABLETAB);
        }
        break;
    case WM_DESTROY:
        {
            PhSaveListViewColumnsToSetting(L"ImageResourcesListViewColumns", GetDlgItem(hwndDlg, IDC_LIST));
        }
        break;
    case WM_SHOWWINDOW:
        {
            if (!propPageContext->LayoutInitialized)
            {
                PPH_LAYOUT_ITEM dialogItem;

                dialogItem = PvAddPropPageLayoutItem(hwndDlg, hwndDlg,
                    PH_PROP_PAGE_TAB_CONTROL_PARENT, PH_ANCHOR_ALL);
                PvAddPropPageLayoutItem(hwndDlg, GetDlgItem(hwndDlg, IDC_LIST),
                    dialogItem, PH_ANCHOR_ALL);

                PvDoPropPageLayout(hwndDlg);

                propPageContext->LayoutInitialized = TRUE;
            }
        }
        break;
    case WM_NOTIFY:
        {
            PvHandleListViewNotifyForCopy(lParam, GetDlgItem(hwndDlg, IDC_LIST));
        }
        break;
    }

    return FALSE;
}