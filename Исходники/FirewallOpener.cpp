bool CFirewallOpener::Init(bool bPreInit)
{
    if (!m_bInited) {
        ASSERT ( m_liAddedRules.IsEmpty() );
        if (thePrefs.GetWindowsVersion() != _WINVER_XP_ || !SUCCEEDED(CoInitialize(NULL)))
            return false;
        HRESULT hr = CoInitializeSecurity (NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
        if (!SUCCEEDED(hr) || !SUCCEEDED(::CoCreateInstance (__uuidof(NetSharingManager), NULL, CLSCTX_ALL, __uuidof(INetSharingManager), (void**)&m_pINetSM)) ) {
            CoUninitialize();
            return false;
        }
    }
    m_bInited = true;
    if (bPreInit) {
        // will return here in order to not create an instance when not really needed
        // preinit is only used to call CoInitializeSecurity before its too late for that (aka something else called it)
        // will have to look deeper into this issue in order to find a nicer way if possible
        return true;
    }

    if (m_pINetSM == NULL) {
        if (!SUCCEEDED(::CoCreateInstance (__uuidof(NetSharingManager), NULL, CLSCTX_ALL, __uuidof(INetSharingManager), (void**)&m_pINetSM)) ) {
            UnInit();
            return false;
        }
    }
    return true;
}