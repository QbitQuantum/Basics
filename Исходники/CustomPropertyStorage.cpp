bool CustomPropertyStorage::DoesPropertyExist(const CStdString sName) const
{
	if(sName.IsEmpty())
	{
		LOG_WS_ERROR(_T("we have been passed an empty custom document property."));
		return false;
	}

	try
	{
		USES_CONVERSION;
		HRESULT hr = S_OK;
		IPropertySetStoragePtr pPropSetStg	 = NULL;
		IPropertyStoragePtr pPropStg		 = NULL;		

		hr = StgOpenStorageEx( CStdStringW(m_sFileName.c_str()),
			 STGM_READ|STGM_SHARE_DENY_WRITE,
			 STGFMT_ANY,
			 0, NULL, NULL, 
			 IID_IPropertySetStorage,
			 reinterpret_cast<void**>(&pPropSetStg) );
		if( FAILED(hr) || (pPropSetStg == NULL)) 
		{
			LOG_WS_ERROR(_T("Failed StgOpenStorageEx"));
			return false;
		}


		hr = pPropSetStg->Open(FMTID_UserDefinedProperties, STGM_READ|STGM_SHARE_EXCLUSIVE, &pPropStg );
		if( FAILED(hr) || (pPropStg == NULL)) 
		{
			LOG_WS_ERROR(_T("Failed StgOpenStorageEx"));
			return false;
		}

		PROPVARIANT propvar;
		PropVariantInit(&propvar);
		PROPSPEC propspec;
		ZeroMemory(&propspec, sizeof(PROPSPEC));

		PropVariantInit( &propvar );
		propspec.ulKind = PRSPEC_LPWSTR;
		propspec.lpwstr = T2W((LPTSTR)sName.c_str());

		hr = pPropStg->ReadMultiple( 1, &propspec, &propvar );
		if( FAILED(hr) ) 
		{
			LOG_WS_ERROR(_T("Failed to ReadMultiple."));
			return false;
		}

		CStdString sValue = ComConvertUtils::PropVariantToString(propvar);

		if(sValue.IsEmpty())
			return false;
		return true;

	}
	catch(...)
	{
		CStdString sError;
		sError.Format(_T("Unexpected error while determining %s property exists ") , sName.c_str() );
		LOG_WS_ERROR(sError);
		return false;
	}
	return false;
}