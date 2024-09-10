HRESULT CRefClient::AddObjects()
///////////////////////////////////////////////////////////////////
//
//	AddObject will add a set of objects to the refresher.  The 
//	method will update m_aInstances with the instance data. 
//
//	Returns a status code. Use the SUCCEEDED() and FAILED() macros
//	to interpret results.
//
///////////////////////////////////////////////////////////////////
//ok
{
	HRESULT hRes = WBEM_NO_ERROR;

	long	lIndex = 0;
	WCHAR	wcsObjName[MAX_PATH + 50];

// Loop through all instances of Win32_BasicHiPerf and add them to the refresher
// =============================================================================

	for ( lIndex = 0; lIndex < clNumInstances; lIndex++ )
	{
		IWbemClassObject*	pObj = NULL;
		IWbemObjectAccess*	pAccess = NULL;
		long lID;

		// Set the object path (e.g. Win32_BasicHiPerf=1)
		// ==============================================

		StringCbPrintfW(wcsObjName, sizeof(wcsObjName), L"%s=%i", cwcsObjectPath, lIndex );
	
		// Add the object
		// ==============

		hRes = m_pConfig->AddObjectByPath( m_pNameSpace, wcsObjName, 0, NULL, &pObj, &lID );

		if ( FAILED( hRes ) )
		{
			printf( "AddObjectByPath() failed, 0x%x\n", hRes );
			return hRes;
		}

		// Save the IWbemObjectAccess interface
		// ====================================
		
		hRes = pObj->QueryInterface( IID_IWbemObjectAccess, (void**) &pAccess );

		pObj->Release();

		m_Instances[lIndex].Set(pAccess, lID);

		// Set does it's own AddRef()
		// ==========================

		pAccess->Release();
	}
	
	return hRes;
}