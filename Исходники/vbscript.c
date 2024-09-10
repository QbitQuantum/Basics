static void parse_script(IActiveScriptParse *parse, const char *src)
{
    BSTR str;
    HRESULT hres;

    SET_EXPECT(OnEnterScript);
    SET_EXPECT(OnLeaveScript);

    str = a2bstr(src);
    hres = IActiveScriptParse_ParseScriptText(parse, str, NULL, NULL, NULL, 0, 0, 0, NULL, NULL);
    SysFreeString(str);
    ok(hres == S_OK, "ParseScriptText failed: %08x\n", hres);

    CHECK_CALLED(OnEnterScript);
    CHECK_CALLED(OnLeaveScript);
}