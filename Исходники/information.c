/**********************************************************************
 * COMCAT_IsClassOfCategories
 */
static HRESULT COMCAT_IsClassOfCategories(
    HKEY key,
    struct class_categories const* categories)
{
    static const WCHAR impl_keyname[] = { 'I', 'm', 'p', 'l', 'e', 'm', 'e', 'n',
                                          't', 'e', 'd', ' ', 'C', 'a', 't', 'e',
                                          'g', 'o', 'r', 'i', 'e', 's', 0 };
    static const WCHAR req_keyname[]  = { 'R', 'e', 'q', 'u', 'i', 'r', 'e', 'd',
                                          ' ', 'C', 'a', 't', 'e', 'g', 'o', 'r',
                                          'i', 'e', 's', 0 };
    HKEY subkey;
    HRESULT res;
    DWORD index;
    LPCWSTR string;

    /* Check that every given category is implemented by class. */
    res = RegOpenKeyExW(key, impl_keyname, 0, KEY_READ, &subkey);
    if (res != ERROR_SUCCESS) return S_FALSE;
    for (string = categories->impl_strings; *string; string += 39) {
	HKEY catkey;
	res = RegOpenKeyExW(subkey, string, 0, 0, &catkey);
	if (res != ERROR_SUCCESS) {
	    RegCloseKey(subkey);
	    return S_FALSE;
	}
	RegCloseKey(catkey);
    }
    RegCloseKey(subkey);

    /* Check that all categories required by class are given. */
    res = RegOpenKeyExW(key, req_keyname, 0, KEY_READ, &subkey);
    if (res == ERROR_SUCCESS) {
	for (index = 0; ; ++index) {
	    WCHAR keyname[39];
	    DWORD size = 39;

	    res = RegEnumKeyExW(subkey, index, keyname, &size,
				NULL, NULL, NULL, NULL);
	    if (res != ERROR_SUCCESS && res != ERROR_MORE_DATA) break;
	    if (size != 38) continue; /* bogus catid in registry */
	    for (string = categories->req_strings; *string; string += 39)
		if (!strcmpiW(string, keyname)) break;
	    if (!*string) {
		RegCloseKey(subkey);
		return S_FALSE;
	    }
	}
	RegCloseKey(subkey);
    }

    return S_OK;
}