HRESULT STDMETHODCALLTYPE CGlobalsX::get_ReplaceMRUList( BSTR __RPC_FAR *pstrMRUList )
{
   LPTSTR psz = new TCHAR[ CM_FIND_REPLACE_MRU_BUFF_SIZE + 1 ];
   CMGetFindReplaceMRUList( psz, FALSE );
   *pstrMRUList = T2BSTR( psz );
   delete [] psz;
   return S_OK;
}