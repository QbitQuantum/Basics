/*-----------------------------------------------------------------------------
SetUserThreshold(IDiskQuotaControl* lpDiskQuotaControl)
    Set the warning threshold limit for a specific user

Parameters
    lpDiskQuotaControl - Pointer to an object that implements the
                         IDiskQuotaControl interface

Return Value
    TRUE - Success
    FALSE - Failure
-----------------------------------------------------------------------------*/
BOOL SetUserThreshold(IDiskQuotaControl* lpDiskQuotaControl)
{
    HRESULT  hr;
    IDiskQuotaUser* lpDiskQuotaUser;
    WCHAR    szUser[MAX_PATH] = {0};
    DWORD    dwCharsRead;
    LONGLONG llLimit = 0;
    HANDLE   hStdIn  = GetStdHandle(STD_INPUT_HANDLE);

    wprintf(L"\n\nEnter the logon name of the user ");
    wprintf(L"(ie. DOMAIN\\USERNAME): ");

    // Get the user for which to set a hard limit
    ReadConsole(hStdIn, szUser, MAX_PATH, &dwCharsRead, NULL);

    szUser[MAX_PATH-1] = L'\0'; // make sure szUSer is NULL terminated

    // Strip the line feed and carriage return
    LfcrToNull(szUser);

    // Check if the name is valid
    hr = lpDiskQuotaControl->FindUserName((LPCWSTR)szUser, &lpDiskQuotaUser);

    if (SUCCEEDED(hr))
    {
        WCHAR    szLimit[MAX_PATH] = {0};
        wprintf(L"\nEnter the new hard limit in bytes (-1 == No Limit): ");

        // Read the threshold from the console
        ReadConsole(hStdIn, szLimit, MAX_PATH, &dwCharsRead, NULL);
        LfcrToNull(szLimit);
        llLimit = _wtoi64(szLimit);

        if (llLimit >= -1)
        {
            // Set the warning threshold for the user
            hr = lpDiskQuotaUser->SetQuotaThreshold(llLimit, TRUE);

            if (FAILED(hr))
            {
                wprintf(L"\nCould not set the quota limit for %s", szUser);
                wprintf(L"to %i64 bytes\n", llLimit);
            }
        }
        else
        {
            wprintf(L"\nInvalid limit!");
        }
        lpDiskQuotaUser->Release();
    }
    else
    {
        PrintError(hr);
    }

    return SUCCEEDED(hr);
}