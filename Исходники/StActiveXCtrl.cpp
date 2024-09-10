StString StActiveXCtrl::loadURL(const CString& theUrl) {
    if(theUrl.IsEmpty()) {
        // invalid URL
        return StString();
    }

    // obtaining the full url
    CComBSTR aURLTemp(theUrl);
    CW2CT aFullUrl(aURLTemp);

    // load file and return path to cache
    IBindHost* aHost = NULL;
    wchar_t aFilePath[ST_MAX_PATH];
    this->GetClientSite()->QueryInterface(IID_IBindHost, (void** )&aHost);
    if(URLDownloadToCacheFileW(aHost, aFullUrl, aFilePath, ST_MAX_PATH, 0, NULL) == S_OK) {
        return StString(aFilePath);
    }

    return StString();
}