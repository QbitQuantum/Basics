static IDispatchEx *parse_procedure_a(IActiveScriptParse *parser, const char *src)
{
    IActiveScriptParseProcedure2 *parse_proc;
    IDispatchEx *dispex;
    IDispatch *disp;
    BSTR str;
    HRESULT hres;

    hres = IUnknown_QueryInterface(parser, &IID_IActiveScriptParseProcedure2, (void**)&parse_proc);
    ok(hres == S_OK, "Coult not get IActiveScriptParseProcedure2: %08x\n", hres);

    str = a2bstr(src);
    hres = IActiveScriptParseProcedure2_64_ParseProcedureText(parse_proc, str, NULL, NULL, NULL, NULL, NULL, 0, 0, 0, &disp);
    SysFreeString(str);
    IUnknown_Release(parse_proc);
    ok(hres == S_OK, "ParseProcedureText failed: %08x\n", hres);
    ok(disp != NULL, "disp == NULL\n");

    hres = IDispatch_QueryInterface(disp, &IID_IDispatchEx, (void**)&dispex);
    IDispatch_Release(dispex);
    ok(hres == S_OK, "Could not get IDispatchEx iface: %08x\n", hres);

    return dispex;
}