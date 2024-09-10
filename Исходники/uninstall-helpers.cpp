int delete_dir_recursively(const QString& path_in)
{
    qWarning ("removing folder %s\n", toCStr(path_in));
#if defined(Q_OS_WIN32)
    const QString path = QDir::toNativeSeparators(QDir::cleanPath(path_in));
    if (path.length() <= 3) {
        // avoid errornous delete drives like C:/ D:/ E:/
        return -1;
    }

    int len = path.length();

    wchar_t *wpath = new wchar_t[len + 2];

    wcscpy(wpath, path.toStdWString().c_str());
    wpath[len + 1] = L'\0';

    SHFILEOPSTRUCTW fileop;
    fileop.hwnd   = NULL;       // no status display
    fileop.wFunc  = FO_DELETE;  // delete operation
    fileop.pFrom  = wpath; // source file name as double null terminated string
    fileop.pTo    = NULL;         // no destination needed
    fileop.fFlags = FOF_NOCONFIRMATION|FOF_SILENT; // do not prompt the user

    fileop.fAnyOperationsAborted = FALSE;
    fileop.lpszProgressTitle     = NULL;
    fileop.hNameMappings         = NULL;

    int ret = SHFileOperationW(&fileop);

    delete []wpath;

    if (ret == 0) {
        return 0;
    } else {
        return -1;
    }
    return 0;
#else
    return posix_rmdir(path_in);
#endif
}