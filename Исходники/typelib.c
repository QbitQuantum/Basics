static void test_CreateDispTypeInfo(void)
{
    ITypeInfo *pTypeInfo, *pTI2;
    HRESULT hr;
    INTERFACEDATA ifdata;
    METHODDATA methdata[4];
    PARAMDATA parms1[2];
    PARAMDATA parms3[1];
    TYPEATTR *pTypeAttr;
    HREFTYPE href;
    FUNCDESC *pFuncDesc;
    MEMBERID memid;

    static WCHAR func1[] = {'f','u','n','c','1',0};
    static const WCHAR func2[] = {'f','u','n','c','2',0};
    static const WCHAR func3[] = {'f','u','n','c','3',0};
    static const WCHAR parm1[] = {'p','a','r','m','1',0};
    static const WCHAR parm2[] = {'p','a','r','m','2',0};
    OLECHAR *name = func1;

    ifdata.pmethdata = methdata;
    ifdata.cMembers = sizeof(methdata) / sizeof(methdata[0]);

    methdata[0].szName = SysAllocString(func1);
    methdata[0].ppdata = parms1;
    methdata[0].dispid = 0x123;
    methdata[0].iMeth = 0;
    methdata[0].cc = CC_STDCALL;
    methdata[0].cArgs = 2;
    methdata[0].wFlags = DISPATCH_METHOD;
    methdata[0].vtReturn = VT_HRESULT;
    parms1[0].szName = SysAllocString(parm1);
    parms1[0].vt = VT_I4;
    parms1[1].szName = SysAllocString(parm2);
    parms1[1].vt = VT_BSTR;

    methdata[1].szName = SysAllocString(func2);
    methdata[1].ppdata = NULL;
    methdata[1].dispid = 0x124;
    methdata[1].iMeth = 1;
    methdata[1].cc = CC_STDCALL;
    methdata[1].cArgs = 0;
    methdata[1].wFlags = DISPATCH_PROPERTYGET;
    methdata[1].vtReturn = VT_I4;

    methdata[2].szName = SysAllocString(func3);
    methdata[2].ppdata = parms3;
    methdata[2].dispid = 0x125;
    methdata[2].iMeth = 3;
    methdata[2].cc = CC_STDCALL;
    methdata[2].cArgs = 1;
    methdata[2].wFlags = DISPATCH_PROPERTYPUT;
    methdata[2].vtReturn = VT_HRESULT;
    parms3[0].szName = SysAllocString(parm1);
    parms3[0].vt = VT_I4;

    methdata[3].szName = SysAllocString(func3);
    methdata[3].ppdata = NULL;
    methdata[3].dispid = 0x125;
    methdata[3].iMeth = 4;
    methdata[3].cc = CC_STDCALL;
    methdata[3].cArgs = 0;
    methdata[3].wFlags = DISPATCH_PROPERTYGET;
    methdata[3].vtReturn = VT_I4;

    hr = CreateDispTypeInfo(&ifdata, LOCALE_NEUTRAL, &pTypeInfo);
    ok(hr == S_OK, "hr %08x\n", hr);

    hr = ITypeInfo_GetTypeAttr(pTypeInfo, &pTypeAttr);
    ok(hr == S_OK, "hr %08x\n", hr);

    ok(pTypeAttr->typekind == TKIND_COCLASS, "typekind %0x\n", pTypeAttr->typekind);
    ok(pTypeAttr->cImplTypes == 1, "cImplTypes %d\n", pTypeAttr->cImplTypes);
    ok(pTypeAttr->cFuncs == 0, "cFuncs %d\n", pTypeAttr->cFuncs);
    ok(pTypeAttr->wTypeFlags == 0, "wTypeFlags %04x\n", pTypeAttr->cFuncs);
    ITypeInfo_ReleaseTypeAttr(pTypeInfo, pTypeAttr);

    hr = ITypeInfo_GetRefTypeOfImplType(pTypeInfo, 0, &href);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(href == 0, "href = 0x%x\n", href);
    hr = ITypeInfo_GetRefTypeInfo(pTypeInfo, href, &pTI2);
    ok(hr == S_OK, "hr %08x\n", hr);
    hr = ITypeInfo_GetTypeAttr(pTI2, &pTypeAttr);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pTypeAttr->typekind == TKIND_INTERFACE, "typekind %0x\n", pTypeAttr->typekind);
    ok(pTypeAttr->cFuncs == 4, "cFuncs %d\n", pTypeAttr->cFuncs);
    ok(IsEqualGUID(&pTypeAttr->guid, &GUID_NULL), "guid {%08x-...}\n", pTypeAttr->guid.Data1);
    ok(pTypeAttr->wTypeFlags == 0, "typeflags %08x\n", pTypeAttr->wTypeFlags);

    ITypeInfo_ReleaseTypeAttr(pTI2, pTypeAttr);

    hr = ITypeInfo_GetFuncDesc(pTI2, 0, &pFuncDesc);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFuncDesc->memid == 0x123, "memid %x\n", pFuncDesc->memid);
    ok(pFuncDesc->funckind == FUNC_VIRTUAL, "funckind %d\n", pFuncDesc->funckind);
    ok(pFuncDesc->invkind == methdata[0].wFlags, "invkind %d\n", pFuncDesc->invkind);
    ok(pFuncDesc->callconv == methdata[0].cc, "callconv %d\n", pFuncDesc->callconv);
    ok(pFuncDesc->cParams == methdata[0].cArgs, "cParams %d\n", pFuncDesc->cParams);
    ok(pFuncDesc->oVft == 0, "oVft %d\n", pFuncDesc->oVft);
    ok(pFuncDesc->wFuncFlags == 0, "oVft %d\n", pFuncDesc->wFuncFlags);
    ok(pFuncDesc->elemdescFunc.tdesc.vt == VT_HRESULT, "ret vt %x\n", pFuncDesc->elemdescFunc.tdesc.vt);
    ok(pFuncDesc->lprgelemdescParam[0].tdesc.vt == VT_I4, "parm 0 vt %x\n", pFuncDesc->lprgelemdescParam[0].tdesc.vt);
    ok(U(pFuncDesc->lprgelemdescParam[0]).paramdesc.wParamFlags == PARAMFLAG_NONE, "parm 0 flags %x\n", U(pFuncDesc->lprgelemdescParam[0]).paramdesc.wParamFlags);

    ok(pFuncDesc->lprgelemdescParam[1].tdesc.vt == VT_BSTR, "parm 1 vt %x\n", pFuncDesc->lprgelemdescParam[1].tdesc.vt);
    ok(U(pFuncDesc->lprgelemdescParam[1]).paramdesc.wParamFlags == PARAMFLAG_NONE, "parm 1 flags %x\n", U(pFuncDesc->lprgelemdescParam[1]).paramdesc.wParamFlags);
    ITypeInfo_ReleaseFuncDesc(pTI2, pFuncDesc);

    hr = ITypeInfo_GetFuncDesc(pTI2, 1, &pFuncDesc);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFuncDesc->funckind == FUNC_VIRTUAL, "funckind %d\n", pFuncDesc->funckind);
    ok(pFuncDesc->invkind == methdata[1].wFlags, "invkind %d\n", pFuncDesc->invkind);
    ok(pFuncDesc->callconv == methdata[1].cc, "callconv %d\n", pFuncDesc->callconv);
    ok(pFuncDesc->cParams == methdata[1].cArgs, "cParams %d\n", pFuncDesc->cParams);
    ok(pFuncDesc->oVft == 4, "oVft %d\n", pFuncDesc->oVft);
    ok(pFuncDesc->wFuncFlags == 0, "oVft %d\n", pFuncDesc->wFuncFlags);
    ok(pFuncDesc->elemdescFunc.tdesc.vt == VT_I4, "ret vt %x\n", pFuncDesc->elemdescFunc.tdesc.vt);
    ITypeInfo_ReleaseFuncDesc(pTI2, pFuncDesc);

    hr = ITypeInfo_GetFuncDesc(pTI2, 2, &pFuncDesc);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFuncDesc->funckind == FUNC_VIRTUAL, "funckind %d\n", pFuncDesc->funckind);
    ok(pFuncDesc->invkind == methdata[2].wFlags, "invkind %d\n", pFuncDesc->invkind);
    ok(pFuncDesc->callconv == methdata[2].cc, "callconv %d\n", pFuncDesc->callconv);
    ok(pFuncDesc->cParams == methdata[2].cArgs, "cParams %d\n", pFuncDesc->cParams);
    ok(pFuncDesc->oVft == 12, "oVft %d\n", pFuncDesc->oVft);
    ok(pFuncDesc->wFuncFlags == 0, "oVft %d\n", pFuncDesc->wFuncFlags);
    ok(pFuncDesc->elemdescFunc.tdesc.vt == VT_HRESULT, "ret vt %x\n", pFuncDesc->elemdescFunc.tdesc.vt);
    ok(pFuncDesc->lprgelemdescParam[0].tdesc.vt == VT_I4, "parm 0 vt %x\n", pFuncDesc->lprgelemdescParam[0].tdesc.vt);
    ok(U(pFuncDesc->lprgelemdescParam[0]).paramdesc.wParamFlags == PARAMFLAG_NONE, "parm 0 flags %x\n", U(pFuncDesc->lprgelemdescParam[0]).paramdesc.wParamFlags);
    ITypeInfo_ReleaseFuncDesc(pTI2, pFuncDesc);

    hr = ITypeInfo_GetFuncDesc(pTI2, 3, &pFuncDesc);
    ok(hr == S_OK, "hr %08x\n", hr);
    ok(pFuncDesc->funckind == FUNC_VIRTUAL, "funckind %d\n", pFuncDesc->funckind);
    ok(pFuncDesc->invkind == methdata[3].wFlags, "invkind %d\n", pFuncDesc->invkind);
    ok(pFuncDesc->callconv == methdata[3].cc, "callconv %d\n", pFuncDesc->callconv);
    ok(pFuncDesc->cParams == methdata[3].cArgs, "cParams %d\n", pFuncDesc->cParams);
    ok(pFuncDesc->oVft == 16, "oVft %d\n", pFuncDesc->oVft);
    ok(pFuncDesc->wFuncFlags == 0, "oVft %d\n", pFuncDesc->wFuncFlags);
    ok(pFuncDesc->elemdescFunc.tdesc.vt == VT_I4, "ret vt %x\n", pFuncDesc->elemdescFunc.tdesc.vt);
    ITypeInfo_ReleaseFuncDesc(pTI2, pFuncDesc);

    /* test GetIDsOfNames on a coclass to see if it searches its interfaces */
    hr = ITypeInfo_GetIDsOfNames(pTypeInfo, &name, 1, &memid);
    ok(hr == S_OK, "hr 0x%08x\n", hr);
    ok(memid == 0x123, "memid 0x%08x\n", memid);

    ITypeInfo_Release(pTI2);
    ITypeInfo_Release(pTypeInfo);

    SysFreeString(parms1[0].szName);
    SysFreeString(parms1[1].szName);
    SysFreeString(parms3[0].szName);
    SysFreeString(methdata[0].szName);
    SysFreeString(methdata[1].szName);
    SysFreeString(methdata[2].szName);
    SysFreeString(methdata[3].szName);
}