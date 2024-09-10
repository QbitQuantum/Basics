static void set_buffer(LPWSTR *buffer, LPCWSTR string)
{
    static const WCHAR empty_string[] = {0};
    ULONG len;

    if (string == NULL)
        string = empty_string;
    len = (wcslen(string) + 1)*sizeof(WCHAR);

    LPWSTR tmp = (LPWSTR) heap_realloc(*buffer, len);
    if (tmp)
        *buffer = tmp;
    else
        len = wcslen(*buffer) + 1;

    StringCchCopyW(*buffer, len, string);
}