BOOL CMainDlg::RawPrint(LPTSTR fileName)
{
    HANDLE p, f;
    p = f = INVALID_HANDLE_VALUE;
    LPBYTE buffer = NULL;
    DWORD err = ERROR_SUCCESS, w, size, r;
    WTL::CString ballon, message;
    CRPTray rwtray;

    WTL::CString printer = CMainDlg::GetRawPrinter();
    if (!printer.GetLength())
    {
        ::MessageBox(NULL, _(IDS_NOPRINTER), _T("RawPrinter"), MB_OK | MB_ICONERROR);
        return FALSE;
    }

    PRINTER_DEFAULTS defaults = { _T("RAW"), 0, PRINTER_ACCESS_USE };
    DOC_INFO_1 doc = { fileName, NULL, _T("RAW") };

    if ((f = ::CreateFile(fileName,
        GENERIC_READ, FILE_SHARE_READ,
        NULL, OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL, NULL)) == INVALID_HANDLE_VALUE)
    {
        message.Format(_(IDS_ERROR_CREATEFILE), fileName, AtlGetErrorDescription(::GetLastError()));
        ::MessageBox(NULL, message, _T("RawPrinter"), MB_OK | MB_ICONERROR);
            goto end;
    }

    size = ::GetFileSize(f, NULL);
    buffer = (LPBYTE) new BYTE[size];
    ::ReadFile(f, buffer, size, &r, NULL);
    ::CloseHandle(f);

    LPTSTR fn = _tcsrchr(fileName, _T('\\'));
    ballon.Format(_(IDS_PRINTING), fn ? fn + 1: fileName, printer);
    rwtray.Ballon(ballon, 3000);

    CALL(::OpenPrinter(printer.GetBuffer(0), &p, &defaults), OpenPrinter);
    CALL(::StartDocPrinter(p, 1, (LPBYTE) &doc), StartDocPrinter);
    CALL(::StartPagePrinter(p), StartPagePrinter);
    CALL(::WritePrinter(p, buffer, size, &w), WritePrinter);
    CALL(::EndPagePrinter(p), EndPagePrinter);
    CALL(::EndDocPrinter(p), EndDocPrinter);

end:
    if (buffer) delete buffer;
    ClosePrinter(p);
    return TRUE;
}