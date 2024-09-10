void CDynamoRIOView::OnEditCopystats()
{
    if (m_ProcessList.GetCurSel() == 0) {
        MessageBox(_T("No instance selected"), _T("Error"), MB_OK | MYMBFLAGS);
        return;
    }
    if (!OpenClipboard()) {
        MessageBox(_T("Error opening clipboard"), _T("Error"),
                   MB_OK | MYMBFLAGS);
        return;
    }
    EmptyClipboard();

#define CLIPBOARD_BUFSZ USHRT_MAX
    TCHAR buf[CLIPBOARD_BUFSZ];
    TCHAR *pos = buf;

    if (m_selected_pid > 0) {
        if (m_stats != NULL) {
            pos += _stprintf(pos, _T("Process id                  = %d\r\n"),
                             m_stats->process_id);
            pos += _stprintf(pos, _T("Process name                = %") ASCII_PRINTF
                             _T("\r\n"), m_stats->process_name);
            pos += _stprintf(pos, _T("Status                      = %s\r\n"),
                             m_Exited.GetBuffer(0));
#ifndef DRGUI_DEMO
            pos += _stprintf(pos, _T("Log mask                    = %s\r\n"),
                             m_LogMask.GetBuffer(0));
            pos += _stprintf(pos, _T("Log level                   = %s\r\n"),
                             m_LogLevel.GetBuffer(0));
            pos += _stprintf(pos, _T("Log file                    = %s\r\n"),
                             m_LogDir.GetBuffer(0));
#endif
            pos += _stprintf(pos, _T("\r\nSTATS\r\n"));
            uint i;
            for (i = 0; i < m_stats->num_stats; i++) {
                if (pos >= &buf[STATS_BUFSZ-STAT_NAME_MAX_LEN*2])
                    break;
                // FIXME: Filter here too
                pos += PrintStat(pos, i, TRUE/*filter*/);
                assert(pos < &buf[STATS_BUFSZ-1]);
            }
        } else {
            CString pname;
            m_ProcessList.GetLBText(m_ProcessList.GetCurSel(), pname);
            _stprintf(pos, _T("%s"), pname);
            pos += _tcslen(pos);
        }
    }
    if (m_clientStats != NULL) {
        pos += PrintClientStats(pos, &buf[STATS_BUFSZ-1]);
    }

    size_t len = _tcslen(buf);

    // Allocate a global memory object for the text.
    HGLOBAL hglbCopy = GlobalAlloc(GMEM_DDESHARE,
                                   (len + 1) * sizeof(TCHAR));
    if (hglbCopy == NULL) {
        CloseClipboard();
        return;
    }

    // Lock the handle and copy the text to the buffer.
    LPTSTR lptstrCopy = (LPTSTR) GlobalLock(hglbCopy);
    memcpy(lptstrCopy, buf, (len + 1) * sizeof(TCHAR));
    lptstrCopy[len] = (TCHAR) 0;    // null TCHARacter
    GlobalUnlock(hglbCopy);

    // Place the handle on the clipboard.
    SetClipboardData(
#ifdef UNICODE
        CF_UNICODETEXT,
#else
        CF_TEXT,
#endif
        hglbCopy);

    CloseClipboard();
}