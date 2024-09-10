/*
 * Check workdir\fname is inside config_dir
 * The logic here is simple: we may reject some valid paths if ..\ is in any of the strings
 */
static BOOL
CheckConfigPath(const WCHAR *workdir, const WCHAR *fname, const settings_t *s)
{
    WCHAR tmp[MAX_PATH];
    const WCHAR *config_file = NULL;
    const WCHAR *config_dir = NULL;

    /* convert fname to full path */
    if (PathIsRelativeW(fname) )
    {
        snwprintf(tmp, _countof(tmp), L"%s\\%s", workdir, fname);
        tmp[_countof(tmp)-1] = L'\0';
        config_file = tmp;
    }
    else
    {
        config_file = fname;
    }

#ifdef UNICODE
    config_dir = s->config_dir;
#else
    if (MultiByteToWideChar(CP_UTF8, 0, s->config_dir, -1, widepath, MAX_PATH) == 0)
    {
        MsgToEventLog(M_SYSERR, TEXT("Failed to convert config_dir name to WideChar"));
        return FALSE;
    }
    config_dir = widepath;
#endif

    if (wcsncmp(config_dir, config_file, wcslen(config_dir)) == 0
        && wcsstr(config_file + wcslen(config_dir), L"..") == NULL)
    {
        return TRUE;
    }

    return FALSE;
}