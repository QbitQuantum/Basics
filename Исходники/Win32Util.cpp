FILE *tmpfile(const wchar_t *prefix)
{
    std::wstring sprefix =
        strutil::format(L"%s.%d.", prefix, GetCurrentProcessId());
    wchar_t *tmpname = _wtempnam(0, sprefix.c_str());
    std::shared_ptr<wchar_t> tmpname_p(tmpname, std::free);
    HANDLE fh = CreateFileW(prefixed_path(tmpname).c_str(),
                            GENERIC_READ | GENERIC_WRITE,
                            0, 0, CREATE_ALWAYS,
                            FILE_ATTRIBUTE_TEMPORARY |
                            FILE_FLAG_DELETE_ON_CLOSE,
                            0);
    if (fh == INVALID_HANDLE_VALUE)
        throw_error(tmpname, GetLastError());
    int fd = _open_osfhandle(reinterpret_cast<intptr_t>(fh),
                             _O_BINARY|_O_RDWR);
    if (fd == -1) {
        CloseHandle(fh);
        util::throw_crt_error("win32::tmpfile: open_osfhandle()");
    }
    FILE *fp = _fdopen(fd, "w+");
    if (!fp) {
        _close(fd);
        util::throw_crt_error("win32::tmpfile: _fdopen()");
    }
    return fp;
}