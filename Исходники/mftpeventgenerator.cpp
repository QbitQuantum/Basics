STDMETHODIMP CMediaEventGenerator::InitMediaEventGenerator(
    void
    )
{
    
    return MFCreateEventQueue(&m_pQueue);

}