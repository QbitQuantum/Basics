void ImportDotXSI()
{

	CComPtr<XSIApplication>						l_pApplication;
	CLSID	lclsid;
	CLSIDFromProgID(L"XSI.Application", &lclsid );
	CoCreateInstance(lclsid, NULL, CLSCTX_INPROC, IID_XSIApplication, (void **)&l_pApplication);

	_variant_t args;  
	_variant_t v;  
	long l = 0 ;

	SAFEARRAY* psa = NULL;  
 
	const int cntArgs = 1 ;

	psa = ::SafeArrayCreateVector( VT_VARIANT, 0, cntArgs );  
 
	args.vt = VT_VARIANT | VT_ARRAY;  
	args.parray = psa;
 
	v = _bstr_t ( "c:\\__tmp.xsi" );
 
	SafeArrayPutElement(psa, &l, &v);  
	l++;  
 
	// more args?
	//

	VARIANT	l_vOutValue;
	l_pApplication->ExecuteScriptCommand( _bstr_t( L"SIImportDotXSIFile" ), args, &l_vOutValue ) ;


}