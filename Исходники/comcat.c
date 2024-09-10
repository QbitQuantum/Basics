/**********************************************************************
 * COMCAT_ICatRegister_RegisterCategories
 */
static HRESULT WINAPI COMCAT_ICatRegister_RegisterCategories(
    LPCATREGISTER iface,
    ULONG cCategories,
    CATEGORYINFO *rgci)
{
    HKEY comcat_key;
    HRESULT res;

    TRACE("\n");

    if (cCategories && rgci == NULL)
	return E_POINTER;

    /* Create (or open) the component categories key. */
    res = RegCreateKeyExW(HKEY_CLASSES_ROOT, comcat_keyname, 0, NULL, 0,
			  KEY_READ | KEY_WRITE, NULL, &comcat_key, NULL);
    if (res != ERROR_SUCCESS) return E_FAIL;

    for (; cCategories; --cCategories, ++rgci) {
	static const WCHAR fmt[] = { '%', 'l', 'X', 0 };
	WCHAR keyname[39];
	WCHAR valname[9];
	HKEY cat_key;

	/* Create (or open) the key for this category. */
	if (!StringFromGUID2(&rgci->catid, keyname, 39)) continue;
	res = RegCreateKeyExW(comcat_key, keyname, 0, NULL, 0,
			      KEY_READ | KEY_WRITE, NULL, &cat_key, NULL);
	if (res != ERROR_SUCCESS) continue;

	/* Set the value for this locale's description. */
	wsprintfW(valname, fmt, rgci->lcid);
	RegSetValueExW(cat_key, valname, 0, REG_SZ,
		       (CONST BYTE*)(rgci->szDescription),
		       (lstrlenW(rgci->szDescription) + 1) * sizeof(WCHAR));

	RegCloseKey(cat_key);
    }

    RegCloseKey(comcat_key);
    return S_OK;
}