HRESULT STDMETHODCALLTYPE C[!output Safe_root]::InvokeCommand( 
   DWORD dwCommandID,
   BSTR /*location*/,
   VARIANT* /*pLocationContext*/,
   BSTR /*itemLocation*/,
   ULONG /*cItemIDs*/,
   ULONG* /*rgItemIDs*/)
{
   ATLTRACE2("%x InvokeCommand: dwCommandID = %d.\n", GetCurrentThreadId(), dwCommandID);

   // ToDo: Execute the context menu command specified by dwCommandID.

   return S_OK;
}