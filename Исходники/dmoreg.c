/***************************************************************
 * DMORegister (MSDMO.@)
 *
 * Register a DirectX Media Object.
 */
HRESULT WINAPI DMORegister(
   LPCWSTR szName,
   REFCLSID clsidDMO,
   REFGUID guidCategory,
   DWORD dwFlags,
   DWORD cInTypes,
   const DMO_PARTIAL_MEDIATYPE *pInTypes,
   DWORD cOutTypes,
   const DMO_PARTIAL_MEDIATYPE *pOutTypes
)
{
    WCHAR szguid[64];
    HRESULT hres;
    HKEY hrkey = 0;
    HKEY hkey = 0;
    HKEY hckey = 0;
    HKEY hclskey = 0;
    LONG ret;

    TRACE("%s %s %s\n", debugstr_w(szName), debugstr_guid(clsidDMO), debugstr_guid(guidCategory));

    if (IsEqualGUID(guidCategory, &GUID_NULL))
        return E_INVALIDARG;

    ret = RegCreateKeyExW(HKEY_CLASSES_ROOT, szDMORootKey, 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hrkey, NULL);
    if (ret)
        return HRESULT_FROM_WIN32(ret);

    /* Create clsidDMO key under MediaObjects */ 
    ret = RegCreateKeyExW(hrkey, GUIDToString(szguid, clsidDMO), 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hkey, NULL);
    if (ret)
        goto lend;

    /* Set default Name value */
    ret = RegSetValueExW(hkey, NULL, 0, REG_SZ, (const BYTE*) szName,
        (strlenW(szName) + 1) * sizeof(WCHAR));

    /* Set InputTypes */
    hres = write_types(hkey, szDMOInputType, pInTypes, cInTypes);

    /* Set OutputTypes */
    hres = write_types(hkey, szDMOOutputType, pOutTypes, cOutTypes);

    if (dwFlags & DMO_REGISTERF_IS_KEYED)
    {
        /* Create Keyed key */ 
        ret = RegCreateKeyExW(hkey, szDMOKeyed, 0, NULL,
            REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hckey, NULL);
        if (ret)
            goto lend;
        RegCloseKey(hckey);
    }

    /* Register the category */
    ret = RegCreateKeyExW(hrkey, szDMOCategories, 0, NULL,
            REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hckey, NULL);
    if (ret)
        goto lend;

    RegCloseKey(hkey);

    ret = RegCreateKeyExW(hckey, GUIDToString(szguid, guidCategory), 0, NULL,
            REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hkey, NULL);
    if (ret)
        goto lend;
    ret = RegCreateKeyExW(hkey, GUIDToString(szguid, clsidDMO), 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hclskey, NULL);
    if (ret)
        goto lend;

lend:
    if (hkey)
        RegCloseKey(hkey);
    if (hckey)
        RegCloseKey(hckey);
    if (hclskey)
        RegCloseKey(hclskey);
    if (hrkey)
        RegCloseKey(hrkey);

    hres = HRESULT_FROM_WIN32(ret);
    TRACE(" hresult=0x%08x\n", hres);
    return hres;
}