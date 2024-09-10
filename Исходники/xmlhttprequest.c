static void test_async_xhr(IHTMLDocument2 *doc, const char *xml_url)
{
    VARIANT vbool, vempty, var;
    BSTR method, url;
    BSTR text;
    LONG val;
    HRESULT hres;

    create_xmlhttprequest(doc);
    if(!xhr)
        return;

    V_VT(&var) = VT_DISPATCH;
    V_DISPATCH(&var) = (IDispatch*)&xmlhttprequest_onreadystatechange_obj;
    hres = IHTMLXMLHttpRequest_put_onreadystatechange(xhr, var);
    ok(hres == S_OK, "put_onreadystatechange failed: %08x\n", hres);

    V_VT(&var) = VT_EMPTY;
    hres = IHTMLXMLHttpRequest_get_onreadystatechange(xhr, &var);
    ok(hres == S_OK, "get_onreadystatechange failed: %08x\n", hres);
    ok(V_VT(&var) == VT_DISPATCH, "V_VT(onreadystatechange) = %d\n", V_VT(&var));
    ok(V_DISPATCH(&var) == (IDispatch*)&xmlhttprequest_onreadystatechange_obj, "unexpected onreadystatechange value\n");

    val = 0xdeadbeef;
    hres = IHTMLXMLHttpRequest_get_status(xhr, &val);
    ok(hres == E_FAIL, "Expect E_FAIL, got: %08x\n", hres);
    ok(val == 0, "Expect 0, got %d\n", val);

    text = (BSTR)0xdeadbeef;
    hres = IHTMLXMLHttpRequest_get_statusText(xhr, &text);
    todo_wine ok(hres == E_FAIL, "Expect E_FAIL, got: %08x\n", hres);
    todo_wine ok(text == NULL, "Expect NULL, got %p\n", text);

    val = 0xdeadbeef;
    hres = IHTMLXMLHttpRequest_get_readyState(xhr, &val);
    ok(hres == S_OK, "get_readyState failed: %08x\n", hres);
    ok(val == 0, "Expect UNSENT, got %d\n", val);

    method = a2bstr("GET");
    url = a2bstr(xml_url);
    V_VT(&vbool) = VT_BOOL;
    V_BOOL(&vbool) = VARIANT_TRUE;
    V_VT(&vempty) = VT_EMPTY;

    SET_EXPECT(xmlhttprequest_onreadystatechange_opened);
    hres = IHTMLXMLHttpRequest_open(xhr, method, url, vbool, vempty, vempty);
    ok(hres == S_OK, "open failed: %08x\n", hres);
    CHECK_CALLED(xmlhttprequest_onreadystatechange_opened);

    SysFreeString(method);
    SysFreeString(url);

    if(FAILED(hres)) {
        IHTMLXMLHttpRequest_Release(xhr);
        xhr = NULL;
        return;
    }

    val = 0xdeadbeef;
    hres = IHTMLXMLHttpRequest_get_status(xhr, &val);
    ok(hres == E_FAIL, "Expect E_FAIL, got: %08x\n", hres);
    ok(val == 0, "Expect 0, got %d\n", val);

    hres = IHTMLXMLHttpRequest_get_statusText(xhr, &text);
    todo_wine ok(hres == E_FAIL, "Expect E_FAIL, got: %08x\n", hres);
    todo_wine ok(text == NULL, "Expect NULL, got %p\n", text);

    val = 0xdeadbeef;
    hres = IHTMLXMLHttpRequest_get_readyState(xhr, &val);
    ok(hres == S_OK, "get_readyState failed: %08x\n", hres);
    ok(val == 1, "Expect OPENED, got %d\n", val);

    SET_EXPECT(xmlhttprequest_onreadystatechange_opened);
    SET_EXPECT(xmlhttprequest_onreadystatechange_headers_received);
    SET_EXPECT(xmlhttprequest_onreadystatechange_loading);
    SET_EXPECT(xmlhttprequest_onreadystatechange_done);
    hres = IHTMLXMLHttpRequest_send(xhr, vempty);

    ok(hres == S_OK, "send failed: %08x\n", hres);
    if(SUCCEEDED(hres))
        pump_msgs(&called_xmlhttprequest_onreadystatechange_done);
    todo_wine CHECK_CALLED(xmlhttprequest_onreadystatechange_opened);
    CHECK_CALLED(xmlhttprequest_onreadystatechange_headers_received);
    CHECK_CALLED(xmlhttprequest_onreadystatechange_loading);
    CHECK_CALLED(xmlhttprequest_onreadystatechange_done);

    if(FAILED(hres)) {
        IHTMLXMLHttpRequest_Release(xhr);
        xhr = NULL;
        return;
    }

    val = 0xdeadbeef;
    hres = IHTMLXMLHttpRequest_get_status(xhr, &val);
    ok(hres == S_OK, "get_status failed: %08x\n", hres);
    ok(val == 200, "Expect 200, got %d\n", val);

    text = NULL;
    hres = IHTMLXMLHttpRequest_get_statusText(xhr, &text);
    todo_wine ok(hres == S_OK, "get_statusText failed: %08x\n", hres);
    todo_wine ok(text != NULL, "text == NULL\n");
    todo_wine ok(!strcmp_wa(text, "OK"), "Expected \"OK\", got %s\n", wine_dbgstr_w(text));
    SysFreeString(text);

    val = 0xdeadbeef;
    hres = IHTMLXMLHttpRequest_get_readyState(xhr, &val);
    ok(hres == S_OK, "get_readyState failed: %08x\n", hres);
    ok(val == 4, "Expect DONE, got %d\n", val);

    text = NULL;
    hres = IHTMLXMLHttpRequest_get_responseText(xhr, &text);
    ok(hres == S_OK, "get_responseText failed: %08x\n", hres);
    ok(text != NULL, "test == NULL\n");
    ok(!strcmp_wa(text, EXPECT_RESPONSE_TEXT), "expect %s, got %s\n",
        EXPECT_RESPONSE_TEXT, wine_dbgstr_w(text));
    SysFreeString(text);

    IHTMLXMLHttpRequest_Release(xhr);
    xhr = NULL;
}