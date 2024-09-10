static void test_setvalue_on_wow64(IPropertyStore *store)
{
    PROPVARIANT pv;
    HRESULT hr;
    LONG ret;
    WCHAR *guidW;
    HKEY root, props, devkey;
    DWORD type, regval, size;

    static const PROPERTYKEY PKEY_Bogus = {
        {0x1da5d803, 0xd492, 0x4edd, {0x8c, 0x23, 0xe0, 0xc0, 0xff, 0xee, 0x7f, 0x00}}, 0x7f
    };
    static const WCHAR bogusW[] = {'{','1','D','A','5','D','8','0','3','-','D','4','9','2','-','4','E','D','D','-','8','C','2','3','-','E','0','C','0','F','F','E','E','7','F','0','0','}',',','1','2','7',0};

    PropVariantInit(&pv);

    pv.vt = VT_EMPTY;
    hr = IPropertyStore_GetValue(store, &PKEY_AudioEndpoint_GUID, &pv);
    ok(hr == S_OK, "Failed to get Endpoint GUID: %08x\n", hr);

    guidW = pv.u.pwszVal;

    pv.vt = VT_UI4;
    pv.u.ulVal = 0xAB;

    hr = IPropertyStore_SetValue(store, &PKEY_Bogus, &pv);
    ok(hr == S_OK || hr == E_ACCESSDENIED, "SetValue failed: %08x\n", hr);
    if (hr != S_OK)
    {
        win_skip("Missing permission to write to registry\n");
        return;
    }

    pv.u.ulVal = 0x00;

    hr = IPropertyStore_GetValue(store, &PKEY_Bogus, &pv);
    ok(hr == S_OK, "GetValue failed: %08x\n", hr);
    ok(pv.u.ulVal == 0xAB, "Got wrong value: 0x%x\n", pv.u.ulVal);

    /* should find the key in 64-bit view */
    ret = RegOpenKeyExW(HKEY_LOCAL_MACHINE, software_renderW, 0, KEY_READ|KEY_WOW64_64KEY, &root);
    ok(ret == ERROR_SUCCESS, "Couldn't open mmdevices Render key: %u\n", ret);

    ret = RegOpenKeyExW(root, guidW, 0, KEY_READ|KEY_WOW64_64KEY, &devkey);
    ok(ret == ERROR_SUCCESS, "Couldn't open mmdevice guid key: %u\n", ret);

    ret = RegOpenKeyExW(devkey, propertiesW, 0, KEY_READ|KEY_WOW64_64KEY, &props);
    ok(ret == ERROR_SUCCESS, "Couldn't open mmdevice property key: %u\n", ret);

    /* Note: the registry key exists even without calling IPropStore::Commit */
    size = sizeof(regval);
    ret = RegGetValueW(props, NULL, bogusW, RRF_RT_DWORD, &type, &regval, &size);
    ok(ret == ERROR_SUCCESS, "Couldn't get bogus propertykey value: %u\n", ret);
    ok(type == REG_DWORD, "Got wrong value type: %u\n", type);
    ok(regval == 0xAB, "Got wrong value: 0x%x\n", regval);

    RegCloseKey(props);
    RegCloseKey(devkey);
    RegCloseKey(root);

    CoTaskMemFree(guidW);

    /* should NOT find the key in 32-bit view */
    ret = RegOpenKeyExW(HKEY_LOCAL_MACHINE, software_renderW, 0, KEY_READ, &root);
    ok(ret == ERROR_FILE_NOT_FOUND, "Wrong error when opening mmdevices Render key: %u\n", ret);
}