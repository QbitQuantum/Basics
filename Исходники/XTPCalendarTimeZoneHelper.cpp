BOOL CXTPCalendarTimeZones::InitFromRegistry()
{
    m_arTZInfo.RemoveAll();

    CString strTZIRootKey = XTP_CALENDAR_TIMEZONESKEY_NT;

    HKEY hkTZIRoot = NULL;
    BOOL bUseIndex = !XTPSystemVersion()->IsWinXPOrGreater();

    // Try NT information first
    LONG lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, strTZIRootKey, 0, KEY_READ, &hkTZIRoot);
    if (lRes != ERROR_SUCCESS)
    {
        // try Win9x information
        strTZIRootKey = XTP_CALENDAR_TIMEZONESKEY_9X;
        bUseIndex = FALSE;

        lRes = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, strTZIRootKey, 0, KEY_READ, &hkTZIRoot);
        if (lRes != ERROR_SUCCESS)
        {
            TRACE(_T("Cannot open Time Zones information registry key. err = %d \n"), lRes);
            return FALSE;
        }
    }

    const DWORD cdwKeyBufSize = 1024;
    TCHAR szTZIKey[cdwKeyBufSize + 1];

    BSTR bstrStandardName = NULL;
    BSTR bstrDaylightName = NULL;

    lRes = ERROR_SUCCESS;
    for (DWORD dwEnumKey = 0; lRes == ERROR_SUCCESS; dwEnumKey++)
    {
        ::ZeroMemory(szTZIKey, sizeof(szTZIKey));

        lRes = ::RegEnumKey (hkTZIRoot, dwEnumKey, szTZIKey, cdwKeyBufSize);

        if (lRes != ERROR_SUCCESS)
        {
            ASSERT(lRes == ERROR_NO_MORE_ITEMS);
            break;
        }

        //===================================================================
        CString strTZIKey = strTZIRootKey + _T("\\") + szTZIKey;

        HKEY hkTZIdata = NULL;
        LONG lRes2 = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, strTZIKey, 0, KEY_READ, &hkTZIdata);
        if (lRes2 != ERROR_SUCCESS)
        {
            TRACE(_T("Cannot open registry key 'HKEY_LOCAL_MACHINE\\%s'. err = %d \n"), (LPCTSTR)strTZIKey, lRes2);
            continue;
        }

        CString strDisplayStr, strStandardName, strDaylightName;
        DWORD dwIndex;
        REGISTRY_TIMEZONE_INFORMATION regTZI;

        if (!GetRegStr(hkTZIdata, XTP_CALENDAR_TZIRegValName_DisplayStr, strDisplayStr))
        {
            TRACE(_T("Cannot get value from registry: 'HKEY_LOCAL_MACHINE\\%s\\%s'\n"), (LPCTSTR)strTZIKey, XTP_CALENDAR_TZIRegValName_DisplayStr);
            continue;
        }
        if (!GetRegBSTR(hkTZIdata, XTP_CALENDAR_TZIRegValName_StandardNameW, bstrStandardName))
        {
            TRACE(_T("Cannot get value from registry: 'HKEY_LOCAL_MACHINE\\%s\\%s'\n"), (LPCTSTR)strTZIKey, XTP_CALENDAR_TZIRegValName_StandardName);
            continue;
        }
        if (!GetRegBSTR(hkTZIdata, XTP_CALENDAR_TZIRegValName_DaylightNameW, bstrDaylightName))
        {
            TRACE(_T("Cannot get value from registry: 'HKEY_LOCAL_MACHINE\\%s\\%s'\n"), (LPCTSTR)strTZIKey, XTP_CALENDAR_TZIRegValName_DaylightName);
            continue;
        }

        if (!GetRegTZI(hkTZIdata, XTP_CALENDAR_TZIRegValName_DATA, regTZI))
        {
            TRACE(_T("Cannot get value from registry: 'HKEY_LOCAL_MACHINE\\%s\\%s'\n"), (LPCTSTR)strTZIKey, XTP_CALENDAR_TZIRegValName_DATA);
            continue;
        }

        if (!GetRegDWORD(hkTZIdata, XTP_CALENDAR_TZIRegValName_Index, dwIndex))
        {
            if (bUseIndex)
            {
                TRACE(_T("Cannot get value from registry: 'HKEY_LOCAL_MACHINE\\%s\\%s'\n"), (LPCTSTR)strTZIKey, XTP_CALENDAR_TZIRegValName_Index);
            }
            dwIndex = 0;
        }

        //=================================================
        CXTPCalendarTimeZone* pXTP_TZI;
        pXTP_TZI = new CXTPCalendarTimeZone();
        if (!pXTP_TZI)
        {
            AfxThrowOleException(E_OUTOFMEMORY);
        }

        pXTP_TZI->Bias = regTZI.Bias;

        WCSNCPY_S(pXTP_TZI->StandardName, 32, bstrStandardName, 32);
        pXTP_TZI->StandardName[_countof(pXTP_TZI->StandardName)-1] = L'\0';

        pXTP_TZI->StandardDate = regTZI.StandardDate;
        pXTP_TZI->StandardBias = regTZI.StandardBias;

        WCSNCPY_S(pXTP_TZI->DaylightName, 32, bstrDaylightName, 32);
        pXTP_TZI->DaylightName[_countof(pXTP_TZI->DaylightName)-1] = L'\0';

        pXTP_TZI->DaylightDate = regTZI.DaylightDate;
        pXTP_TZI->DaylightBias = regTZI.DaylightBias;

        pXTP_TZI->m_strDisplayString = strDisplayStr;
        pXTP_TZI->m_dwIndex = dwIndex;

        m_arTZInfo.Add(pXTP_TZI, FALSE);

        RegCloseKey(hkTZIdata);
    }

    RegCloseKey(hkTZIRoot);

    //-----------------------------------------------
    if (bstrStandardName)
    {
        ::SysFreeString(bstrStandardName);
    }
    if (bstrDaylightName)
    {
        ::SysFreeString(bstrDaylightName);
    }

    //-----------------------------------------------
    int nCount = m_arTZInfo.GetCount();
    for (int i = 0; i < nCount; i++)
    {
        for (int j = i + 1; j < nCount; j++)
        {
            CXTPCalendarTimeZonePtr ptrElem1, ptrElem2;
            ptrElem1 = m_arTZInfo.GetAt(i, TRUE);
            ptrElem2 = m_arTZInfo.GetAt(j, TRUE);

            if (CompareTZI(ptrElem1, ptrElem2, bUseIndex) > 0)
            {
                m_arTZInfo.SetAt(i, ptrElem2.Detach());
                m_arTZInfo.SetAt(j, ptrElem1.Detach());
            }
        }
    }

    return TRUE;
}