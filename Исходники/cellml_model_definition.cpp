std::string ws2s(const std::wstring& wstr)
{
#ifdef CSIM_HAVE_STD_CODECVT
    typedef std::codecvt_utf8<wchar_t> convert_typeX;
    std::wstring_convert<convert_typeX, wchar_t> converterX;
    return converterX.to_bytes(wstr);
#else
    std::string ss;
    if (wstr.length() > 0)
    {
        const wchar_t* sp = wstr.c_str();
        size_t len = wcsrtombs(NULL,&sp,0,NULL);
        if (len > 0)
        {
            len++;
            char* s = (char*)malloc(len);
            wcsrtombs(s,&sp,len,NULL);
            ss = std::string(s);
            free(s);
            return(ss);
        }
    }
    return(ss);
#endif
}