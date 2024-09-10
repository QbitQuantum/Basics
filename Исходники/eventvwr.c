BOOL
QueryEventMessages(LPWSTR lpMachineName,
                   LPWSTR lpLogName)
{
    HWND hwndDlg = NULL;
    HANDLE hEventLog;
    EVENTLOGRECORD *pevlr;
    DWORD dwRead, dwNeeded, dwThisRecord, dwTotalRecords = 0, dwCurrentRecord = 0, dwRecordsToRead = 0, dwFlags, dwMaxLength;
    size_t cchRemaining;
    LPWSTR lpSourceName;
    LPWSTR lpComputerName;
    LPSTR lpData;
    BOOL bResult = TRUE; /* Read succeeded. */

    WCHAR szWindowTitle[MAX_PATH];
    WCHAR szStatusText[MAX_PATH];
    WCHAR szLocalDate[MAX_PATH];
    WCHAR szLocalTime[MAX_PATH];
    WCHAR szEventID[MAX_PATH];
    WCHAR szEventTypeText[MAX_LOADSTRING];
    WCHAR szCategoryID[MAX_PATH];
    WCHAR szUsername[MAX_PATH];
    WCHAR szEventText[EVENT_MESSAGE_FILE_BUFFER];
    WCHAR szCategory[MAX_PATH];
    WCHAR szData[MAX_PATH];
    PWCHAR lpTitleTemplateEnd;

    SYSTEMTIME time;
    LVITEMW lviEventItem;

    dwFlags = EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ;

    /* Open the event log. */
    hEventLog = OpenEventLogW(lpMachineName,
                             lpLogName);
    if (hEventLog == NULL)
    {
        ShowLastWin32Error();
        return FALSE;
    }

    lpSourceLogName = lpLogName;
    lpComputerName = lpMachineName;

    /* Disable listview redraw */
    SendMessage(hwndListView, WM_SETREDRAW, FALSE, 0);

    /* Clear the list view */
    (void)ListView_DeleteAllItems (hwndListView);
    FreeRecords();

    GetOldestEventLogRecord(hEventLog, &dwThisRecord);

    /* Get the total number of event log records. */
    GetNumberOfEventLogRecords (hEventLog , &dwTotalRecords);
    g_TotalRecords = dwTotalRecords;

    if (dwTotalRecords > 0)
    {
        EnableMenuItem(hMainMenu, IDM_CLEAR_EVENTS, MF_BYCOMMAND | MF_ENABLED);
        EnableMenuItem(hMainMenu, IDM_SAVE_PROTOCOL, MF_BYCOMMAND | MF_ENABLED);
    }
    else
    {
        EnableMenuItem(hMainMenu, IDM_CLEAR_EVENTS, MF_BYCOMMAND | MF_GRAYED);
        EnableMenuItem(hMainMenu, IDM_SAVE_PROTOCOL, MF_BYCOMMAND | MF_GRAYED);
    }

    g_RecordPtrs = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwTotalRecords * sizeof(PVOID));

    /* If we have at least 1000 records show the waiting dialog */
    if (dwTotalRecords > 1000)
    {
        CloseHandle(CreateThread(NULL,
                                 0,
                                 ShowStatusMessageThread,
                                 (LPVOID)&hwndDlg,
                                 0,
                                 NULL));
    }

    while (dwCurrentRecord < dwTotalRecords)
    {
        pevlr = HeapAlloc(GetProcessHeap(), 0, sizeof(EVENTLOGRECORD));
        g_RecordPtrs[dwCurrentRecord] = pevlr;

        bResult = ReadEventLog(hEventLog,  // Event log handle
                               dwFlags,    // Sequential read
                               0,          // Ignored for sequential read
                               pevlr,      // Pointer to buffer
                               sizeof(EVENTLOGRECORD),   // Size of buffer
                               &dwRead,    // Number of bytes read
                               &dwNeeded); // Bytes in the next record
        if((!bResult) && (GetLastError () == ERROR_INSUFFICIENT_BUFFER))
        {
            HeapFree(GetProcessHeap(), 0, pevlr);
            pevlr = HeapAlloc(GetProcessHeap(), 0, dwNeeded);
            g_RecordPtrs[dwCurrentRecord] = pevlr;

            ReadEventLogW(hEventLog,  // event log handle
                         dwFlags,    // read flags
                         0,          // offset; default is 0
                         pevlr,      // pointer to buffer
                         dwNeeded,   // size of buffer
                         &dwRead,    // number of bytes read
                         &dwNeeded); // bytes in next record
        }

        while (dwRead > 0)
        {
            LoadStringW(hInst, IDS_NOT_AVAILABLE, szUsername, MAX_PATH);
            LoadStringW(hInst, IDS_NOT_AVAILABLE, szEventText, MAX_PATH);
            LoadStringW(hInst, IDS_NONE, szCategory, MAX_PATH);

            // Get the event source name.
            lpSourceName = (LPWSTR)((LPBYTE)pevlr + sizeof(EVENTLOGRECORD));

            // Get the computer name
            lpComputerName = (LPWSTR)((LPBYTE)pevlr + sizeof(EVENTLOGRECORD) + (wcslen(lpSourceName) + 1) * sizeof(WCHAR));

            // This ist the data section of the current event
            lpData = (LPSTR)((LPBYTE)pevlr + pevlr->DataOffset);

            // Compute the event type
            EventTimeToSystemTime(pevlr->TimeWritten, &time);

            // Get the username that generated the event
            GetEventUserName(pevlr, szUsername);

            GetDateFormatW(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &time, NULL, szLocalDate, MAX_PATH);
            GetTimeFormatW(LOCALE_USER_DEFAULT, 0, &time, NULL, szLocalTime, MAX_PATH);

            GetEventType(pevlr->EventType, szEventTypeText);
            GetEventCategory(lpLogName, lpSourceName, pevlr, szCategory);

            StringCbPrintfW(szEventID, sizeof(szEventID), L"%u", (pevlr->EventID & 0xFFFF));
            StringCbPrintfW(szCategoryID, sizeof(szCategoryID), L"%u", pevlr->EventCategory);

            lviEventItem.mask = LVIF_IMAGE | LVIF_TEXT | LVIF_PARAM;
            lviEventItem.iItem = 0;
            lviEventItem.iSubItem = 0;
            lviEventItem.lParam = (LPARAM)pevlr;
            lviEventItem.pszText = szEventTypeText;

            switch (pevlr->EventType)
            {
                case EVENTLOG_ERROR_TYPE:
                    lviEventItem.iImage = 2;
                    break;

                case EVENTLOG_AUDIT_FAILURE:
                    lviEventItem.iImage = 2;
                    break;

                case EVENTLOG_WARNING_TYPE:
                    lviEventItem.iImage = 1;
                    break;

                case EVENTLOG_INFORMATION_TYPE:
                    lviEventItem.iImage = 0;
                    break;

                case EVENTLOG_AUDIT_SUCCESS:
                    lviEventItem.iImage = 0;
                    break;

                case EVENTLOG_SUCCESS:
                    lviEventItem.iImage = 0;
                    break;
            }

            lviEventItem.iItem = ListView_InsertItem(hwndListView, &lviEventItem);

            ListView_SetItemText(hwndListView, lviEventItem.iItem, 1, szLocalDate);
            ListView_SetItemText(hwndListView, lviEventItem.iItem, 2, szLocalTime);
            ListView_SetItemText(hwndListView, lviEventItem.iItem, 3, lpSourceName);
            ListView_SetItemText(hwndListView, lviEventItem.iItem, 4, szCategory);
            ListView_SetItemText(hwndListView, lviEventItem.iItem, 5, szEventID);
            ListView_SetItemText(hwndListView, lviEventItem.iItem, 6, szUsername); //User
            ListView_SetItemText(hwndListView, lviEventItem.iItem, 7, lpComputerName); //Computer
            MultiByteToWideChar(CP_ACP,
                                0,
                                lpData,
                                pevlr->DataLength,
                                szData,
                                MAX_PATH);
            ListView_SetItemText(hwndListView, lviEventItem.iItem, 8, szData); //Event Text

            dwRead -= pevlr->Length;
            pevlr = (EVENTLOGRECORD *)((LPBYTE) pevlr + pevlr->Length);
        }

        dwRecordsToRead--;
        dwCurrentRecord++;
    }

    // All events loaded
    if(hwndDlg)
        EndDialog(hwndDlg, 0);

    StringCchPrintfExW(szWindowTitle,
                       sizeof(szWindowTitle) / sizeof(WCHAR),
                       &lpTitleTemplateEnd,
                       &cchRemaining,
                       0,
                       szTitleTemplate, szTitle, lpLogName); /* i = number of characters written */
    /* lpComputerName can be NULL here if no records was read */
    dwMaxLength = (DWORD)cchRemaining;
    if (!lpComputerName)
        GetComputerNameW(lpTitleTemplateEnd, &dwMaxLength);
    else
        StringCchCopyW(lpTitleTemplateEnd, dwMaxLength, lpComputerName);

    StringCbPrintfW(szStatusText, sizeof(szStatusText), szStatusBarTemplate, lpLogName, dwTotalRecords);

    // Update the status bar
    SendMessageW(hwndStatus, SB_SETTEXT, (WPARAM)0, (LPARAM)szStatusText);

    // Set the window title
    SetWindowTextW(hwndMainWindow, szWindowTitle);

    // Resume list view redraw
    SendMessageW(hwndListView, WM_SETREDRAW, TRUE, 0);

    // Close the event log.
    CloseEventLog(hEventLog);

    return TRUE;
}