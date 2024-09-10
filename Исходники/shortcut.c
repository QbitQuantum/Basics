/* register_keys - helper function, which recursively creates the registry keys and values in 
 * parameter 'keys' in the registry under hRootKey. */
static BOOL register_keys(HKEY hRootKey, const struct registry_key *keys, unsigned int numKeys) {
    HKEY hKey;
    unsigned int iKey, iValue;

    for (iKey = 0; iKey < numKeys; iKey++) {
        if (ERROR_SUCCESS == RegCreateKeyExA(hRootKey, keys[iKey].szName, 0, NULL, 0, 
                                             KEY_WRITE, NULL, &hKey, NULL))
        {
            for (iValue = 0; iValue < keys[iKey].cValues; iValue++) {
                const struct registry_value * value = &keys[iKey].pValues[iValue];
                if (ERROR_SUCCESS != RegSetValueExA(hKey, value->szName, 0, value->dwType,
                                                    REG_VALUE_ADDR(value), REG_VALUE_SIZE(value)))
                {
                    RegCloseKey(hKey);
                    return FALSE;
                }
            }
            
            if (!register_keys(hKey, keys[iKey].pSubKeys, keys[iKey].cSubKeys)) {
                RegCloseKey(hKey);
                return FALSE;
            }
            
            RegCloseKey(hKey);
        }
    }
        
    return TRUE;
}