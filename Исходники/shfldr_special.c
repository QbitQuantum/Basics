static void test_printers_folder(void)
{
    IShellFolder2 *folder;
    IPersistFolder2 *pf;
    SHELLDETAILS details;
    SHCOLSTATEF state;
    LPITEMIDLIST pidl1, pidl2;
    HRESULT hr;
    INT i;

    CoInitialize( NULL );

    hr = CoCreateInstance(&CLSID_Printers, NULL, CLSCTX_INPROC_SERVER, &IID_IShellFolder2, (void**)&folder);
    if (hr != S_OK)
    {
        win_skip("Failed to created IShellFolder2 for Printers folder\n");
        CoUninitialize();
        return;
    }

if (0)
{
    /* crashes on XP */
    hr = IShellFolder2_GetDetailsOf(folder, NULL, 0, NULL);
    hr = IShellFolder2_GetDefaultColumnState(folder, 0, NULL);
    hr = IPersistFolder2_GetCurFolder(pf, NULL);
}

    /* 5 columns defined */
    hr = IShellFolder2_GetDetailsOf(folder, NULL, 6, &details);
    ok(hr == E_NOTIMPL, "got 0x%08x\n", hr);

    hr = IShellFolder2_GetDefaultColumnState(folder, 6, &state);
    ok(broken(hr == E_NOTIMPL) || hr == E_INVALIDARG /* Win7 */, "got 0x%08x\n", hr);

    hr = IShellFolder2_GetDetailsOf(folder, NULL, 0, &details);
    ok(hr == S_OK || broken(E_NOTIMPL) /* W2K */, "got 0x%08x\n", hr);
    /* test every column if method is implemented */
    if (hr == S_OK)
    {
        ok(details.str.uType == STRRET_WSTR, "got %d\n", details.str.uType);

        for(i = 0; i < 6; i++)
        {
            hr = IShellFolder2_GetDetailsOf(folder, NULL, i, &details);
            ok(hr == S_OK, "got 0x%08x\n", hr);

            /* all columns are left-aligned */
            ok(details.fmt == LVCFMT_LEFT, "got 0x%x\n", details.fmt);
            /* can't be on w9x at this point, IShellFolder2 unsupported there,
               check present for running Wine with w9x setup */
            if (SHELL_OsIsUnicode()) SHFree(details.str.u.pOleStr);

            hr = IShellFolder2_GetDefaultColumnState(folder, i, &state);
            ok(hr == S_OK, "got 0x%08x\n", hr);
            /* all columns are string except document count */
            if (i == 1)
                ok(state == (SHCOLSTATE_TYPE_INT | SHCOLSTATE_ONBYDEFAULT), "got 0x%x\n", state);
            else
                ok(state == (SHCOLSTATE_TYPE_STR | SHCOLSTATE_ONBYDEFAULT), "got 0x%x\n", state);
        }
    }

    /* default pidl */
    hr = IShellFolder2_QueryInterface(folder, &IID_IPersistFolder2, (void**)&pf);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    /* not initialized */
    pidl1 = (void*)0xdeadbeef;
    hr = IPersistFolder2_GetCurFolder(pf, &pidl1);
    ok(hr == S_FALSE, "got 0x%08x\n", hr);
    ok(pidl1 == NULL, "got %p\n", pidl1);

    hr = SHGetSpecialFolderLocation(NULL, CSIDL_PRINTERS, &pidl2);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IPersistFolder2_Initialize(pf, pidl2);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IPersistFolder2_GetCurFolder(pf, &pidl1);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ok(ILIsEqual(pidl1, pidl2), "expected same PIDL\n");
    IPersistFolder2_Release(pf);

    ILFree(pidl1);
    ILFree(pidl2);
    IShellFolder2_Release(folder);

    CoUninitialize();
}