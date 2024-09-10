BOOL INSTAPI
SQLReadFileDSNW (LPCWSTR lpszFileName, LPCWSTR lpszAppName,
                 LPCWSTR lpszKeyName, LPWSTR lpszString, WORD cbString, WORD * pcbString)
{
    char *_filename_u8 = NULL;
    char *_appname_u8 = NULL;
    char *_keyname_u8 = NULL;
    char *_string_u8 = NULL;
    BOOL retcode = FALSE;

    _filename_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszFileName, SQL_NTS);
    if (_filename_u8 == NULL && lpszFileName)
    {
        PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
        goto done;
    }

    _appname_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszAppName, SQL_NTS);
    if (_appname_u8 == NULL && lpszAppName)
    {
        PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
        goto done;
    }

    _keyname_u8 = (char *) dm_SQL_WtoU8 ((SQLWCHAR *) lpszKeyName, SQL_NTS);
    if (_keyname_u8 == NULL && lpszKeyName)
    {
        PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
        goto done;
    }

    if (cbString > 0)
    {
        if ((_string_u8 = malloc (cbString * UTF8_MAX_CHAR_LEN + 1)) == NULL)
        {
            PUSH_ERROR (ODBC_ERROR_OUT_OF_MEM);
            goto done;
        }
    }

    retcode =
        SQLReadFileDSN (_filename_u8, _appname_u8, _keyname_u8, _string_u8,
                        cbString * UTF8_MAX_CHAR_LEN, pcbString);

    if (retcode == TRUE)
    {
        dm_StrCopyOut2_U8toW (_string_u8, lpszString, cbString, pcbString);
    }

done:
    MEM_FREE (_filename_u8);
    MEM_FREE (_appname_u8);
    MEM_FREE (_keyname_u8);
    MEM_FREE (_string_u8);

    return retcode;
}