/////////////////////////////////////////////////////////////////
// HRESULT CSession::GetSchemaRowset
//
/////////////////////////////////////////////////////////////////
HRESULT CSession::GetSchemaRowset(CAggregate* pCAggregate, REFGUID guidSchema, ULONG cRestrictions, VARIANT* rgRestrictions, REFIID riid, ULONG cPropSets, DBPROPSET* rgPropSets, IUnknown** ppIUnknown)
{
	HRESULT hr = S_OK;
	if(!m_pIDBSchemaRowset)
		return E_FAIL;
	
	//Schema Rowset
	WCHAR wszBuffer[MAX_NAME_LEN+1];
	WCHAR* pwszSchemaName = GetSchemaName(guidSchema);

	//Try to find the String Resprentation of the guidSchema
	if(pwszSchemaName == NULL)
	{
		StringFromGUID2(guidSchema, wszBuffer, MAX_NAME_LEN);
		pwszSchemaName = wszBuffer;
	}
	
	//GetSchema Rowset
	XTEST_(hr = m_pIDBSchemaRowset->GetRowset(
					pCAggregate,		// punkOuter
					guidSchema,			// schema IID
					cRestrictions,		// # of restrictions
					rgRestrictions,		// array of restrictions
					riid,				// rowset interface
					cPropSets,			// # of properties
					rgPropSets,			// properties
					ppIUnknown),S_OK);	// rowset pointer

	TRACE_METHOD(hr, L"IDBSchemaRowset::GetRowset(0x%p, %s, %d, 0x%p, %s, %d, 0x%p, &0x%p)", pCAggregate, pwszSchemaName, cRestrictions, rgRestrictions, GetInterfaceName(riid), cPropSets, rgPropSets, ppIUnknown ? *ppIUnknown : NULL);

	//Display Errors (if occurred)
	TESTC(hr = DisplayPropErrors(hr, cPropSets, rgPropSets));

	//Handle Aggregation
	if(pCAggregate)
		TESTC(hr = pCAggregate->HandleAggregation(riid, ppIUnknown));

CLEANUP:
	return hr;
}