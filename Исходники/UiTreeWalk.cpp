HRESULT UiTreeWalk::AppendUiAttributes(long left, long top, IUIAutomationElement* pCurUia, long nPos, std::wstring& wstr)
{
    SAFEARRAY *rid;
    REQUIRE_SUCCESS_HR(pCurUia->GetRuntimeId(&rid));
    LONG lbound;
    REQUIRE_SUCCESS_HR(SafeArrayGetLBound(rid, 1, &lbound));
    LONG ubound;
    REQUIRE_SUCCESS_HR(SafeArrayGetUBound(rid, 1, &ubound));

    CComBSTR bstrRuntimeId;
    LONG runtimeId = 0;
    WCHAR temp[16];
    for (LONG i = lbound; i <= ubound; i++)
    {
        REQUIRE_SUCCESS_HR(SafeArrayGetElement(rid, &i, &runtimeId));
        _ltow_s(runtimeId, temp, 10);
        REQUIRE_SUCCESS_HR(bstrRuntimeId.Append(temp));
        
        if (i < ubound)
        {
            REQUIRE_SUCCESS_HR(bstrRuntimeId.Append(L"."));
        }
    }

    REQUIRE_SUCCESS_HR(SafeArrayDestroy(rid));

    if (bstrRuntimeId == NULL)
    {
        wsprintf(temp, L"%lu", reinterpret_cast<std::uintptr_t>(pCurUia));
        bstrRuntimeId = temp;
    }

    CComPtr<IUIAutomationElement> spUia(pCurUia);
    auto it = cachedAutoElements.find(bstrRuntimeId);
    if (it == cachedAutoElements.end())
    {
        cachedAutoElements.insert(std::make_pair(bstrRuntimeId, spUia));
    }
    else
    {
        it->second = spUia;
    }

    CComBSTR bstrClass;
    REQUIRE_SUCCESS_HR(pCurUia->get_CurrentClassName(&bstrClass));
    bstrClass = bstrClass == NULL ? L"" : bstrClass;
    std::wstring shortClass(bstrClass, SysStringLen(bstrClass));
    bool bStartWith = XmlEncode(shortClass, MaxNameLength);
    if (bStartWith == true || shortClass.length() >= MaxNameLength)
    {
        shortClass.insert(0, L"starts-with:");
    }

    CComBSTR bstrName;
    REQUIRE_SUCCESS_HR(pCurUia->get_CurrentName(&bstrName));
    bstrName = bstrName == NULL ? L"" : bstrName;

    std::wstring shortName(bstrName, SysStringLen(bstrName));
    bStartWith = XmlEncode(shortName, MaxNameLength);

    if (bStartWith == true || shortName.length() >= MaxNameLength)
    {
        shortName.insert(0, L"starts-with:");
    }

    CComBSTR bstrCtrlType;
    REQUIRE_SUCCESS_HR(pCurUia->get_CurrentLocalizedControlType(&bstrCtrlType));
    bstrCtrlType = bstrCtrlType == NULL ? L"" : bstrCtrlType;

    CONTROLTYPEID cid;
    REQUIRE_SUCCESS_HR(pCurUia->get_CurrentControlType(&cid));

    CComBSTR bstrProgrammaticName;
    if (cid >= UIA_ButtonControlTypeId && UIA_ButtonControlTypeId <= UIA_AppBarControlTypeId)
    {
        REQUIRE_SUCCESS_HR(bstrProgrammaticName.Append(gc_controlTypesTable[cid - UIA_ButtonControlTypeId].pszName));
    }

    // CurrentLocalizedControlType can be empty: Cortana set reminder Time button's parent
    if (bstrProgrammaticName.Length() == 0)
    {
        bstrProgrammaticName = L"Unknown";
    }

    CComBSTR bstrAutoId;
    REQUIRE_SUCCESS_HR(pCurUia->get_CurrentAutomationId(&bstrAutoId));
    bstrAutoId = bstrAutoId == NULL ? L"" : bstrAutoId;

    std::wstring shortAutoId(bstrAutoId, SysStringLen(bstrAutoId));
    bStartWith = XmlEncode(shortAutoId, MaxNameLength);

    if (bStartWith == true || shortAutoId.length() >= MaxNameLength)
    {
        shortAutoId.insert(0, L"starts-with:");
    }

    RECT rect;
    REQUIRE_SUCCESS_HR(pCurUia->get_CurrentBoundingRectangle(&rect));

    WCHAR chPos[16];
    if (nPos <= 0)
    {
        wsprintf(chPos, L"");
    }
    else
    {
        wsprintf(chPos, L"%d", nPos + 1); // xpath index starts at 1
    } 

    wsprintf(UiTreeWalk::s_chBuffer,
        c_chNodeFormat,
        bstrProgrammaticName.m_str,
        bstrCtrlType.m_str,
        shortClass.c_str(),
        shortName.c_str(),
        shortAutoId.c_str(),
        rect.left,
        rect.top,
        rect.right - rect.left,
        rect.bottom - rect.top,
        left - rect.left,
        top - rect.top,
        chPos,
        bstrRuntimeId.m_str);

    if (wcslen(UiTreeWalk::s_chBuffer) > 0)
    {
        wstr.append(UiTreeWalk::s_chBuffer);
    }

    return S_OK;
}