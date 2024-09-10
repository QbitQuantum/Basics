HRESULT STDMETHODCALLTYPE CIEHtmlElement::put_id(BSTR v)
{
    nsCOMPtr<nsIDOMHTMLElement> domHtmlElmt = do_QueryInterface(mDOMNode);
    if (!domHtmlElmt)
        return E_UNEXPECTED;
    USES_CONVERSION;
    nsDependentString strID(OLE2CW(v));
    if (FAILED(domHtmlElmt->SetId(strID)))
        return E_FAIL;
    return S_OK;
}