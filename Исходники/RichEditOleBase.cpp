//
// IOleObject methods
//
HRESULT RichEditOleBase::Advise(IAdviseSink *pAdvSink,DWORD *pdwConnection)
{
    HRESULT hr = S_OK;
    if (m_spOleAdviseHolder == NULL)
        hr = CreateOleAdviseHolder(&m_spOleAdviseHolder);
    if (SUCCEEDED(hr))
        hr = m_spOleAdviseHolder->Advise(pAdvSink, pdwConnection);
    return hr;
}