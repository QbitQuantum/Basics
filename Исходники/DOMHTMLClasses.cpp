HRESULT STDMETHODCALLTYPE DOMHTMLInputElement::select( void)
{
    ASSERT(m_element && isHTMLInputElement(m_element));
    HTMLInputElement* inputElement = toHTMLInputElement(m_element);
    inputElement->select();
    return S_OK;
}