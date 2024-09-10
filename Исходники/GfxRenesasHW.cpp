STDMETHODIMP CGfxRenesasHW::SetSrcRect(const RECT *pRect)
{
    if(EqualRect(pRect,&m_rectSrc))
        return S_OK;
    m_rectSrc = *pRect;

    return S_OK;
}