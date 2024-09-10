static
BOOL
DoLogon(
    IN HWND hwndDlg,
    IN OUT PGINA_CONTEXT pgContext)
{
    LPWSTR UserName = NULL;
    LPWSTR Password = NULL;
    LPWSTR Domain = NULL;
    BOOL result = FALSE;
    NTSTATUS Status, SubStatus = STATUS_SUCCESS;

    if (GetTextboxText(hwndDlg, IDC_USERNAME, &UserName) && *UserName == '\0')
        goto done;

    if (GetTextboxText(hwndDlg, IDC_LOGON_TO, &Domain) && *Domain == '\0')
        goto done;

    if (!GetTextboxText(hwndDlg, IDC_PASSWORD, &Password))
        goto done;

    Status = DoLoginTasks(pgContext, UserName, Domain, Password, &SubStatus);
    if (Status == STATUS_LOGON_FAILURE)
    {
        ResourceMessageBox(pgContext,
                           hwndDlg,
                           MB_OK | MB_ICONEXCLAMATION,
                           IDS_LOGONTITLE,
                           IDS_LOGONWRONGUSERORPWD);
        goto done;
    }
    else if (Status == STATUS_ACCOUNT_RESTRICTION)
    {
        TRACE("DoLoginTasks failed! Status 0x%08lx  SubStatus 0x%08lx\n", Status, SubStatus);

        if (SubStatus == STATUS_ACCOUNT_DISABLED)
        {
            ResourceMessageBox(pgContext,
                               hwndDlg,
                               MB_OK | MB_ICONEXCLAMATION,
                               IDS_LOGONTITLE,
                               IDS_LOGONUSERDISABLED);
            goto done;
        }
        else if (SubStatus == STATUS_ACCOUNT_LOCKED_OUT)
        {
            TRACE("Account locked!\n");
            pgContext->pWlxFuncs->WlxMessageBox(pgContext->hWlx,
                                                hwndDlg,
                                                L"Account locked!",
                                                L"Logon error",
                                                MB_OK | MB_ICONERROR);
            goto done;
        }
        else if ((SubStatus == STATUS_PASSWORD_MUST_CHANGE) ||
                 (SubStatus == STATUS_PASSWORD_EXPIRED))
        {
            if (SubStatus == STATUS_PASSWORD_MUST_CHANGE)
                ResourceMessageBox(pgContext,
                                   hwndDlg,
                                   MB_OK | MB_ICONSTOP,
                                   IDS_LOGONTITLE,
                                   IDS_PASSWORDMUSTCHANGE);
            else
                ResourceMessageBox(pgContext,
                                   hwndDlg,
                                   MB_OK | MB_ICONSTOP,
                                   IDS_LOGONTITLE,
                                   IDS_PASSWORDEXPIRED);

            if (!OnChangePassword(hwndDlg,
                                  pgContext))
                goto done;

            Status = DoLoginTasks(pgContext,
                                  pgContext->UserName,
                                  pgContext->Domain,
                                  pgContext->Password,
                                  &SubStatus);
            if (!NT_SUCCESS(Status))
            {
                TRACE("Login after password change failed! (Status 0x%08lx)\n", Status);

                goto done;
            }
        }
        else
        {
            TRACE("Other error!\n");
            pgContext->pWlxFuncs->WlxMessageBox(pgContext->hWlx,
                                                hwndDlg,
                                                L"Other error!",
                                                L"Logon error",
                                                MB_OK | MB_ICONERROR);
            goto done;
        }
    }
    else if (!NT_SUCCESS(Status))
    {
        TRACE("DoLoginTasks failed! Status 0x%08lx\n", Status);

        goto done;
    }


    if (!CreateProfile(pgContext, UserName, Domain, Password))
    {
        ERR("Failed to create the profile!\n");
        goto done;
    }

    ZeroMemory(pgContext->Password, 256 * sizeof(WCHAR));
    wcscpy(pgContext->Password, Password);

    result = TRUE;

done:
    if (UserName != NULL)
        HeapFree(GetProcessHeap(), 0, UserName);

    if (Password != NULL)
        HeapFree(GetProcessHeap(), 0, Password);

    if (Domain != NULL)
        HeapFree(GetProcessHeap(), 0, Domain);

    return result;
}