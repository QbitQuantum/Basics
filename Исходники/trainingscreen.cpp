 static
 HRESULT KillStandaloneGame (void)
 {
     HRESULT hr = S_OK;
     m_spAdminGamesPtr = 0;
     if (m_spAdminGamePtr)
     {
         if (CoIsHandlerConnected (m_spAdminGamePtr))
             hr = m_spAdminGamePtr->Kill ();
         m_spAdminGamePtr = 0;
     }
     return hr;
 }