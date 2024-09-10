 IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv)
 {
     static const QITAB qit[] =
     {
         QITABENT(CPlaylistCreator, INamespaceWalkCB),
         QITABENT(CPlaylistCreator, INamespaceWalkCB2),
         { 0 },
     };
     return QISearch(this, qit, riid, ppv);
 }