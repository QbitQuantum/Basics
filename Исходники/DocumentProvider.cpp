HRESULT STDMETHODCALLTYPE SumatraUIAutomationDocumentProvider::QueryInterface(REFIID riid, void** ppv) {
    static const QITAB qit[] = {QITABENT(SumatraUIAutomationDocumentProvider, IRawElementProviderSimple),
                                QITABENT(SumatraUIAutomationDocumentProvider, IRawElementProviderFragment),
                                QITABENT(SumatraUIAutomationDocumentProvider, ITextProvider),
                                QITABENT(SumatraUIAutomationDocumentProvider, IAccIdentity),
                                {0}};
    return QISearch(this, qit, riid, ppv);
}