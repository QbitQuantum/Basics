static VOID
InitProbeListPage(HWND hwndDlg)
{
    LV_COLUMN Column;
    LV_ITEM Item;
    WCHAR szBuffer[MAX_STR_SIZE], szGuid[MAX_STR_SIZE],
          szTrimGuid[MAX_STR_SIZE], szStatusText[MAX_STR_SIZE];
    HWND hList = GetDlgItem(hwndDlg, IDC_PROBELIST);
    PWSTR pstrStatusText;
    HDEVINFO hDevInfo;
    SP_DEVINFO_DATA DevInfoData;
    ULONG ulStatus, ulProblemNumber;
    GUID ClassGuid;
    RECT Rect;
    DWORD Index;

    if (!hList) return;

    ZeroMemory(&Column, sizeof(LV_COLUMN));

    GetClientRect(hList, &Rect);

    Column.mask         = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
    Column.fmt          = LVCFMT_LEFT;
    Column.iSubItem     = 0;
    Column.pszText      = NULL;
    Column.cx           = Rect.right - GetSystemMetrics(SM_CXVSCROLL);
    (VOID) ListView_InsertColumn(hList, 0, &Column);

    ZeroMemory(&Item, sizeof(LV_ITEM));

    LoadString(hApplet, IDS_ADDNEWDEVICE, szBuffer, sizeof(szBuffer) / sizeof(WCHAR));

    Item.mask       = LVIF_TEXT | LVIF_PARAM | LVIF_STATE | LVIF_IMAGE;
    Item.pszText    = (LPWSTR) szBuffer;
    Item.iItem      = (INT) ListView_GetItemCount(hList);
    Item.iImage     = -1;
    (VOID) ListView_InsertItem(hList, &Item);

    hDevInfo = SetupDiGetClassDevsEx(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT, NULL, NULL, 0);

    if (hDevInfo == INVALID_HANDLE_VALUE) return;

    /* Get the device image List */
    ImageListData.cbSize = sizeof(ImageListData);
    SetupDiGetClassImageList(&ImageListData);

    DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    for (Index = 0; TRUE; Index++)
    {
        szBuffer[0] = L'\0';

        if (!SetupDiEnumDeviceInfo(hDevInfo, Index, &DevInfoData)) break;

        if (CM_Get_DevNode_Status_Ex(&ulStatus, &ulProblemNumber, DevInfoData.DevInst, 0, NULL) == CR_SUCCESS)
        {
            if (ulStatus & DN_NO_SHOW_IN_DM) continue;
        }

        /* Get the device's friendly name */
        if (!SetupDiGetDeviceRegistryProperty(hDevInfo,
                                              &DevInfoData,
                                              SPDRP_FRIENDLYNAME,
                                              0,
                                              (BYTE*)szBuffer,
                                              MAX_STR_SIZE,
                                              NULL))
        {
            /* If the friendly name fails, try the description instead */
            SetupDiGetDeviceRegistryProperty(hDevInfo,
                                             &DevInfoData,
                                             SPDRP_DEVICEDESC,
                                             0,
                                             (BYTE*)szBuffer,
                                             MAX_STR_SIZE,
                                             NULL);
        }

        SetupDiGetDeviceRegistryProperty(hDevInfo,
                                         &DevInfoData,
                                         SPDRP_CLASSGUID,
                                         0,
                                         (BYTE*)szGuid,
                                         MAX_STR_SIZE,
                                         NULL);

        TrimGuidString(szGuid, szTrimGuid);
        UuidFromStringW(szTrimGuid, &ClassGuid);

        SetupDiGetClassImageIndex(&ImageListData,
                                  &ClassGuid,
                                  &Item.iImage);

        DeviceProblemTextW(NULL,
                           DevInfoData.DevInst,
                           ulProblemNumber,
                           szStatusText,
                           sizeof(szStatusText) / sizeof(WCHAR));

        pstrStatusText = (PWSTR)HeapAlloc(hProcessHeap, 0, sizeof(szStatusText));
        lstrcpy(pstrStatusText, szStatusText);

        if (szBuffer[0] != L'\0')
        {
            /* Set device name */
            Item.pszText = (LPWSTR) szBuffer;
            Item.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE | LVIF_IMAGE;
            Item.lParam = (LPARAM) pstrStatusText;
            Item.iItem = (INT) ListView_GetItemCount(hList);
            (VOID) ListView_InsertItem(hList, &Item);
        }

        DevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
    }

    (VOID) ListView_SetImageList(hList, ImageListData.ImageList, LVSIL_SMALL);
    (VOID) ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT);
    SetupDiDestroyDeviceInfoList(hDevInfo);
}