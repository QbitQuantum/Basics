STDMETHODIMP CGraphElement::put_PointColor(OLE_COLOR newVal)
{

    HRESULT hr;
    COLORREF col;
    hr = OleTranslateColor(newVal, nullptr, &col);

    if(m_PointColor == col)
    {
        return S_FALSE;
    }

    m_PointColor = col;

    if(m_pCtrl)
    {
        m_pCtrl->Refresh(TRUE);
    }
    return S_OK;
}