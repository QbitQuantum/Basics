LanguageManager::LanguageManager()
{
    COMPtr<IMultiLanguage> multiLanguage;
    if (FAILED(::CoCreateInstance(CLSID_CMultiLanguage, 0, CLSCTX_INPROC_SERVER, IID_IMultiLanguage, reinterpret_cast<LPVOID*>(&multiLanguage))))
        return;

    COMPtr<IEnumCodePage> enumInterface;
    if (FAILED(multiLanguage->EnumCodePages(MIMECONTF_BROWSER, &enumInterface)))
        return;

    MIMECPINFO cpInfo;
    ULONG ccpInfo;
    while (SUCCEEDED(enumInterface->Next(1, &cpInfo, &ccpInfo)) && ccpInfo) {
        if (!IsValidCodePage(cpInfo.uiCodePage))
            continue;

        HashMap<UINT, CString>::iterator i = codePageCharsets().find(cpInfo.uiCodePage);

        CString name(String(cpInfo.wszWebCharset).latin1());
        if (i == codePageCharsets().end()) {
            CharsetInfo info;
            info.m_codePage = cpInfo.uiCodePage;
            knownCharsets().set(name.data(), info);
            i = codePageCharsets().set(cpInfo.uiCodePage, name).iterator;
        }
        if (i != codePageCharsets().end()) {
            HashMap<String, CharsetInfo>::iterator j = knownCharsets().find(String(i->value.data(), i->value.length()));
            ASSERT(j != knownCharsets().end());
            CharsetInfo& info = j->value;
            info.m_name = i->value.data();
            info.m_friendlyName = cpInfo.wszDescription;
            info.m_aliases.append(name);
            info.m_aliases.append(String(cpInfo.wszHeaderCharset).latin1());
            info.m_aliases.append(String(cpInfo.wszBodyCharset).latin1());
            String cpName = "cp" + String::number(cpInfo.uiCodePage);
            info.m_aliases.append(cpName.latin1());
            supportedCharsets().add(i->value.data());
        }
    }
}