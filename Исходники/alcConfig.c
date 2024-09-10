void ReadALConfig(void)
{
    WCHAR buffer[PATH_MAX];
    const WCHAR *str;
    FILE *f;

    if(SHGetSpecialFolderPathW(NULL, buffer, CSIDL_APPDATA, FALSE) != FALSE)
    {
        size_t p = lstrlenW(buffer);
        _snwprintf(buffer+p, PATH_MAX-p, L"\\alsoft.ini");

        TRACE("Loading config %ls...\n", buffer);
        f = _wfopen(buffer, L"rt");
        if(f)
        {
            LoadConfigFromFile(f);
            fclose(f);
        }
    }

    if((str=_wgetenv(L"ALSOFT_CONF")) != NULL && *str)
    {
        TRACE("Loading config %ls...\n", str);
        f = _wfopen(str, L"rt");
        if(f)
        {
            LoadConfigFromFile(f);
            fclose(f);
        }
    }
}