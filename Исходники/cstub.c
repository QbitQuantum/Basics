static void test_NdrDllRegisterProxy( void )
{
    HRESULT res;
    const ExtendedProxyFileInfo *pf;
    HMODULE hmod = GetModuleHandleA(NULL);


    res = NdrDllRegisterProxy(NULL, NULL, NULL);
    ok(res == E_HANDLE, "Incorrect return code %x\n",res);
    pf = NULL;
    res = NdrDllRegisterProxy(hmod, &pf, NULL);
    ok(res == E_NOINTERFACE, "Incorrect return code %x\n",res);
    res = NdrDllRegisterProxy(hmod, proxy_file_list2, NULL);
    ok(res == E_NOINTERFACE, "Incorrect return code %x\n",res);
    /* This fails on Vista and Windows 7 due to permissions */
    res = NdrDllRegisterProxy(hmod, proxy_file_list, NULL);
    ok(res == S_OK || res == E_ACCESSDENIED, "NdrDllRegisterProxy failed %x\n",res);
    if (res == S_OK)
    {
        res = NdrDllUnregisterProxy(hmod,proxy_file_list, NULL);
        ok(res == S_OK, "NdrDllUnregisterProxy failed %x\n",res);
    }
}