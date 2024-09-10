/*--------------------------------------------------------------------------*/
wchar_t *createGUID(void)
{
    GUID guid;
    wchar_t* pwstrGUID = NULL;
    wchar_t* ret = NULL;

    CoCreateGuid (&guid);
    StringFromCLSID(&guid, &pwstrGUID);

    //remove first '{' and last '}'
    pwstrGUID[wcslen(pwstrGUID) - 1] = L'\0';
    ret = os_wcsdup(pwstrGUID + 1);
    CoTaskMemFree(pwstrGUID);
    return ret;
}