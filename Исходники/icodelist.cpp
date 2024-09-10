// GetItemText --------------------------------------------------------------
STDMETHODIMP CICodeList::GetItemText( long ItemIndex, BSTR* pstrVal )
{
   ASSERT( m_pCtrl != NULL && ::IsWindow( m_pCtrl->m_hWnd ) );
   if( !::IsWindow( m_pCtrl->GetSafeHwnd() ) )
      return E_POINTER;

   CHECK_PTR( pstrVal );
   int iLen = m_pCtrl->GetItemText( ItemIndex, NULL, 0 );
   LPTSTR pszText = new TCHAR[ iLen + 1 ];

   if( NULL == pszText )
      return E_OUTOFMEMORY;

   ZeroMemory( pszText, sizeof(TCHAR) * (iLen + 1) );
   m_pCtrl->GetItemText( ItemIndex, pszText, iLen );

   USES_CONVERSION;
   *pstrVal = T2BSTR( pszText );

   delete [] pszText;

   return S_OK;
}