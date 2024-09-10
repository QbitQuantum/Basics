bool GetRealURL(std::string url, int maxsize, std::string &outstr, int timeout = 10)
{
    char buffer[HTTP_BUFFER_LEN];//下载文件的缓冲区
    DWORD bytes_read = 1;//下载的字节数
    bool getre = false;
    outstr = "";

    if(url.length() < 6)
        return false;

    //打开一个internet连接
    HINTERNET internet=InternetOpen(_T("HTTP"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, NULL);
    if(!internet)
        return false;

    DWORD dtimeout = timeout * 300;
    InternetSetOption(internet, INTERNET_OPTION_CONNECT_TIMEOUT, &dtimeout, sizeof(DWORD));
    InternetSetOption(internet, INTERNET_OPTION_SEND_TIMEOUT, &dtimeout, sizeof(DWORD));
    InternetSetOption(internet, INTERNET_OPTION_RECEIVE_TIMEOUT, &dtimeout, sizeof(DWORD));
    dtimeout = timeout/10;
    InternetSetOption(internet, INTERNET_OPTION_CONNECT_RETRIES, &dtimeout, sizeof(DWORD));

    //打开一个http url地址
    HINTERNET file_handle=InternetOpenUrl(internet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);

    if(file_handle) {
        //从url地址中读取文件内容到缓冲区buffer
        BOOL b = 0;
        int readbyte = 0;
        while(bytes_read > 0) {
            b = InternetReadFile(file_handle, buffer, 512 , &bytes_read);
            if(!b)
                break;
            readbyte += bytes_read;
            buffer[bytes_read] = 0;
            outstr += buffer;
        }
        getre = true;
    }
    //关闭连接
    InternetCloseHandle(internet);

    return getre;
}