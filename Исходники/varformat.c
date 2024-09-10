static void test_VarFormatFromTokens(void)
{
    static WCHAR number_fmt[] = {'#','#','#',',','#','#','0','.','0','0',0};
    static const WCHAR number[] = {'6',',','9','0',0};
    static const WCHAR number_us[] = {'6','9','0','.','0','0',0};

    static WCHAR date_fmt[] = {'d','d','-','m','m',0};
    static const WCHAR date[] = {'1','2','-','1','1',0};
    static const WCHAR date_us[] = {'1','1','-','1','2',0};

    static WCHAR string_fmt[] = {'@',0};
    static const WCHAR string_de[] = {'1',',','5',0};
    static const WCHAR string_us[] = {'1','.','5',0};

    BYTE buff[256];
    LCID lcid;
    VARIANT var;
    BSTR bstr;
    HRESULT hres;

    V_VT(&var) = VT_BSTR;
    V_BSTR(&var) = SysAllocString(number);

    lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
    hres = VarTokenizeFormatString(number_fmt, buff, sizeof(buff), 1, 1, lcid, NULL);
    ok(hres == S_OK, "VarTokenizeFormatString failed: %x\n", hres);
    hres = VarFormatFromTokens(&var, number_fmt, buff, 0, &bstr, lcid);
    ok(hres == S_OK, "VarFormatFromTokens failed: %x\n", hres);
    ok(!strcmpW(bstr, number_us), "incorrectly formatted number: %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    lcid = MAKELCID(MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN), SORT_DEFAULT);
    hres = VarTokenizeFormatString(number_fmt, buff, sizeof(buff), 1, 1, lcid, NULL);
    ok(hres == S_OK, "VarTokenizeFormatString failed: %x\n", hres);
    hres = VarFormatFromTokens(&var, number_fmt, buff, 0, &bstr, lcid);
    ok(hres == S_OK, "VarFormatFromTokens failed: %x\n", hres);
    ok(!strcmpW(bstr, number), "incorrectly formatted number: %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    VariantClear(&var);

    V_VT(&var) = VT_BSTR;
    V_BSTR(&var) = SysAllocString(date);

    lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
    hres = VarTokenizeFormatString(date_fmt, buff, sizeof(buff), 1, 1, lcid, NULL);
    ok(hres == S_OK, "VarTokenizeFormatString failed: %x\n", hres);
    hres = VarFormatFromTokens(&var, date_fmt, buff, 0, &bstr, lcid);
    ok(hres == S_OK, "VarFormatFromTokens failed: %x\n", hres);
    ok(!strcmpW(bstr, date_us), "incorrectly formatted date: %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    lcid = MAKELCID(MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN), SORT_DEFAULT);
    hres = VarTokenizeFormatString(date_fmt, buff, sizeof(buff), 1, 1, lcid, NULL);
    ok(hres == S_OK, "VarTokenizeFormatString failed: %x\n", hres);
    hres = VarFormatFromTokens(&var, date_fmt, buff, 0, &bstr, lcid);
    ok(hres == S_OK, "VarFormatFromTokens failed: %x\n", hres);
    ok(!strcmpW(bstr, date), "incorrectly formatted date: %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    VariantClear(&var);

    V_VT(&var) = VT_R4;
    V_R4(&var) = 1.5;

    lcid = MAKELCID(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), SORT_DEFAULT);
    hres = VarTokenizeFormatString(string_fmt, buff, sizeof(buff), 1, 1, lcid, NULL);
    ok(hres == S_OK, "VarTokenizeFormatString failed: %x\n", hres);
    hres = VarFormatFromTokens(&var, string_fmt, buff, 0, &bstr, lcid);
    ok(hres == S_OK, "VarFormatFromTokens failed: %x\n", hres);
    ok(!strcmpW(bstr, string_us), "incorrectly formatted string: %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);

    lcid = MAKELCID(MAKELANGID(LANG_GERMAN, SUBLANG_GERMAN), SORT_DEFAULT);
    hres = VarTokenizeFormatString(string_fmt, buff, sizeof(buff), 1, 1, lcid, NULL);
    ok(hres == S_OK, "VarTokenizeFormatString failed: %x\n", hres);
    hres = VarFormatFromTokens(&var, string_fmt, buff, 0, &bstr, lcid);
    ok(hres == S_OK, "VarFormatFromTokens failed: %x\n", hres);
    ok(!strcmpW(bstr, string_de), "incorrectly formatted string: %s\n", wine_dbgstr_w(bstr));
    SysFreeString(bstr);
}