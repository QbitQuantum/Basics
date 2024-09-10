static HRESULT WINAPI HTMLElementCollection_tags(IHTMLElementCollection *iface,
                                                 VARIANT tagName, IDispatch **pdisp)
{
    HTMLElementCollection *This = impl_from_IHTMLElementCollection(iface);
    DWORD i;
    nsAString tag_str;
    const PRUnichar *tag;
    elem_vector_t buf = {NULL, 0, 8};

    if(V_VT(&tagName) != VT_BSTR) {
        WARN("Invalid arg\n");
        return DISP_E_MEMBERNOTFOUND;
    }

    TRACE("(%p)->(%s %p)\n", This, debugstr_w(V_BSTR(&tagName)), pdisp);

    buf.buf = heap_alloc(buf.size*sizeof(HTMLElement*));

    nsAString_Init(&tag_str, NULL);

    for(i=0; i<This->len; i++) {
        if(!This->elems[i]->nselem)
            continue;

        nsIDOMHTMLElement_GetTagName(This->elems[i]->nselem, &tag_str);
        nsAString_GetData(&tag_str, &tag);

        if(CompareStringW(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, tag, -1,
                          V_BSTR(&tagName), -1) == CSTR_EQUAL) {
            node_addref(&This->elems[i]->node);
            elem_vector_add(&buf, This->elems[i]);
        }
    }

    nsAString_Finish(&tag_str);
    elem_vector_normalize(&buf);

    TRACE("fount %d tags\n", buf.len);

    *pdisp = (IDispatch*)HTMLElementCollection_Create(buf.buf, buf.len);
    return S_OK;
}