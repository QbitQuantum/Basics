// IUnknown
HRESULT STDMETHODCALLTYPE SumatraUIAutomationTextRange::QueryInterface(REFIID riid, void **ppv)
{
    static const QITAB qit[] = {
        QITABENT(SumatraUIAutomationTextRange, ITextRangeProvider),
        { 0 }
    };
    return QISearch(this, qit, riid, ppv);
}