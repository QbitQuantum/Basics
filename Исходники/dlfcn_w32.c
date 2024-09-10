static void set_error(const char * e)
{
    char * s;
    char * old_s;
    size_t len;

    DWORD slot = get_tl_error_slot();

    if (slot == TLS_OUT_OF_INDEXES)
        return;

    len = strlen(e) * sizeof(char) + sizeof(char);
    s = LocalAlloc(LMEM_FIXED, len);
    if (s == NULL)
        return;

    old_s = (char *) TlsGetValue(slot);
    TlsSetValue(slot, (LPVOID) s);

    if (old_s != NULL)
        LocalFree(old_s);
}