static void test_registry(void)
{
    static const WCHAR keypathW[] = {'H','K','E','Y','_','C','U','R','R','E','N','T','_','U','S','E','R','\\',
        'S','o','f','t','w','a','r','e','\\','W','i','n','e','\\','T','e','s','t','\\',0};
    static const WCHAR regsz2W[] = {'r','e','g','s','z','2',0};
    static const WCHAR regszW[] = {'r','e','g','s','z',0};
    static const WCHAR regdwordW[] = {'r','e','g','d','w','o','r','d',0};
    static const WCHAR regbinaryW[] = {'r','e','g','b','i','n','a','r','y',0};
    static const WCHAR regmultiszW[] = {'r','e','g','m','u','l','t','i','s','z',0};

    static const WCHAR regsz1W[] = {'H','K','E','Y','_','C','U','R','R','E','N','T','_','U','S','E','R','\\',
        'S','o','f','t','w','a','r','e','\\','W','i','n','e','\\','T','e','s','t','\\','r','e','g','s','z','1',0};
    static const WCHAR foobarW[] = {'f','o','o','b','a','r',0};
    static const WCHAR fooW[] = {'f','o','o',0};
    static const WCHAR brokenW[] = {'H','K','E','Y','_','b','r','o','k','e','n','_','k','e','y',0};
    static const WCHAR broken2W[] = {'H','K','E','Y','_','C','U','R','R','E','N','T','_','U','S','E','R','a',0};
    WCHAR pathW[MAX_PATH];
    DWORD dwvalue, type;
    VARIANT value, v;
    IWshShell3 *sh3;
    VARTYPE vartype;
    LONG bound;
    HRESULT hr;
    BSTR name;
    HKEY root;
    LONG ret;
    UINT dim;

    hr = CoCreateInstance(&CLSID_WshShell, NULL, CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER,
            &IID_IWshShell3, (void**)&sh3);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    /* RegRead() */
    V_VT(&value) = VT_I2;
    hr = IWshShell3_RegRead(sh3, NULL, &value);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);
    ok(V_VT(&value) == VT_I2, "got %d\n", V_VT(&value));

    name = SysAllocString(brokenW);
    hr = IWshShell3_RegRead(sh3, name, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);
    V_VT(&value) = VT_I2;
    hr = IWshShell3_RegRead(sh3, name, &value);
    ok(hr == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), "got 0x%08x\n", hr);
    ok(V_VT(&value) == VT_I2, "got %d\n", V_VT(&value));
    SysFreeString(name);

    name = SysAllocString(broken2W);
    V_VT(&value) = VT_I2;
    hr = IWshShell3_RegRead(sh3, name, &value);
    ok(hr == HRESULT_FROM_WIN32(ERROR_PATH_NOT_FOUND), "got 0x%08x\n", hr);
    ok(V_VT(&value) == VT_I2, "got %d\n", V_VT(&value));
    SysFreeString(name);

    ret = RegCreateKeyA(HKEY_CURRENT_USER, "Software\\Wine\\Test", &root);
    ok(ret == 0, "got %d\n", ret);

    ret = RegSetValueExA(root, "regsz", 0, REG_SZ, (const BYTE*)"foobar", 7);
    ok(ret == 0, "got %d\n", ret);

    ret = RegSetValueExA(root, "regsz2", 0, REG_SZ, (const BYTE*)"foobar\0f", 9);
    ok(ret == 0, "got %d\n", ret);

    ret = RegSetValueExA(root, "regmultisz", 0, REG_MULTI_SZ, (const BYTE*)"foo\0bar\0", 9);
    ok(ret == 0, "got %d\n", ret);

    dwvalue = 10;
    ret = RegSetValueExA(root, "regdword", 0, REG_DWORD, (const BYTE*)&dwvalue, sizeof(dwvalue));
    ok(ret == 0, "got %d\n", ret);

    dwvalue = 11;
    ret = RegSetValueExA(root, "regbinary", 0, REG_BINARY, (const BYTE*)&dwvalue, sizeof(dwvalue));
    ok(ret == 0, "got %d\n", ret);

    /* REG_SZ */
    lstrcpyW(pathW, keypathW);
    lstrcatW(pathW, regszW);
    name = SysAllocString(pathW);
    VariantInit(&value);
    hr = IWshShell3_RegRead(sh3, name, &value);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(V_VT(&value) == VT_BSTR, "got %d\n", V_VT(&value));
    ok(!lstrcmpW(V_BSTR(&value), foobarW), "got %s\n", wine_dbgstr_w(V_BSTR(&value)));
    VariantClear(&value);
    SysFreeString(name);

    /* REG_SZ with embedded NULL */
    lstrcpyW(pathW, keypathW);
    lstrcatW(pathW, regsz2W);
    name = SysAllocString(pathW);
    VariantInit(&value);
    hr = IWshShell3_RegRead(sh3, name, &value);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(V_VT(&value) == VT_BSTR, "got %d\n", V_VT(&value));
    ok(SysStringLen(V_BSTR(&value)) == 6, "len %d\n", SysStringLen(V_BSTR(&value)));
    VariantClear(&value);
    SysFreeString(name);

    /* REG_DWORD */
    lstrcpyW(pathW, keypathW);
    lstrcatW(pathW, regdwordW);
    name = SysAllocString(pathW);
    VariantInit(&value);
    hr = IWshShell3_RegRead(sh3, name, &value);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(V_VT(&value) == VT_I4, "got %d\n", V_VT(&value));
    ok(V_I4(&value) == 10, "got %d\n", V_I4(&value));
    SysFreeString(name);

    /* REG_BINARY */
    lstrcpyW(pathW, keypathW);
    lstrcatW(pathW, regbinaryW);
    name = SysAllocString(pathW);
    VariantInit(&value);
    hr = IWshShell3_RegRead(sh3, name, &value);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(V_VT(&value) == (VT_ARRAY|VT_VARIANT), "got 0x%x\n", V_VT(&value));
    dim = SafeArrayGetDim(V_ARRAY(&value));
    ok(dim == 1, "got %u\n", dim);

    hr = SafeArrayGetLBound(V_ARRAY(&value), 1, &bound);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(bound == 0, "got %u\n", bound);

    hr = SafeArrayGetUBound(V_ARRAY(&value), 1, &bound);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(bound == 3, "got %u\n", bound);

    hr = SafeArrayGetVartype(V_ARRAY(&value), &vartype);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(vartype == VT_VARIANT, "got %d\n", vartype);

    bound = 0;
    hr = SafeArrayGetElement(V_ARRAY(&value), &bound, &v);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(V_VT(&v) == VT_UI1, "got %d\n", V_VT(&v));
    ok(V_UI1(&v) == 11, "got %u\n", V_UI1(&v));
    VariantClear(&v);
    VariantClear(&value);
    SysFreeString(name);

    /* REG_MULTI_SZ */
    lstrcpyW(pathW, keypathW);
    lstrcatW(pathW, regmultiszW);
    name = SysAllocString(pathW);
    VariantInit(&value);
    hr = IWshShell3_RegRead(sh3, name, &value);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(V_VT(&value) == (VT_ARRAY|VT_VARIANT), "got 0x%x\n", V_VT(&value));
    SysFreeString(name);

    dim = SafeArrayGetDim(V_ARRAY(&value));
    ok(dim == 1, "got %u\n", dim);

    hr = SafeArrayGetLBound(V_ARRAY(&value), 1, &bound);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(bound == 0, "got %u\n", bound);

    hr = SafeArrayGetUBound(V_ARRAY(&value), 1, &bound);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(bound == 1, "got %u\n", bound);

    hr = SafeArrayGetVartype(V_ARRAY(&value), &vartype);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(vartype == VT_VARIANT, "got %d\n", vartype);

    bound = 0;
    hr = SafeArrayGetElement(V_ARRAY(&value), &bound, &v);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(V_VT(&v) == VT_BSTR, "got %d\n", V_VT(&v));
    ok(!lstrcmpW(V_BSTR(&v), fooW), "got %s\n", wine_dbgstr_w(V_BSTR(&v)));
    VariantClear(&v);
    VariantClear(&value);

    name = SysAllocString(regsz1W);
    V_VT(&value) = VT_I2;
    hr = IWshShell3_RegRead(sh3, name, &value);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), "got 0x%08x\n", hr);
    ok(V_VT(&value) == VT_I2, "got %d\n", V_VT(&value));
    VariantClear(&value);
    SysFreeString(name);

    delete_key(root);

    /* RegWrite() */
    ret = RegCreateKeyA(HKEY_CURRENT_USER, "Software\\Wine\\Test", &root);
    ok(ret == 0, "got %d\n", ret);

    hr = IWshShell3_RegWrite(sh3, NULL, NULL, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    lstrcpyW(pathW, keypathW);
    lstrcatW(pathW, regszW);
    name = SysAllocString(pathW);

    hr = IWshShell3_RegWrite(sh3, name, NULL, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    VariantInit(&value);
    hr = IWshShell3_RegWrite(sh3, name, &value, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    hr = IWshShell3_RegWrite(sh3, name, &value, &value);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    /* type is optional */
    V_VT(&v) = VT_ERROR;
    V_ERROR(&v) = DISP_E_PARAMNOTFOUND;
    hr = IWshShell3_RegWrite(sh3, name, &value, &v);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    /* default type is REG_SZ */
    V_VT(&value) = VT_I4;
    V_I4(&value) = 12;
    hr = IWshShell3_RegWrite(sh3, name, &value, &v);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    type = REG_NONE;
    ret = RegGetValueA(root, NULL, "regsz", RRF_RT_ANY, &type, NULL, NULL);
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);
    ok(type == REG_SZ, "got %d\n", type);

    ret = RegDeleteValueA(root, "regsz");
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);
    V_VT(&value) = VT_BSTR;
    V_BSTR(&value) = SysAllocString(regszW);
    hr = IWshShell3_RegWrite(sh3, name, &value, &v);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    VariantClear(&value);

    type = REG_NONE;
    ret = RegGetValueA(root, NULL, "regsz", RRF_RT_ANY, &type, NULL, NULL);
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);
    ok(type == REG_SZ, "got %d\n", type);

    ret = RegDeleteValueA(root, "regsz");
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);
    V_VT(&value) = VT_R4;
    V_R4(&value) = 1.2;
    hr = IWshShell3_RegWrite(sh3, name, &value, &v);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    VariantClear(&value);

    type = REG_NONE;
    ret = RegGetValueA(root, NULL, "regsz", RRF_RT_ANY, &type, NULL, NULL);
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);
    ok(type == REG_SZ, "got %d\n", type);

    ret = RegDeleteValueA(root, "regsz");
    ok(ret == ERROR_SUCCESS, "got %d\n", ret);
    V_VT(&value) = VT_R4;
    V_R4(&value) = 1.2;
    V_VT(&v) = VT_I2;
    V_I2(&v) = 1;
    hr = IWshShell3_RegWrite(sh3, name, &value, &v);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
    VariantClear(&value);

    SysFreeString(name);

    delete_key(root);
    IWshShell3_Release(sh3);
}