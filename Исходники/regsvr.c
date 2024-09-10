/***********************************************************************
 *		unregister_coclasses
 */
static HRESULT unregister_coclasses(struct regsvr_coclass const *list)
{
    LONG res = ERROR_SUCCESS;
    HKEY coclass_key;

    res = RegOpenKeyExW(HKEY_CLASSES_ROOT, clsid_keyname, 0,
			KEY_READ | KEY_WRITE, &coclass_key);
    if (res == ERROR_FILE_NOT_FOUND) return S_OK;
    if (res != ERROR_SUCCESS) goto error_return;

    for (; res == ERROR_SUCCESS && list->clsid; ++list) {
	WCHAR buf[39];

	StringFromGUID2(list->clsid, buf, 39);
	res = SHDeleteKeyW(coclass_key, buf);
	if (res == ERROR_FILE_NOT_FOUND) res = ERROR_SUCCESS;
	if (res != ERROR_SUCCESS) goto error_close_coclass_key;

	if (list->progid) {
	    res = SHDeleteKeyA(HKEY_CLASSES_ROOT, list->progid);
	    if (res == ERROR_FILE_NOT_FOUND) res = ERROR_SUCCESS;
	    if (res != ERROR_SUCCESS) goto error_close_coclass_key;
	}

	if (list->viprogid) {
	    res = SHDeleteKeyA(HKEY_CLASSES_ROOT, list->viprogid);
	    if (res == ERROR_FILE_NOT_FOUND) res = ERROR_SUCCESS;
	    if (res != ERROR_SUCCESS) goto error_close_coclass_key;
	}
    }

error_close_coclass_key:
    RegCloseKey(coclass_key);
error_return:
    return res != ERROR_SUCCESS ? HRESULT_FROM_WIN32(res) : S_OK;
}