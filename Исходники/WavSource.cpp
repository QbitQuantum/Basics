HRESULT WavSource::QueryInterface(REFIID iid, void** ppv)
{
    static const QITAB qit[] = 
    {
        QITABENT(WavSource, IMFMediaEventGenerator),
        QITABENT(WavSource, IMFMediaSource),
        { 0 }
    };
    return QISearch(this, qit, iid, ppv);
}