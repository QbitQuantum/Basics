bool dial_open_conn(const char *name)
{
    BOOL pwd;
    DWORD ret, i = 0;
    HRASCONN conn = NULL;
    RASDIALPARAMSW params;

    if (dial_find_conn(name))
        return TRUE;

    memset(&params, 0, sizeof(params));
    params.dwSize = sizeof(params);
    while (i < (sizeof(params.szEntryName) - 1)) {
        if (!(params.szEntryName[i] = name[i]))
            break;
        ++i;
    }
    ret = RasGetEntryDialParamsW(NULL, &params, &pwd);
    if (ERROR_SUCCESS != ret)
        return FALSE;

    ret = RasDialW(NULL, NULL, &params, 0, NULL, &conn);
    if (ERROR_SUCCESS != ret)
        return FALSE;
    return TRUE;
}