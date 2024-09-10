ListViewAccServer * ListViewAccServer::CreateProvider(HWND hControl, ListViewAccProvider * provider)
{
    ATL::CComPtr<IAccPropServices> pAccPropSvc;
    HRESULT hr = pAccPropSvc.CoCreateInstance(CLSID_AccPropServices, NULL, CLSCTX_SERVER);
    if (hr == S_OK && pAccPropSvc)
    {
        ListViewAccServer * pLVServer = new (std::nothrow) ListViewAccServer(pAccPropSvc);
        if (pLVServer)
        {
            pLVServer->m_pAccProvider = provider;

            MSAAPROPID propid = PROPID_ACC_HELP;
            pAccPropSvc->SetHwndPropServer(hControl, (DWORD)OBJID_CLIENT, CHILDID_SELF, &propid, 1, pLVServer, ANNO_CONTAINER);
            pLVServer->Release();
        }
        return pLVServer;
    }
    return NULL;
}