HRESULT CScriptManager::GetItemTypeInfo( LPCTSTR pszItemName,
   ITypeInfo** ppTypeInfo )
{
   IProvideClassInfoPtr pProvideClassInfo;
   IDispatch* pDispatch;
   HRESULT hResult;
   BOOL tFound;

   ENSURE( pszItemName != NULL );
   ENSURE( ppTypeInfo != NULL );

   *ppTypeInfo = NULL;

   if( strcmp( pszItemName, "TCForm" ) == 0 )
   {
	  hResult = m_pDoc->GetTypeInfoOfGuid( GetUserDefaultLCID(),
		 __uuidof( Document ), ppTypeInfo );
	  if( SUCCEEDED( hResult ) )
	  {
		 return( S_OK );
	  }
   }
   else
   {
	  tFound = m_mapNamedItems.Lookup( pszItemName, pDispatch );
	  if( tFound )
	  {
		 pProvideClassInfo = pDispatch;
		 if( pProvideClassInfo != NULL )
		 {
			hResult = pProvideClassInfo->GetClassInfo( ppTypeInfo );
			if( SUCCEEDED( hResult ) )
			{
			   return( S_OK );
			}
		 }
	  }
   }

   return( TYPE_E_ELEMENTNOTFOUND );
}