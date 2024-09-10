static INT
LoadFreeldrSettings(HINF hInf, HWND hwndDlg)
{
    INFCONTEXT InfContext;
    PBOOTRECORD pRecord;
    WCHAR szDefaultOs[MAX_PATH];
    WCHAR szName[MAX_PATH];
    WCHAR szValue[MAX_PATH];
    DWORD LineLength;
    DWORD TimeOut;
    LRESULT lResult;

    if (!SetupFindFirstLineW(hInf,
                             L"FREELOADER",
                             L"DefaultOS",
                             &InfContext))
    {
        /* Failed to find default os */
        return FALSE;
    }

    if (!SetupGetStringFieldW(&InfContext,
                              1,
                              szDefaultOs,
                              sizeof(szDefaultOs) / sizeof(WCHAR),
                              &LineLength))
    {
        /* No key */
        return FALSE;
    }

    if (!SetupFindFirstLineW(hInf,
                             L"FREELOADER",
                             L"TimeOut",
                             &InfContext))
    {
        /* Expected to find timeout value */
        return FALSE;
    }


    if (!SetupGetIntField(&InfContext,
                          1,
                          (PINT)&TimeOut))
    {
        /* Failed to retrieve timeout */
        return FALSE;
    }

    if (!SetupFindFirstLineW(hInf,
                             L"Operating Systems",
                             NULL,
                             &InfContext))
    {
        /* Expected list of operating systems */
        return FALSE;
    }

    do
    {
        if (!SetupGetStringFieldW(&InfContext,
                                  0,
                                  szName,
                                  sizeof(szName) / sizeof(WCHAR),
                                  &LineLength))
        {
            /* The ini file is messed up */
            return FALSE;
        }

        if (!SetupGetStringFieldW(&InfContext,
                                  1,
                                  szValue,
                                  sizeof(szValue) / sizeof(WCHAR),
                                  &LineLength))
        {
            /* The ini file is messed up */
            return FALSE;
        }

        pRecord = ReadFreeldrSection(hInf, szName);
        if (pRecord)
        {
            lResult = SendDlgItemMessageW(hwndDlg, IDC_STRECOSCOMBO, CB_ADDSTRING, (WPARAM)0, (LPARAM)szValue);
            if (lResult != CB_ERR)
            {
                SendDlgItemMessageW(hwndDlg, IDC_STRECOSCOMBO, CB_SETITEMDATA, (WPARAM)lResult, (LPARAM)pRecord);
                if (!wcscmp(szDefaultOs, szName))
                {
                    /* We store the friendly name as key */
                    wcscpy(szDefaultOs, szValue);
                }
            }
            else
            {
                HeapFree(GetProcessHeap(), 0, pRecord);
            }
        }
    }
    while (SetupFindNextLine(&InfContext, &InfContext));

    /* Find default os in list */
    lResult = SendDlgItemMessageW(hwndDlg, IDC_STRECOSCOMBO, CB_FINDSTRING, (WPARAM)-1, (LPARAM)szDefaultOs);
    if (lResult != CB_ERR)
    {
        /* Set cur sel */
        SendDlgItemMessageW(hwndDlg, IDC_STRECOSCOMBO, CB_SETCURSEL, (WPARAM)lResult, (LPARAM)0);
    }

    if(TimeOut)
    {
        SendDlgItemMessageW(hwndDlg, IDC_STRECLIST, BM_SETCHECK, (WPARAM)BST_CHECKED, (LPARAM)0);
    }

    SetTimeout(hwndDlg, TimeOut);

    return TRUE;
}