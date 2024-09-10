HICON	CFaviconManager::GetFaviconFromURL(LPCTSTR url)
{
    CString strFaviconURL;
    CString strHtmlPath;
    if (SUCCEEDED(::URLDownloadToCacheFile(NULL, url, strHtmlPath.GetBuffer(MAX_PATH), MAX_PATH, 0, NULL))) {
        strHtmlPath.ReleaseBuffer();
        CAtlFile	file;
        if (SUCCEEDED(file.Create(strHtmlPath, GENERIC_READ, 0, OPEN_EXISTING))) {
            enum { kMaxReadSize = 2000 };
            unique_ptr<char[]>	htmlContent(new char[kMaxReadSize + 1]);
            DWORD	dwReadSize = 0;
            file.Read((LPVOID)htmlContent.get(), kMaxReadSize, dwReadSize);
            htmlContent[dwReadSize] = '\0';

            boost::regex	rx("<link (?:(?<rel>rel=[\"']?(?:shortcut icon|icon)[\"']?) (?<href>href=[\"']?(?<url>[^ \"]+)[\"']?)|(?<href>href=[\"']?(?<url>[^ \"]+)[\"']?) (?<rel>rel=[\"']?(?:shortcut icon|icon)[\"']?))[^>]+>", boost::regex::icase);
            boost::cmatch	result;
            if (boost::regex_search(htmlContent.get(), result, rx)) {
                CString strhref = result["url"].str().c_str();
                DWORD	dwSize = INTERNET_MAX_URL_LENGTH;
                ::UrlCombine(url, strhref, strFaviconURL.GetBuffer(INTERNET_MAX_URL_LENGTH), &dwSize, 0);
                strFaviconURL.ReleaseBuffer();
            }
        }
    }
    if (strFaviconURL.IsEmpty()) {	// ルートにあるFaviconのアドレスを得る
        DWORD cchResult = INTERNET_MAX_URL_LENGTH;
        if (::CoInternetParseUrl(url, PARSE_ROOTDOCUMENT, 0, strFaviconURL.GetBuffer(INTERNET_MAX_URL_LENGTH), INTERNET_MAX_URL_LENGTH, &cchResult, 0) == S_OK) {
            strFaviconURL.ReleaseBuffer();
            strFaviconURL += _T("/favicon.ico");
        }
    }

    if (strFaviconURL.GetLength() > 0) {
        CCritSecLock	lock(s_cs);
        CIconHandle hIcon = GetFavicon(strFaviconURL);
        if (hIcon == NULL) {
            hIcon = _DownloadFavicon(strFaviconURL);
            if (hIcon) {
                s_mapIcon[std::wstring(strFaviconURL)] = hIcon;
                hIcon	= hIcon.DuplicateIcon();
            }
        } else {
            hIcon = hIcon.DuplicateIcon();
        }
        return hIcon;
    }
    return NULL;
}