LanguageManager::LanguageManager()
{
    IEnumCodePage* enumInterface;
    IMultiLanguage* mli = FontCache::getMultiLanguageInterface();
    if (mli && S_OK == mli->EnumCodePages(MIMECONTF_BROWSER, &enumInterface)) {
        MIMECPINFO cpInfo;
        ULONG ccpInfo;
        while (S_OK == enumInterface->Next(1, &cpInfo, &ccpInfo) && ccpInfo) {
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
                HashMap<String, CharsetInfo>::iterator j = knownCharsets().find(String(i->second.data(), i->second.length()));
                ASSERT(j != knownCharsets().end());
                CharsetInfo& info = j->second;
                info.m_name = i->second.data();
                info.m_friendlyName = cpInfo.wszDescription;
                info.m_aliases.append(name);
                info.m_aliases.append(String(cpInfo.wszHeaderCharset).latin1());
                info.m_aliases.append(String(cpInfo.wszBodyCharset).latin1());
                String cpName = "cp" + String::number(cpInfo.uiCodePage);
                info.m_aliases.append(cpName.latin1());
                supportedCharsets().add(i->second.data());
            }
        }
        enumInterface->Release();
    }
}