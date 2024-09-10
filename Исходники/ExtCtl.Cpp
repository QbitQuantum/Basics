HRESULT CExtendedControl::Init( REFCLSID clsidControl,
   CTestContainer98Item* pItem )
{
   HRESULT hResult;
   ITypeLibPtr pTypeLib;
   LPOLESTR pszModuleO;
   TCHAR szModule[MAX_PATH];
   CString strTLBPath;

   ASSERT( m_pItem != NULL );
   ASSERT( m_pControl == NULL );

   hResult = CoCreateInstance( clsidControl, (IUnknown*)this,
	  CLSCTX_INPROC_SERVER|CLSCTX_INPROC_HANDLER, IID_IUnknown, (void**)&m_pControl );
   if( FAILED( hResult ) )
   {
	  return( hResult );
   }

   m_pInnerDispatch = m_pControl;
   if( m_pInnerDispatch == NULL )
   {
	  return( E_NOINTERFACE );
   }
   Release();  // Artificially release because we QI'd the aggregate.

   GetModuleFileName( NULL, szModule, MAX_PATH );
   strTLBPath = szModule;
   strTLBPath += _T( "\\2" );  // Load the second TLB from the executable

   pszModuleO = strTLBPath.AllocSysString();
   hResult = LoadTypeLib( pszModuleO, &pTypeLib );
   if( FAILED( hResult ) )
   {
	  TCTrace( TRACELEVEL_NORMAL,
		 "Failed to load typelib for extended control\n" );
	  return( hResult );
   }

   hResult = pTypeLib->GetTypeInfoOfGuid( __uuidof( ITCExtendedControl ),
	  &m_pTypeInfo );
   if( FAILED( hResult ) )
   {
	  return( hResult );
   }

   m_pItem = pItem;
   m_pView = m_pItem->GetDocument()->GetView();

   return( S_OK );
}