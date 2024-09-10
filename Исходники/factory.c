/***********************************************************************
 *          DllRegisterServer (shdocvw.@)
 */
HRESULT WINAPI DllRegisterServer(void)
{
    ITypeLib *typelib;
    HRESULT hres;

    static const WCHAR shdocvwW[] = {'s','h','d','o','c','v','w','.','d','l','l',0};

    hres = register_server(TRUE);
    if(FAILED(hres))
        return hres;

    hres = LoadTypeLibEx(shdocvwW, REGKIND_REGISTER, &typelib);
    if(FAILED(hres)) {
        ERR("Could not load typelib: %08x\n", hres);
        return hres;
    }

    ITypeLib_Release(typelib);

    return hres;
}