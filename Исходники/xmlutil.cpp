UINT CXmlUtil::GetFieldInt(const XMLDOMElementPtr& ele,
                           const wchar_t* filename,
                           INT defValue)
{
    UINT nRet = defValue;
    std::wstring str = GetField(ele, filename);

    if (_wcsicmp(str.c_str(), L"true") == 0)
        return 1;
    if (_wcsicmp(str.c_str(), L"false") == 0)
        return 0;

    if (!str.empty())
    {
        wchar_t* endptr;
        if (_wcsnicmp(str.c_str(), L"0x", 2) == 0)
            nRet = wcstol(str.c_str(), &endptr, 16);
        else
            nRet = _wtoi(str.c_str());
    }

    return nRet;
}