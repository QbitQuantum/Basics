int main(int argc, char *argv[])
{
    DWORD dwError;
    HANDLE hReg = NULL;
    PLWREG_VALUE_ATTRIBUTES pAttr = NULL;
    PLWREG_VALUE_ATTRIBUTES pAttr_int = NULL;
    PWSTR* ppwszRootKeyNames = NULL;
    DWORD dwNumRootKeys = 0;
    wchar16_t szSubKey[] = {'a', 0};
    wchar16_t szSubKey1[] = {'b', 0};
    wchar16_t szValueName[] = {'a','t','t','r',0};
    wchar16_t szValueName1[] = {'a','t','t','r','1',0};
    HKEY hKey = NULL;
    HKEY hSubKey = NULL;
    HKEY hSubSubKey = NULL;

    PLWREG_CURRENT_VALUEINFO pCurrentValue = NULL;
    PLWREG_VALUE_ATTRIBUTES pValueAttributes = NULL;
    PLWREG_VALUE_ATTRIBUTES pValueAttributes_int = NULL;

    ValueAttribute.Range.ppszRangeEnumStrings = ppszRangeEnumStrings;
    ValueAttribute_int.Range.RangeInteger.Max = 100;
    ValueAttribute_int.Range.RangeInteger.Min = 1;

    DWORD dwType = REG_NONE;
    PBYTE pData[MAX_VALUE_LENGTH] = {0};
    DWORD cbData = MAX_VALUE_LENGTH;

    wchar16_t pCurrData[] = {'C', 'u', 'r', 'r', 'e', 'n', 't', 0};


    dwError = RegConvertValueAttributesAToW(ValueAttribute,
                                            &pAttr);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegConvertValueAttributesAToW(ValueAttribute_int,
                                            &pAttr_int);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegOpenServer(&hReg);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegEnumRootKeysW(hReg,
                               &ppwszRootKeyNames,
                               &dwNumRootKeys);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegOpenKeyExW(
                hReg,
                NULL,
                ppwszRootKeyNames[0],
                0,
                KEY_ALL_ACCESS | KEY_SET_VALUE | KEY_CREATE_SUB_KEY | DELETE,
                &hKey);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegCreateKeyExW(
                hReg,
                hKey,
                szSubKey,
                0,
                NULL,
                0,
                KEY_ALL_ACCESS,
                NULL,
                &hSubKey,
                NULL);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegCreateKeyExW(
                hReg,
                hSubKey,
                szSubKey1,
                0,
                NULL,
                0,
                KEY_ALL_ACCESS,
                NULL,
                &hSubSubKey,
                NULL);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegSetValueAttributesW(
                   hReg,
                   hKey,
                   NULL,
                   szValueName,
                   pAttr);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegSetValueAttributesW(
                   hReg,
                   hKey,
                   NULL,
                   szValueName1,
                   pAttr_int);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegSetValueAttributesW(
                   hReg,
                   hKey,
                   szSubKey,
                   szValueName,
                   pAttr);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegSetValueAttributesW(
                   hReg,
                   hKey,
                   szSubKey,
                   szValueName1,
                   pAttr);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegSetValueAttributesW(
                   hReg,
                   hSubSubKey,
                   NULL,
                   szValueName1,
                   pAttr_int);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegSetValueAttributesW(
                   hReg,
                   hSubSubKey,
                   NULL,
                   szValueName,
                   pAttr);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegGetValueAttributesW(
                   hReg,
                   hKey,
                   NULL,
                   szValueName,
                   &pCurrentValue,
                   &pValueAttributes);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegGetValueAttributesW(
                   hReg,
                   hKey,
                   NULL,
                   szValueName1,
                   NULL,
                   &pValueAttributes_int);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegSetValueExW(
                  hReg,
                  hSubKey,
                  szValueName,
                  0,
                  REG_SZ,
                  (const BYTE*)pCurrData,
                  (wc16slen(pCurrData)+1)*sizeof(*pCurrData));
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegGetValueW(
                   hReg,
                   hKey,
                   szSubKey,
                   szValueName,
                   RRF_RT_REG_NONE,
                   &dwType,
                   pData,
                   &cbData);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegDeleteValueAttributesW(
                   hReg,
                   hKey,
                   NULL,
                   szValueName);
    BAIL_ON_REG_ERROR(dwError);

    dwError = RegDeleteTreeW(
                   hReg,
                   hKey,
                   szSubKey);
    if (LWREG_ERROR_KEY_IS_ACTIVE == dwError)
    {
        if (hSubKey)
        {
            RegCloseKey(hReg, hSubKey);
        }
        if (hSubSubKey)
        {
            RegCloseKey(hReg, hSubSubKey);
        }
        dwError = RegDeleteTreeW(
                hReg,
                hKey,
                szSubKey);
        BAIL_ON_REG_ERROR(dwError);
    }
    BAIL_ON_REG_ERROR(dwError);

cleanup:

    if (hKey)
    {
        RegCloseKey(hReg, hKey);
    }
    if (hSubKey)
    {
        RegCloseKey(hReg, hSubKey);
    }
    if (hSubSubKey)
    {
        RegCloseKey(hReg, hSubSubKey);
    }


    if (hReg)
    {
        RegCloseServer(hReg);
    }

    RegFreeWC16StringArray(ppwszRootKeyNames,
                           dwNumRootKeys);

    RegSafeFreeValueAttributes(&pAttr);
    RegSafeFreeCurrentValueInfo(&pCurrentValue);
    RegSafeFreeValueAttributes(&pValueAttributes);


    return dwError;

error:

    goto cleanup;
}