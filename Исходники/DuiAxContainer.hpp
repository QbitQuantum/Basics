 // IOleInPlaceSiteEx
 STDMETHOD(OnInPlaceActivateEx)(BOOL *pfNoRedraw, DWORD dwFlags)
 {
     HRESULT hr = S_FALSE;
     OleLockRunning(m_spOleObject, TRUE, FALSE);
     if (pfNoRedraw) {
         *pfNoRedraw = FALSE;
     }
     if ((dwFlags & ACTIVATE_WINDOWLESS) != 0) {
         if ( m_spOleObjectWindowless != NULL ) {
             m_bInplaceActive = true;
             hr = S_OK;
         }
     } else {
         // object is not windowless, ensure we won't dispatch message to this control
         m_bInplaceActive = false;
     }
     return hr;
 }