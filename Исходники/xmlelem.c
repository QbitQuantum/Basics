static HRESULT WINAPI xmlelem_get_tagName(IXMLElement *iface, BSTR *p)
{
    xmlelem *This = impl_from_IXMLElement(iface);

    TRACE("(%p, %p)\n", iface, p);

    if (!p)
        return E_INVALIDARG;

    *p = bstr_from_xmlChar(This->node->name);
    CharUpperBuffW(*p, SysStringLen(*p));

    TRACE("returning %s\n", debugstr_w(*p));

    return S_OK;
}