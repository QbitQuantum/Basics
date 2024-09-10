 // IUnknown
 IFACEMETHODIMP QueryInterface(REFIID riid, void ** ppv)
 {
     static const QITAB qit[] =
     {
         QITABENT(CFilterSample, IInitializeWithStream),
         QITABENT(CFilterSample, IFilter),
         {0, 0 },
     };
     return QISearch(this, qit, riid, ppv);
 }