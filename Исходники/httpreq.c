static void test_XMLHTTP(void)
{
    static const char bodyA[] = "mode=Test";
    static const char urlA[] = "http://crossover.codeweavers.com/posttest.php";
    static const char xmltestA[] = "http://crossover.codeweavers.com/xmltest.xml";
    static const char referertesturl[] = "http://test.winehq.org/tests/referer.php";
    static const WCHAR wszExpectedResponse[] = {'F','A','I','L','E','D',0};
    static const CHAR xmltestbodyA[] = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<a>TEST</a>\n";
    static const WCHAR norefererW[] = {'n','o',' ','r','e','f','e','r','e','r',' ','s','e','t',0};

    IXMLHttpRequest *xhr;
    IObjectWithSite *obj_site, *obj_site2;
    BSTR bstrResponse, str, str1;
    VARIANT varbody, varbody_ref;
    VARIANT dummy;
    LONG state, status, bound;
    IDispatch *event;
    void *ptr;
    HRESULT hr;
    HGLOBAL g;

    xhr = create_xhr();

    VariantInit(&dummy);
    V_VT(&dummy) = VT_ERROR;
    V_ERROR(&dummy) = DISP_E_MEMBERNOTFOUND;

    hr = IXMLHttpRequest_put_onreadystatechange(xhr, NULL);
    EXPECT_HR(hr, S_OK);

    hr = IXMLHttpRequest_abort(xhr);
    EXPECT_HR(hr, S_OK);

    V_VT(&varbody) = VT_I2;
    V_I2(&varbody) = 1;
    hr = IXMLHttpRequest_get_responseBody(xhr, &varbody);
    EXPECT_HR(hr, E_PENDING);
    ok(V_VT(&varbody) == VT_EMPTY, "got type %d\n", V_VT(&varbody));
    ok(V_I2(&varbody) == 1, "got %d\n", V_I2(&varbody));

    V_VT(&varbody) = VT_I2;
    V_I2(&varbody) = 1;
    hr = IXMLHttpRequest_get_responseStream(xhr, &varbody);
    EXPECT_HR(hr, E_PENDING);
    ok(V_VT(&varbody) == VT_EMPTY, "got type %d\n", V_VT(&varbody));
    ok(V_I2(&varbody) == 1, "got %d\n", V_I2(&varbody));

    /* send before open */
    hr = IXMLHttpRequest_send(xhr, dummy);
    ok(hr == E_FAIL || broken(hr == E_UNEXPECTED) /* win2k */, "got 0x%08x\n", hr);

    /* initial status code */
    hr = IXMLHttpRequest_get_status(xhr, NULL);
    ok(hr == E_POINTER || broken(hr == E_INVALIDARG) /* <win8 */, "got 0x%08x\n", hr);

    status = 0xdeadbeef;
    hr = IXMLHttpRequest_get_status(xhr, &status);
    ok(hr == E_FAIL || broken(hr == E_UNEXPECTED) /* win2k */, "got 0x%08x\n", hr);
    ok(status == READYSTATE_UNINITIALIZED || broken(status == 0xdeadbeef) /* <win8 */, "got %d\n", status);

    hr = IXMLHttpRequest_get_statusText(xhr, &str);
    ok(hr == E_FAIL, "got 0x%08x\n", hr);

    /* invalid parameters */
    test_open(xhr, NULL, NULL, E_INVALIDARG);
    test_open(xhr, "POST", NULL, E_INVALIDARG);
    test_open(xhr, NULL, urlA, E_INVALIDARG);

    hr = IXMLHttpRequest_setRequestHeader(xhr, NULL, NULL);
    EXPECT_HR(hr, E_INVALIDARG);

    hr = IXMLHttpRequest_setRequestHeader(xhr, _bstr_("header1"), NULL);
    ok(hr == E_FAIL || broken(hr == E_UNEXPECTED) /* win2k */, "got 0x%08x\n", hr);

    hr = IXMLHttpRequest_setRequestHeader(xhr, NULL, _bstr_("value1"));
    EXPECT_HR(hr, E_INVALIDARG);

    hr = IXMLHttpRequest_setRequestHeader(xhr, _bstr_("header1"), _bstr_("value1"));
    ok(hr == E_FAIL || broken(hr == E_UNEXPECTED) /* win2k */, "got 0x%08x\n", hr);

    hr = IXMLHttpRequest_get_readyState(xhr, NULL);
    ok(hr == E_POINTER || broken(hr == E_INVALIDARG) /* <win8 */, "got 0x%08x\n", hr);

    state = -1;
    hr = IXMLHttpRequest_get_readyState(xhr, &state);
    EXPECT_HR(hr, S_OK);
    ok(state == READYSTATE_UNINITIALIZED, "got %d, expected READYSTATE_UNINITIALIZED\n", state);

    httpreq = xhr;
    event = create_dispevent();

    EXPECT_REF(event, 1);
    hr = IXMLHttpRequest_put_onreadystatechange(xhr, event);
    EXPECT_HR(hr, S_OK);
    EXPECT_REF(event, 2);

    g_unexpectedcall = g_expectedcall = 0;

    test_open(xhr, "POST", urlA, S_OK);

    ok(g_unexpectedcall == 0, "unexpected disp event call\n");
    ok(g_expectedcall == 1 || broken(g_expectedcall == 0) /* win2k */, "no expected disp event call\n");

    /* status code after ::open() */
    status = 0xdeadbeef;
    hr = IXMLHttpRequest_get_status(xhr, &status);
    ok(hr == E_FAIL || broken(hr == E_UNEXPECTED) /* win2k */, "got 0x%08x\n", hr);
    ok(status == READYSTATE_UNINITIALIZED || broken(status == 0xdeadbeef) /* <win8 */, "got %d\n", status);

    state = -1;
    hr = IXMLHttpRequest_get_readyState(xhr, &state);
    EXPECT_HR(hr, S_OK);
    ok(state == READYSTATE_LOADING, "got %d, expected READYSTATE_LOADING\n", state);

    hr = IXMLHttpRequest_abort(xhr);
    EXPECT_HR(hr, S_OK);

    state = -1;
    hr = IXMLHttpRequest_get_readyState(xhr, &state);
    EXPECT_HR(hr, S_OK);
    ok(state == READYSTATE_UNINITIALIZED || broken(state == READYSTATE_LOADING) /* win2k */,
        "got %d, expected READYSTATE_UNINITIALIZED\n", state);

    test_open(xhr, "POST", urlA, S_OK);

    hr = IXMLHttpRequest_setRequestHeader(xhr, _bstr_("header1"), _bstr_("value1"));
    EXPECT_HR(hr, S_OK);

    hr = IXMLHttpRequest_setRequestHeader(xhr, NULL, _bstr_("value1"));
    EXPECT_HR(hr, E_INVALIDARG);

    hr = IXMLHttpRequest_setRequestHeader(xhr, _bstr_(""), _bstr_("value1"));
    EXPECT_HR(hr, E_INVALIDARG);

    V_VT(&varbody) = VT_BSTR;
    V_BSTR(&varbody) = _bstr_(bodyA);

    hr = IXMLHttpRequest_send(xhr, varbody);
    if (hr == INET_E_RESOURCE_NOT_FOUND)
    {
        skip("No connection could be made with crossover.codeweavers.com\n");
        IXMLHttpRequest_Release(xhr);
        return;
    }
    EXPECT_HR(hr, S_OK);

    /* response headers */
    hr = IXMLHttpRequest_getAllResponseHeaders(xhr, NULL);
    ok(hr == E_POINTER || broken(hr == E_INVALIDARG) /* <win8 */, "got 0x%08x\n", hr);
    hr = IXMLHttpRequest_getAllResponseHeaders(xhr, &str);
    EXPECT_HR(hr, S_OK);
    /* status line is stripped already */
    ok(memcmp(str, _bstr_("HTTP"), 4*sizeof(WCHAR)), "got response headers %s\n", wine_dbgstr_w(str));
    ok(*str, "got empty headers\n");
    hr = IXMLHttpRequest_getAllResponseHeaders(xhr, &str1);
    EXPECT_HR(hr, S_OK);
    ok(str1 != str, "got %p\n", str1);
    SysFreeString(str1);
    SysFreeString(str);

    hr = IXMLHttpRequest_getResponseHeader(xhr, NULL, NULL);
    EXPECT_HR(hr, E_INVALIDARG);
    hr = IXMLHttpRequest_getResponseHeader(xhr, _bstr_("Date"), NULL);
    ok(hr == E_POINTER || broken(hr == E_INVALIDARG) /* <win8 */, "got 0x%08x\n", hr);
    hr = IXMLHttpRequest_getResponseHeader(xhr, _bstr_("Date"), &str);
    EXPECT_HR(hr, S_OK);
    ok(*str != ' ', "got leading space in header %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    /* status code after ::send() */
    status = 0xdeadbeef;
    hr = IXMLHttpRequest_get_status(xhr, &status);
    EXPECT_HR(hr, S_OK);
    ok(status == 200, "got %d\n", status);

    hr = IXMLHttpRequest_get_statusText(xhr, NULL);
    ok(hr == E_POINTER || broken(hr == E_INVALIDARG) /* <win8 */, "got 0x%08x\n", hr);

    hr = IXMLHttpRequest_get_statusText(xhr, &str);
    EXPECT_HR(hr, S_OK);
    ok(!lstrcmpW(str, _bstr_("OK")), "got status %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    /* another ::send() after completed request */
    V_VT(&varbody) = VT_BSTR;
    V_BSTR(&varbody) = _bstr_(bodyA);

    hr = IXMLHttpRequest_send(xhr, varbody);
    ok(hr == E_FAIL || broken(hr == E_UNEXPECTED) /* win2k */, "got 0x%08x\n", hr);

    hr = IXMLHttpRequest_get_responseText(xhr, &bstrResponse);
    EXPECT_HR(hr, S_OK);
    /* the server currently returns "FAILED" because the Content-Type header is
     * not what the server expects */
    if(hr == S_OK)
    {
        ok(!memcmp(bstrResponse, wszExpectedResponse, sizeof(wszExpectedResponse)),
            "expected %s, got %s\n", wine_dbgstr_w(wszExpectedResponse), wine_dbgstr_w(bstrResponse));
        SysFreeString(bstrResponse);
    }

    /* POST: VT_VARIANT|VT_BYREF body */
    test_open(xhr, "POST", urlA, S_OK);

    V_VT(&varbody_ref) = VT_VARIANT|VT_BYREF;
    V_VARIANTREF(&varbody_ref) = &varbody;
    hr = IXMLHttpRequest_send(xhr, varbody_ref);
    EXPECT_HR(hr, S_OK);

    /* GET request */
    test_open(xhr, "GET", xmltestA, S_OK);

    V_VT(&varbody) = VT_EMPTY;

    hr = IXMLHttpRequest_send(xhr, varbody);
    if (hr == INET_E_RESOURCE_NOT_FOUND)
    {
        skip("No connection could be made with crossover.codeweavers.com\n");
        IXMLHttpRequest_Release(xhr);
        return;
    }
    EXPECT_HR(hr, S_OK);

    hr = IXMLHttpRequest_get_responseText(xhr, NULL);
    ok(hr == E_POINTER || broken(hr == E_INVALIDARG) /* <win8 */, "got 0x%08x\n", hr);

    hr = IXMLHttpRequest_get_responseText(xhr, &bstrResponse);
    EXPECT_HR(hr, S_OK);
    ok(!memcmp(bstrResponse, _bstr_(xmltestbodyA), sizeof(xmltestbodyA)*sizeof(WCHAR)),
        "expected %s, got %s\n", xmltestbodyA, wine_dbgstr_w(bstrResponse));
    SysFreeString(bstrResponse);

    hr = IXMLHttpRequest_get_responseBody(xhr, NULL);
    EXPECT_HR(hr, E_INVALIDARG);

    V_VT(&varbody) = VT_EMPTY;
    hr = IXMLHttpRequest_get_responseBody(xhr, &varbody);
    EXPECT_HR(hr, S_OK);
    ok(V_VT(&varbody) == (VT_ARRAY|VT_UI1), "got type %d, expected %d\n", V_VT(&varbody), VT_ARRAY|VT_UI1);
    ok(SafeArrayGetDim(V_ARRAY(&varbody)) == 1, "got %d, expected one dimension\n", SafeArrayGetDim(V_ARRAY(&varbody)));

    bound = -1;
    hr = SafeArrayGetLBound(V_ARRAY(&varbody), 1, &bound);
    EXPECT_HR(hr, S_OK);
    ok(bound == 0, "got %d, expected zero bound\n", bound);

    hr = SafeArrayAccessData(V_ARRAY(&varbody), &ptr);
    EXPECT_HR(hr, S_OK);
    ok(memcmp(ptr, xmltestbodyA, sizeof(xmltestbodyA)-1) == 0, "got wrong body data\n");
    SafeArrayUnaccessData(V_ARRAY(&varbody));

    VariantClear(&varbody);

    /* get_responseStream */
    hr = IXMLHttpRequest_get_responseStream(xhr, NULL);
    EXPECT_HR(hr, E_INVALIDARG);

    V_VT(&varbody) = VT_EMPTY;
    hr = IXMLHttpRequest_get_responseStream(xhr, &varbody);
    ok(V_VT(&varbody) == VT_UNKNOWN, "got type %d\n", V_VT(&varbody));
    EXPECT_HR(hr, S_OK);
    EXPECT_REF(V_UNKNOWN(&varbody), 1);

    g = NULL;
    hr = GetHGlobalFromStream((IStream*)V_UNKNOWN(&varbody), &g);
    EXPECT_HR(hr, S_OK);
    ok(g != NULL, "got %p\n", g);

    IDispatch_Release(event);

    /* test if referrer header is sent */
    test_open(xhr, "GET", referertesturl, S_OK);

    V_VT(&varbody) = VT_EMPTY;
    hr = IXMLHttpRequest_send(xhr, varbody);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = IXMLHttpRequest_get_responseText(xhr, &str);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(!lstrcmpW(str, norefererW), "got response text %s\n", wine_dbgstr_w(str));
    SysFreeString(str);

    /* interaction with object site */
    hr = IXMLHttpRequest_QueryInterface(xhr, &IID_IObjectWithSite, (void**)&obj_site);
    EXPECT_HR(hr, S_OK);

    hr = IObjectWithSite_SetSite(obj_site, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXMLHttpRequest_QueryInterface(xhr, &IID_IObjectWithSite, (void**)&obj_site2);
    EXPECT_HR(hr, S_OK);
    ok(obj_site == obj_site2 || broken(obj_site != obj_site2), "got new instance\n");
    IObjectWithSite_Release(obj_site2);

    set_xhr_site(xhr);

    test_open(xhr, "GET", "tests/referer.php", S_OK);
    str1 = a2bstr("http://test.winehq.org/");

    V_VT(&varbody) = VT_EMPTY;
    hr = IXMLHttpRequest_send(xhr, varbody);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IXMLHttpRequest_get_responseText(xhr, &str);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ok(!lstrcmpW(str, str1), "got response text %s, expected %s\n", wine_dbgstr_w(str), wine_dbgstr_w(str1));
    SysFreeString(str);
    SysFreeString(str1);

    /* try to set site another time */
    hr = IObjectWithSite_SetSite(obj_site, &testsite);
    EXPECT_HR(hr, S_OK);

    IObjectWithSite_Release(obj_site);
    IXMLHttpRequest_Release(xhr);
    free_bstrs();
}