/*
 * Allocate (duplicate) a wide char string.
 */
PWSTR MEMHEAP::AllocStr(PCWSTR str)
{
    if (str == NULL)
        return NULL;

    size_t str_len = wcslen(str) + 1;
    PWSTR strNew = (PWSTR) Alloc(str_len * sizeof(WCHAR));
    HRESULT hr;
    hr = StringCchCopyW(strNew, str_len, str);
    ASSERT (SUCCEEDED (hr));
    return strNew;
}