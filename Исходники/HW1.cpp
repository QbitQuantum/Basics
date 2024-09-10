bool create_bob_txt()
{
    // current directory 를 구한다.
    wchar_t *buf=NULL;
    uint32_t buflen = 0;
    buflen = GetCurrentDirectoryW(buflen, buf);
        if (0 == buflen)
        {
        print("err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
        return false;
        }
 
        buf = (PWSTR) malloc(sizeof(WCHAR) * buflen);
        if (0 == GetCurrentDirectoryW(buflen, buf))
        {
                print("err, GetCurrentDirectoryW() failed. gle = 0x%08x", GetLastError());
                free(buf);
                return false;
        }
 
    // current dir \\ bob.txt 파일명 생성
    wchar_t file_name[260];
    if (!SUCCEEDED(StringCbPrintfW(
                            file_name,
                            sizeof(file_name),
                            L"%ws\\bob.txt",
                            buf)))
    {  
        print("err, can not create file name");
        free(buf);
        return false;
    }
    free(buf); buf = NULL;
 
    if (true == is_file_existsW(file_name))
    {
        ::DeleteFileW(file_name);
    }
 
    // 파일 생성
    HANDLE file_handle = CreateFileW(
                                file_name,
                                                        GENERIC_WRITE,
                                                        FILE_SHARE_READ,
                                                        NULL,
                                                        CREATE_NEW,
                                                        FILE_ATTRIBUTE_NORMAL,
                                                        NULL); 
        if(file_handle == INVALID_HANDLE_VALUE)
        {                                              
        print("err, CreateFile(path=%ws), gle=0x%08x", file_name, GetLastError());
        return false;
        }
 
    // 파일에 데이터 쓰기
    DWORD bytes_written = 0;
    wchar_t string_buf[1024];
    if (!SUCCEEDED(StringCbPrintfW(
                        string_buf,
                        sizeof(string_buf),
                        L"동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라만세")))
    {
        print("err, can not create data to write.");
        CloseHandle(file_handle);
        return false;
    }
 
    if (!WriteFile(file_handle, string_buf, wcslen(string_buf), &bytes_written, NULL))
    {
        print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
        CloseHandle(file_handle);
        return false;
    }
 
    // 영어로 쓰기
    if (!SUCCEEDED(StringCbPrintfW(
                        string_buf,
                        sizeof(string_buf),
                        L"All work and no play makes jack a dull boy.")))
    {
        print("err, can not create data to write.");
        CloseHandle(file_handle);
        return false;
    }
 
    if (!WriteFile(file_handle, string_buf, wcslen(string_buf), &bytes_written, NULL))
    {
        print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
        CloseHandle(file_handle);
        return false;
    }
 
 
 
 
    char string_bufa[1024];
    if (!SUCCEEDED(StringCbPrintfA(
                        string_bufa,
                        sizeof(string_bufa),
                        "동해물과 백두산이 마르고 닳도록 하느님이 보우하사 우리나라만세")))
    {
        print("err, can not create data to write.");
        CloseHandle(file_handle);
        return false;
    }
 
    if (!WriteFile(file_handle, string_bufa, strlen(string_bufa), &bytes_written, NULL))
    {
        print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
        CloseHandle(file_handle);
        return false;
    }
 
    // 영어로 쓰기
    if (!SUCCEEDED(StringCbPrintfA(
                        string_bufa,
                        sizeof(string_bufa),
                        "All work and no play makes jack a dull boy.")))
    {
        print("err, can not create data to write.");
        CloseHandle(file_handle);
        return false;
    }
 
    if (!WriteFile(file_handle, string_bufa, strlen(string_bufa), &bytes_written, NULL))
    {
        print("err, WriteFile() failed. gle = 0x%08x", GetLastError());
        CloseHandle(file_handle);
        return false;
    }
 
    // 파일 닫기
    CloseHandle(file_handle);
    return true;
 
}