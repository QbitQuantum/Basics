/*--------------------------------------------------------------------------*/
wchar_t *createtempfilenameW(const wchar_t *wcprefix, BOOL bShortFormat)
{
    wchar_t *wcReturnedTempFilename = NULL;

#ifdef _MSC_VER
    wchar_t *wcTmpDir = getTMPDIRW();
    if (wcTmpDir)
    {
        unsigned int uRetVal = 0;
        wchar_t wcTempFileName[MAX_PATH];
        uRetVal = GetTempFileNameW(wcTmpDir, wcprefix, 0, wcTempFileName);
        if (uRetVal != 0)
        {
            size_t len = wcslen(wcTempFileName) + 1;
            wchar_t* shortTempFilename = (wchar_t *)MALLOC(len * sizeof(wchar_t));
            if (shortTempFilename)
            {
                if (bShortFormat)
                {
                    GetShortPathNameW(wcTempFileName, shortTempFilename, (DWORD)len);
                }
                wcReturnedTempFilename = shortTempFilename;
            }
        }

        FREE(wcTmpDir);
    }
#else
    char *prefix = wide_string_to_UTF8(wcprefix);
    char *result = createtempfilename(prefix, bShortFormat);

    wcReturnedTempFilename = to_wide_string(result);

    if (result)
    {
        FREE(result);
        result = NULL;
    }
    if (prefix)
    {
        FREE(prefix);
        prefix = NULL;
    }
    if (result)
    {
        FREE(result);
        result = NULL;
    }
#endif
    return wcReturnedTempFilename;
}