static HRESULT parse_script_ae(IActiveScriptParse *parser, const char *script)
{
    BSTR str;
    HRESULT hres;

    str = a2bstr(script);
    hres = IActiveScriptParse64_ParseScriptText(parser, str, NULL, NULL, NULL, 0, 0, 0, NULL, NULL);
    SysFreeString(str);

    return hres;
}