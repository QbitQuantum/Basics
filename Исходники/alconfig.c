void ReadALConfig(void)
{
    al_string ppath = AL_STRING_INIT_STATIC();
    WCHAR buffer[MAX_PATH];
    const WCHAR *str;
    FILE *f;

    if(SHGetSpecialFolderPathW(NULL, buffer, CSIDL_APPDATA, FALSE) != FALSE)
    {
        al_string filepath = AL_STRING_INIT_STATIC();
        alstr_copy_wcstr(&filepath, buffer);
        alstr_append_cstr(&filepath, "\\alsoft.ini");

        TRACE("Loading config %s...\n", alstr_get_cstr(filepath));
        f = al_fopen(alstr_get_cstr(filepath), "rt");
        if(f)
        {
            LoadConfigFromFile(f);
            fclose(f);
        }
        alstr_reset(&filepath);
    }

    GetProcBinary(&ppath, NULL);
    if(!alstr_empty(ppath))
    {
        alstr_append_cstr(&ppath, "\\alsoft.ini");
        TRACE("Loading config %s...\n", alstr_get_cstr(ppath));
        f = al_fopen(alstr_get_cstr(ppath), "r");
        if(f)
        {
            LoadConfigFromFile(f);
            fclose(f);
        }
    }

    if((str=_wgetenv(L"ALSOFT_CONF")) != NULL && *str)
    {
        al_string filepath = AL_STRING_INIT_STATIC();
        alstr_copy_wcstr(&filepath, str);

        TRACE("Loading config %s...\n", alstr_get_cstr(filepath));
        f = al_fopen(alstr_get_cstr(filepath), "rt");
        if(f)
        {
            LoadConfigFromFile(f);
            fclose(f);
        }
        alstr_reset(&filepath);
    }

    alstr_reset(&ppath);
}