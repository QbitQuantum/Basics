static int nr_win32_get_adapter_friendly_name(char *adapter_GUID, char **friendly_name)
{
    int r,_status;
    HKEY adapter_reg;
    TCHAR adapter_key[_NR_MAX_KEY_LENGTH];
    TCHAR keyval_buf[_NR_MAX_KEY_LENGTH];
    TCHAR adapter_GUID_tchar[_NR_MAX_NAME_LENGTH];
    DWORD keyval_len, key_type;
    size_t converted_chars, newlen;
    char *my_fn = 0;

#ifdef _UNICODE
    mbstowcs_s(&converted_chars, adapter_GUID_tchar, strlen(adapter_GUID)+1,
               adapter_GUID, _TRUNCATE);
#else
    strlcpy(adapter_GUID_tchar, adapter_GUID, _NR_MAX_NAME_LENGTH);
#endif

    _tcscpy_s(adapter_key, _NR_MAX_KEY_LENGTH, TEXT(_ADAPTERS_BASE_REG));
    _tcscat_s(adapter_key, _NR_MAX_KEY_LENGTH, TEXT("\\"));
    _tcscat_s(adapter_key, _NR_MAX_KEY_LENGTH, adapter_GUID_tchar);
    _tcscat_s(adapter_key, _NR_MAX_KEY_LENGTH, TEXT("\\Connection"));

    r = RegOpenKeyEx(HKEY_LOCAL_MACHINE, adapter_key, 0, KEY_READ, &adapter_reg);

    if (r != ERROR_SUCCESS) {
      r_log(NR_LOG_STUN, LOG_ERR, "Got error %d opening adapter reg key\n", r);
      ABORT(R_INTERNAL);
    }

    keyval_len = sizeof(keyval_buf);
    r = RegQueryValueEx(adapter_reg, TEXT("Name"), NULL, &key_type,
                        (BYTE *)keyval_buf, &keyval_len);

    RegCloseKey(adapter_reg);

#ifdef UNICODE
    newlen = wcslen(keyval_buf)+1;
    my_fn = (char *) RCALLOC(newlen);
    if (!my_fn) {
      ABORT(R_NO_MEMORY);
    }
    wcstombs_s(&converted_chars, my_fn, newlen, keyval_buf, _TRUNCATE);
#else
    my_fn = r_strdup(keyval_buf);
#endif

    *friendly_name = my_fn;
    _status=0;

abort:
    if (_status) {
      if (my_fn) free(my_fn);
    }
    return(_status);
}