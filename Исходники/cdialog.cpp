//---------------------------------------------------------------------------
HRESULT CSimpleDialog::AddStatusMessage(LPCWSTR wszFormat, ...)
{
    HRESULT    hr                          = S_OK;
    HWND       hJobStatus;
    WCHAR      *pwszExistingText           = NULL;
    DWORD      cchExistingText             = 0;
    WCHAR      *pwszBuf                    = NULL;
    DWORD      cchBuf                      = 0;
    SYSTEMTIME Time;
    WCHAR      wszTimeBuf[20]              = {0};
    WCHAR      wszNewText[MAX_BUFFER_SIZE] = {0};
    

    if (!wszFormat)
    {
        return S_OK;
    }

    // 
    // Build a string with the text passed as a parameter
    //
    va_list arglist;
    va_start(arglist, wszFormat);

    hr = StringCchVPrintfW(wszNewText, MAX_BUFFER_SIZE, wszFormat, arglist);
    if (FAILED(hr))
    {
        goto cleanup;
    }

    //
    // Retrieve the text that is currently displayed in the Edit box
    //

    hJobStatus      = GetDlgItem(m_hWnd, IDC_JOBSTATUS);
    cchExistingText = GetWindowTextLength(hJobStatus) + 1;

    if (cchExistingText)
    {
        pwszExistingText = new WCHAR[cchExistingText];
        if (!pwszExistingText)
        {
            hr = E_OUTOFMEMORY;
            goto cleanup;
        }

        GetWindowText(hJobStatus, pwszExistingText, cchExistingText);
    }

    //
    // Get a string for the current time
    //

    GetLocalTime(&Time);
    hr = StringCchPrintfW(wszTimeBuf, ARRAYSIZE(wszTimeBuf), L"[%.2u:%.2u %.2u.%.3us] ", Time.wHour, Time.wMinute, Time.wSecond, Time.wMilliseconds);
    if (FAILED(hr))
    {
        goto cleanup;
    }

    //
    // Allocate a buffer for the new contents of the edit box
    //
    cchBuf  = cchExistingText + static_cast<DWORD>(wcslen(wszTimeBuf)) + static_cast<DWORD>(wcslen(wszNewText)) + 2 + 1;  // 2 for the break line
    pwszBuf = new WCHAR[cchBuf];
    if (!pwszBuf)
    {
        hr = E_OUTOFMEMORY;
        goto cleanup;
    }
    pwszBuf[0] = L'\0';

    //
    // Build the new string
    //
    hr = StringCchPrintfW(pwszBuf, cchBuf, L"%s%s%s\r\n", (pwszExistingText? pwszExistingText : L""), wszTimeBuf, wszNewText);
    if (FAILED(hr))
    {
        goto cleanup;
    }

    //
    // Update the control with the new string
    //
    if (!SetWindowText(hJobStatus, pwszBuf))
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
        goto cleanup;
    }

    //
    // Automatically scroll down the edit box
    //
    SendMessage(hJobStatus, EM_SETSEL, (WPARAM)0, (LPARAM)-1);
	SendMessage(hJobStatus, EM_SCROLLCARET, 0, 0);

cleanup:

    va_end(arglist);

    if (pwszExistingText)
    {
        delete [] pwszExistingText;
        pwszExistingText = NULL;
    }

    if (pwszBuf)
    {
        delete [] pwszBuf;
        pwszBuf = NULL;
    }

    return hr;
}