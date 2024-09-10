 CSimpleWndHelper::~CSimpleWndHelper()
 {
     if(m_hHeap) HeapDestroy(m_hHeap);
     DeleteCriticalSection(&m_cs);
     if(m_atom) UnregisterClass((LPCTSTR)m_atom,m_hInst);
 }