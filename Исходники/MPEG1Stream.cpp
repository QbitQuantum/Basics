HRESULT MPEG1Stream::QueryInterface(REFIID riid, void** ppv)
{
    static const QITAB qit[] = 
    {
        QITABENT(MPEG1Stream, IMFMediaEventGenerator),
        QITABENT(MPEG1Stream, IMFMediaStream),
        { 0 }
    };
    return QISearch(this, qit, riid, ppv);
}