static
VOID
ShowFailureActions(
    HWND hwndDlg,
    PRECOVERYDATA pRecoveryData)
{
    WCHAR szBuffer[256];
    PWSTR startPtr, endPtr;
    INT i, index, id, length;

    for (i = 0; i < min(pRecoveryData->pServiceFailure->cActions, 3); i++)
    {
        index = -1;

        switch (pRecoveryData->pServiceFailure->lpsaActions[i].Type)
        {
            case SC_ACTION_NONE:
                index = 0;
                break;

            case SC_ACTION_RESTART:
                index = 1;

                wsprintf(szBuffer, L"%lu", pRecoveryData->pServiceFailure->lpsaActions[i].Delay / 60000);
                SendDlgItemMessageW(hwndDlg,
                                    IDC_RESTART_TIME,
                                    WM_SETTEXT,
                                    0,
                                    (LPARAM)szBuffer);

                for (id = IDC_RESTART_TEXT1; id <= IDC_RESTART_TEXT2; id++)
                     EnableWindow(GetDlgItem(hwndDlg, id), TRUE);
                break;

            case SC_ACTION_REBOOT:
                index = 3;

                EnableWindow(GetDlgItem(hwndDlg, IDC_RESTART_OPTIONS), TRUE);
                break;

            case SC_ACTION_RUN_COMMAND:
                index = 2;

                for (id = IDC_RUN_GROUPBOX; id <= IDC_ADD_FAILCOUNT; id++)
                    EnableWindow(GetDlgItem(hwndDlg, id), TRUE);
                break;
        }

        if (index != -1)
        {
            SendDlgItemMessageW(hwndDlg,
                                IDC_FIRST_FAILURE + i,
                                CB_SETCURSEL,
                                index,
                                0);
        }
    }

    wsprintf(szBuffer, L"%lu", pRecoveryData->pServiceFailure->dwResetPeriod / 86400);
    SendDlgItemMessageW(hwndDlg,
                        IDC_RESET_TIME,
                        WM_SETTEXT,
                        0,
                        (LPARAM)szBuffer);

    if (pRecoveryData->pServiceFailure->lpCommand != NULL)
    {
        ZeroMemory(szBuffer, sizeof(szBuffer));

        startPtr = pRecoveryData->pServiceFailure->lpCommand;
        if (*startPtr == L'\"')
            startPtr++;

        endPtr = wcschr(startPtr, L'\"');
        if (endPtr != NULL)
        {
            length = (INT)((LONG_PTR)endPtr - (LONG_PTR)startPtr);
            CopyMemory(szBuffer, startPtr, length);
        }
        else
        {
            wcscpy(szBuffer, startPtr);
        }

        SendDlgItemMessageW(hwndDlg,
                            IDC_PROGRAM,
                            WM_SETTEXT,
                            0,
                            (LPARAM)szBuffer);

        ZeroMemory(szBuffer, sizeof(szBuffer));

        if (endPtr != NULL)
        {
            startPtr = endPtr + 1;
            while (iswspace(*startPtr))
                startPtr++;

            endPtr = wcsstr(pRecoveryData->pServiceFailure->lpCommand, L"/fail=%1%");
            if (endPtr != NULL)
            {
                while (iswspace(*(endPtr - 1)))
                    endPtr--;

                length = (INT)((LONG_PTR)endPtr - (LONG_PTR)startPtr);
                CopyMemory(szBuffer, startPtr, length);
            }
            else
            {
                wcscpy(szBuffer, startPtr);
            }

            SendDlgItemMessageW(hwndDlg,
                                IDC_PARAMETERS,
                                WM_SETTEXT,
                                0,
                                (LPARAM)szBuffer);

            endPtr = wcsstr(pRecoveryData->pServiceFailure->lpCommand, L"/fail=%1%");
            if (endPtr != NULL)
            {
                SendDlgItemMessageW(hwndDlg,
                                    IDC_ADD_FAILCOUNT,
                                    BM_SETCHECK,
                                    BST_CHECKED,
                                    0);
            }
        }
    }
}