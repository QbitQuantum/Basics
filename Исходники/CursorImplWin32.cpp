 void CursorImplWin32::destroy()
 {
     if(m_handler)
     {
         DestroyCursor(m_handler);
         m_handler = nullptr;
     }
 }