static HRESULT WINAPI httprequest_open(IXMLHTTPRequest *iface, BSTR method, BSTR url,
        VARIANT async, VARIANT user, VARIANT password)
{
    httprequest *This = impl_from_IXMLHTTPRequest( iface );
    HRESULT hr;
    VARIANT str, is_async;

    TRACE("(%p)->(%s %s %s)\n", This, debugstr_w(method), debugstr_w(url),
        debugstr_variant(&async));

    if (!method || !url) return E_INVALIDARG;

    /* free previously set data */
    SysFreeString(This->url);
    SysFreeString(This->user);
    SysFreeString(This->password);
    This->url = This->user = This->password = NULL;

    if (lstrcmpiW(method, MethodGetW) == 0)
    {
        This->verb = BINDVERB_GET;
    }
    else if (lstrcmpiW(method, MethodPutW) == 0)
    {
        This->verb = BINDVERB_PUT;
    }
    else if (lstrcmpiW(method, MethodPostW) == 0)
    {
        This->verb = BINDVERB_POST;
    }
    else
    {
        FIXME("unsupported request type %s\n", debugstr_w(method));
        This->verb = -1;
        return E_FAIL;
    }

    This->url = SysAllocString(url);

    VariantInit(&is_async);
    hr = VariantChangeType(&is_async, &async, 0, VT_BOOL);
    This->async = hr == S_OK && V_BOOL(&is_async) == VARIANT_TRUE;

    VariantInit(&str);
    hr = VariantChangeType(&str, &user, 0, VT_BSTR);
    if (hr == S_OK)
        This->user = V_BSTR(&str);

    hr = VariantChangeType(&str, &password, 0, VT_BSTR);
    if (hr == S_OK)
        This->password = V_BSTR(&str);

    httprequest_setreadystate(This, READYSTATE_LOADING);

    return S_OK;
}