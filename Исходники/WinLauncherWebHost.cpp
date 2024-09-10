 SimpleEventListener(LPWSTR type)
 {
     wcsncpy_s(m_eventType, 100, type, 100);
     m_eventType[99] = 0;
 }