// ## Internet Explorer ##
bool Nicookie::findInternetExplorer()
{
    WCHAR cookie_data[256];
    DWORD cookie_data_size = 256;
    BOOL result = false;
#ifdef _MSC_VER
    // 保護モードでの取得。VisualStudioでのみ有効。
    // 32bitは32bitだけ、64bitは64bitだけしか取得できない。
    HRESULT hr;
    hr = IEGetProtectedModeCookie(Nicookie::COOKIE_URL.toStdWString().c_str(),
                                  Nicookie::COOKIE_NAME.toStdWString().c_str(),
                                  cookie_data,
                                  &cookie_data_size,
                                  0);
    result = (hr == S_OK);
#endif // _MSC_VER
    if (!result) {
        result = InternetGetCookieW(Nicookie::COOKIE_URL.toStdWString().c_str(),
                                    Nicookie::COOKIE_NAME.toStdWString().c_str(),
                                    cookie_data,
                                    &cookie_data_size);
    }
    if (result) {
        this->userSession = QString::fromStdWString(std::wstring(cookie_data));
        return true;
    } else {
        setError(Nicookie::NotFoundDataError);
        return false;
    }
}