bool CHTTPDirectory::Exists(const char* strPath)
{
    CCurlFile http;
    CURL url(strPath);
    struct __stat64 buffer;

    if( http.Stat(url, &buffer) != 0 )
    {
        return false;
    }

    if (buffer.st_mode == _S_IFDIR)
        return true;

    return false;
}