static void test_DMOUnregister(void)
{
    static const WCHAR testdmoW[] = {'t','e','s','t','d','m','o',0};
    HRESULT hr;

    hr = DMOUnregister(&GUID_unknowndmo, &GUID_unknowncategory);
    ok(hr == S_FALSE, "got 0x%08x\n", hr);

    hr = DMOUnregister(&GUID_unknowndmo, &GUID_NULL);
    ok(hr == S_FALSE, "got 0x%08x\n", hr);

    /* can't register for all categories */
    hr = DMORegister(testdmoW, &GUID_unknowndmo, &GUID_NULL, 0, 0, NULL, 0, NULL);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = DMORegister(testdmoW, &GUID_unknowndmo, &GUID_unknowncategory, 0, 0, NULL, 0, NULL);
    if (hr != S_OK) {
        win_skip("Failed to register DMO. Probably user doesn't have persmissions to do so.\n");
        return;
    }

    hr = DMOUnregister(&GUID_unknowndmo, &GUID_NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = DMOUnregister(&GUID_unknowndmo, &GUID_NULL);
    ok(hr == S_FALSE, "got 0x%08x\n", hr);
}