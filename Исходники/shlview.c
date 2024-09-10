static void test_GetItemObject(void)
{
    IShellFolder *desktop;
    IShellView *view;
    IUnknown *unk;
    HRESULT hr;

    hr = SHGetDesktopFolder(&desktop);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    hr = IShellFolder_CreateViewObject(desktop, NULL, &IID_IShellView, (void**)&view);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    /* from documentation three interfaces are supported for SVGIO_BACKGROUND:
       IContextMenu, IDispatch, IPersistHistory */
    hr = IShellView_GetItemObject(view, SVGIO_BACKGROUND, &IID_IContextMenu, (void**)&unk);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    IUnknown_Release(unk);

    unk = NULL;
    hr = IShellView_GetItemObject(view, SVGIO_BACKGROUND, &IID_IDispatch, (void**)&unk);
    todo_wine ok(hr == S_OK || broken(hr == E_NOTIMPL) /* NT4 */, "got (0x%08x)\n", hr);
    if (unk) IUnknown_Release(unk);

    unk = NULL;
    hr = IShellView_GetItemObject(view, SVGIO_BACKGROUND, &IID_IPersistHistory, (void**)&unk);
    todo_wine ok(hr == S_OK || broken(hr == E_NOTIMPL) /* W9x, NT4 */, "got (0x%08x)\n", hr);
    if (unk) IUnknown_Release(unk);

    /* example of unsupported interface, base for IPersistHistory */
    hr = IShellView_GetItemObject(view, SVGIO_BACKGROUND, &IID_IPersist, (void**)&unk);
    ok(hr == E_NOINTERFACE || broken(hr == E_NOTIMPL) /* W2K */, "got (0x%08x)\n", hr);

    IShellView_Release(view);
    IShellFolder_Release(desktop);
}