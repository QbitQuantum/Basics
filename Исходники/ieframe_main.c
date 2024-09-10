HRESULT register_class_object(BOOL do_reg)
{
    HRESULT hres;

    static DWORD cookie;

    if(do_reg) {
        hres = CoRegisterClassObject(&CLSID_InternetExplorer,
                (IUnknown*)&InternetExplorerFactory, CLSCTX_SERVER,
                REGCLS_MULTIPLEUSE|REGCLS_SUSPENDED, &cookie);
        if (FAILED(hres)) {
            ERR("failed to register object %08x\n", hres);
            return hres;
        }

        hres = CoResumeClassObjects();
        if(SUCCEEDED(hres))
            return hres;

        ERR("failed to resume object %08x\n", hres);
    }

    return CoRevokeClassObject(cookie);
}