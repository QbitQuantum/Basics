/////////////////////////////////////////////////////////////////////
// OPCBrowser::MoveTo method
STDMETHODIMP COPCBrowserImpl::MoveTo( SAFEARRAY ** ppBranches )
{
   if(*ppBranches == NULL)
      return E_INVALIDARG;

   // Clear out the list
   ClearNames();

   HRESULT hr = S_OK;
   LONG lBound=0;
   LONG uBound=0;
   // ServerHandles
   hr = SafeArrayGetLBound(*ppBranches, 1, &lBound);
   if( FAILED(hr) )
      return hr;
   hr = SafeArrayGetUBound(*ppBranches, 1, &uBound);
   if( FAILED(hr) )
      return hr;

   hr = MoveToRoot();
   if( FAILED(hr) )
      return hr;

   for( LONG index=lBound; index<=uBound; index++ )
   {
      BSTR Branch;
      hr = SafeArrayGetElement(*ppBranches, &index, &Branch);
      if( FAILED(hr) )
         return hr;
      if(*Branch != 0 )
      {
         hr = m_pOPCBrowser->ChangeBrowsePosition( OPC_BROWSE_DOWN, Branch );
         SysFreeString( Branch );
         if( FAILED(hr) )
            return hr;
      }
   }
   return hr;
}