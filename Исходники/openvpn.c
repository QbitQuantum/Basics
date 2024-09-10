/*
 * Write a line to the status log window and optionally to the log file
 */
static void
WriteStatusLog (connection_t *c, const WCHAR *prefix, const WCHAR *line, BOOL fileio)
{
    HWND logWnd = GetDlgItem(c->hwndStatus, ID_EDT_LOG);
    FILE *log_fd;
    time_t now;
    WCHAR datetime[26];

    time (&now);
    /* TODO: change this to use _wctime_s when mingw supports it */
    wcsncpy (datetime, _wctime(&now), _countof(datetime));
    datetime[24] = L' ';

    /* Remove lines from log window if it is getting full */
    if (SendMessage(logWnd, EM_GETLINECOUNT, 0, 0) > MAX_LOG_LINES)
    {
        int pos = SendMessage(logWnd, EM_LINEINDEX, DEL_LOG_LINES, 0);
        SendMessage(logWnd, EM_SETSEL, 0, pos);
        SendMessage(logWnd, EM_REPLACESEL, FALSE, (LPARAM) _T(""));
    }
    /* Append line to log window */
    SendMessage(logWnd, EM_SETSEL, (WPARAM) -1, (LPARAM) -1);
    SendMessage(logWnd, EM_REPLACESEL, FALSE, (LPARAM) datetime);
    SendMessage(logWnd, EM_REPLACESEL, FALSE, (LPARAM) prefix);
    SendMessage(logWnd, EM_REPLACESEL, FALSE, (LPARAM) line);
    SendMessage(logWnd, EM_REPLACESEL, FALSE, (LPARAM) L"\n");

    if (!fileio) return;

    log_fd = _tfopen (c->log_path, TEXT("at+,ccs=UTF-8"));
    if (log_fd)
    {
        fwprintf (log_fd, L"%s%s%s\n", datetime, prefix, line);
        fclose (log_fd);
    }
}