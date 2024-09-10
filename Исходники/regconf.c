BOOL pmConfig(
    OUT CfgPermittedManagers **permitMgrs,
    OUT INT *permitMgrsLen)
    {
    LONG  status;
    HKEY  hkResult;
    DWORD iValue;
//    DWORD dwTitle;
    DWORD dwType;
    TCHAR dummy[MAX_PATH+1];
    DWORD dummySize;
    TCHAR value[MAX_PATH+1];
    DWORD valueSize;
    LPSTR pTemp;

    *permitMgrs = NULL;
    *permitMgrsLen = 0;

    SNMPDBG((SNMP_LOG_TRACE, "SNMP: INIT: loading permitted managers.\n"));

    if ((status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, pszSnmpSrvPmKey,
                               0, (KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS |
                               KEY_TRAVERSE), &hkResult)) != ERROR_SUCCESS)
        {
        SNMPDBG((SNMP_LOG_ERROR, "SNMP: INIT: error %d opening PermittedManagers subkey.\n", status));
        SnmpSvcReportEvent(SNMP_EVENT_INVALID_REGISTRY_KEY, 1, &pszSnmpSrvPmKey, status);
        return FALSE;
        }

    iValue = 0;

    dummySize = MAX_PATH;
    valueSize = MAX_PATH;

    while((status = RegEnumValue(hkResult, iValue, dummy, &dummySize,
                                 NULL, &dwType, (LPBYTE)value, &valueSize))
          != ERROR_NO_MORE_ITEMS)
        {
        if (status != ERROR_SUCCESS)
            {
            SNMPDBG((SNMP_LOG_ERROR, "SNMP: INIT: error %d enumerating PermittedManagers subkey.\n", status));
            SnmpSvcReportEvent(SNMP_EVENT_INVALID_REGISTRY_KEY, 1, &pszSnmpSrvPmKey, status);
            RegCloseKey(hkResult);
            return FALSE;
            }

        SNMPDBG((SNMP_LOG_TRACE, "SNMP: INIT: processing permitted manager %s\n", value));
        (*permitMgrsLen)++;
        *permitMgrs = (CfgPermittedManagers *)SnmpUtilMemReAlloc(*permitMgrs,
            (*permitMgrsLen * sizeof(CfgPermittedManagers)));

        pTemp = (LPSTR)SnmpUtilMemAlloc(valueSize+1);
        value[valueSize] = TEXT('\0');
#ifdef UNICODE
        SnmpUtilUnicodeToAnsi(&pTemp, value, FALSE);
#else
        memcpy(pTemp, value, valueSize+1);
#endif

        (*permitMgrs)[iValue].addrText = pTemp;
        SnmpSvcAddrToSocket((*permitMgrs)[iValue].addrText,
                     &((*permitMgrs)[iValue].addrEncoding));

        dummySize = MAX_PATH;
        valueSize = MAX_PATH;

        iValue++;
        }

    RegCloseKey(hkResult);

    return TRUE;

    } // end pmConfig()