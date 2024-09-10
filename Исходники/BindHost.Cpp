STDMETHODIMP CTCBindHost::MonikerBindToStorage( IMoniker* pMoniker,
   IBindCtx* pBindCtx, IBindStatusCallback* pBSC, REFIID iid, void** ppObject )
{
   HRESULT hResult;
   IBindCtxPtr pNewBindCtx;

   TCTrace( TRACELEVEL_NORMAL, "IBindHost::MonikerBindToStorage\n" );

   if( ppObject == NULL )
   {
	  return( E_POINTER );
   }
   *ppObject = NULL;

   if( pBindCtx != NULL )
   {
	  pNewBindCtx = pBindCtx;
	  if( pBSC )
	  {
		 hResult = RegisterBindStatusCallback( pBindCtx, pBSC, NULL, 0 );
		 if( FAILED( hResult ) )
		 {
			return( hResult );
		 }
	  }
   }
   else
   {
	  if( pBSC )
	  {
		 hResult = CreateAsyncBindCtx( 0, pBSC, NULL, &pNewBindCtx );
		 if( FAILED( hResult ) )
		 {
			return( hResult );
		 }
	  }
	  else
	  {
		 hResult = CreateBindCtx( 0, &pNewBindCtx );
		 if( FAILED( hResult ) )
		 {
			return( hResult );
		 }
	  }
   }
   ASSERT( pNewBindCtx != NULL );

   return( pMoniker->BindToStorage( pNewBindCtx, NULL, iid, ppObject ) );
}