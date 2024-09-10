STDMETHODIMP DDTaskManager::SetLocale(/* in */ LCID lcid) {
    if (!SetThreadLocale(lcid)) {
        _ASSERTE(!"Couldn't set thread-locale");
        return HRESULT_FROM_WIN32(GetLastError());
    }

    return S_OK;
}