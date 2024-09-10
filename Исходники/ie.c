static void test_navigate(IWebBrowser2 *wb, const char *url)
{
    VARIANT urlv, emptyv;
    MSG msg;
    HRESULT hres;

    SET_EXPECT(Invoke_NAVIGATECOMPLETE2);

    V_VT(&urlv) = VT_BSTR;
    V_BSTR(&urlv) = a2bstr(url);
    V_VT(&emptyv) = VT_EMPTY;
    hres = IWebBrowser2_Navigate2(wb, &urlv, &emptyv, &emptyv, &emptyv, &emptyv);
    ok(hres == S_OK, "Navigate2 failed: %08x\n", hres);
    SysFreeString(V_BSTR(&urlv));

    while(!navigate_complete && GetMessageW(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CHECK_CALLED(Invoke_NAVIGATECOMPLETE2);
}