void GroupBase::doAsyncRefresh( const AsyncRequestListElem &request )
{
	IOPCDataCallback* callBack = NULL;
	HRESULT hResult = getCallback( IID_IOPCDataCallback, (IUnknown**)&callBack );

	if( FAILED( hResult ) )
		return;

	size_t counts = request->getCounts();

	if( counts == 0 ) // keep alive
	{
		OPCHANDLE pHandles = 0;
		VARIANT pValue;
		VariantInit( &pValue );
		WORD pQuality = 0;
		FILETIME  pTimeStamp;
		memset( &pTimeStamp, 0, sizeof( pTimeStamp ) );
		HRESULT pErrors = S_OK;

		callBack->OnDataChange(	request->getTransactionID(),
			clientHandle,
			S_OK,
			S_OK,
			0,
			&pHandles,
			&pValue,
			&pQuality,
			&pTimeStamp,
			&pErrors );
		callBack->Release();
		return;
	}

	OPCHANDLE *pHandles = NULL;
	VARIANT *pValue = NULL;
	WORD *pQuality = NULL;
	FILETIME *pTimeStamp = NULL;
	HRESULT *pErrors = NULL;

	pHandles = os::win32::com::allocMemory< OPCHANDLE >( counts );
	if( pHandles == NULL )
		return;

	pValue = os::win32::com::allocMemory< VARIANT >( counts );
	if( pValue == NULL )
	{
		os::win32::com::freeMemory( pHandles );
		return;
	}
	os::win32::com::zeroMemory( pValue, counts );

	pQuality = os::win32::com::allocMemory< WORD >( counts );
	if( pQuality == NULL )
	{
		os::win32::com::freeMemory( pHandles );
		os::win32::com::freeMemory( pValue );
		return;
	}

	pTimeStamp = os::win32::com::allocMemory< FILETIME >( counts );
	if( pTimeStamp == NULL )
	{
		os::win32::com::freeMemory( pHandles );
		os::win32::com::freeMemory( pValue );
		os::win32::com::freeMemory( pQuality );
		return;
	}

	pErrors = os::win32::com::allocMemory< HRESULT >( counts );
	if( pErrors == NULL )
	{
		os::win32::com::freeMemory( pHandles );
		os::win32::com::freeMemory( pValue );
		os::win32::com::freeMemory( pQuality );
		os::win32::com::freeMemory( pTimeStamp );
		return;
	}

	GroupItemElemList::iterator iter;
	GroupItemElemList::iterator groupIterEnd = itemList.end();
	
	const std::list< ItemHVQT >  *handles = &request->getItemHVQTList();
	size_t i = 0;	
	BOOST_FOREACH( const ItemHVQT& el, *handles )
	{
		iter = itemList.find( el.getHandle() );
		if( iter == groupIterEnd )
		{
			pErrors[i] = OPC_E_INVALIDHANDLE;
			continue;
		}
		pHandles[i] = iter->second->getClientHandle();
		try
		{
			if( request->getSource() == OPC_DS_CACHE )
				pErrors[i] = iter->second->getCachedValue().copyTo( pValue[i] );
			else
				pErrors[i] = iter->second->readValue().copyTo( pValue[i] );
		}
		catch( Tag::NotExistTag& )
		{
			pErrors[i] = OPC_E_INVALIDHANDLE;
		}

		if( FAILED( pErrors[i] ) )
			continue;

		pQuality[i] = iter->second->getQuality();
		pTimeStamp[i] = iter->second->getTimeStamp();
		++i;
	}

	callBack->OnDataChange(	request->getTransactionID(),
		clientHandle,
		S_OK,
		S_OK,
		(DWORD)counts,
		pHandles,
		pValue,
		pQuality,
		pTimeStamp,
		pErrors );
	callBack->Release();
	os::win32::com::freeMemory( pHandles );
	os::win32::com::freeMemory( pValue );
	os::win32::com::freeMemory( pQuality );
	os::win32::com::freeMemory( pTimeStamp );
	os::win32::com::freeMemory( pErrors );
}