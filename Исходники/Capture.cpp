STDMETHODIMP CaptureManager::CaptureEngineCB::QueryInterface(REFIID riid, void** ppv)
{
    static const QITAB qit[] = 
    {
        QITABENT(CaptureEngineCB, IMFCaptureEngineOnEventCallback),
        { 0 }
    };
    return QISearch(this, qit, riid, ppv);
}      