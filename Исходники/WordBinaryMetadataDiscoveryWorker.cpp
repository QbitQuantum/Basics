void CWordBinaryMetadataDiscoveryWorker::DiscoverCustomProperties() 
{
	bool bNotFound;
	OpenPropertySet(FMTID_UserDefinedProperties, bNotFound);

	if(bNotFound)
	{
		ClosePropertySet();
		return;
	}

	if(NULL == m_pPropertyStg)
		throw Workshare::Exception(_T("NULL pointer encountered (m_pPropertyStg)"));

	IEnumSTATPROPSTG *pEnumProp;
	
	HRESULT hRes = m_pPropertyStg->Enum(&pEnumProp);
	if(FAILED(hRes))
	{
		ClosePropertySet();
		HandlePropertyError(_T(__FUNCTION__), _T("Enumerate user-defined properties failed"), hRes);
		return;
	}

	STATPROPSTG PropertyInformation;
	ZeroMemory(&PropertyInformation, sizeof(STATPROPSTG));
	PROPSPEC propSpec;
	PROPVARIANT propVar;

   CStdString exclusions = CMetawallGatewaySettings::GetCustomPropertiesExclusions();

	while(S_OK == pEnumProp->Next(1, &PropertyInformation, NULL))
	{
		PropVariantInit(&propVar);
		// Build a PROPSPEC for this property.
		ZeroMemory(&propSpec, sizeof(PROPSPEC));
		propSpec.ulKind = PRSPEC_PROPID;
		propSpec.propid = PropertyInformation.propid;

		// Read this property.
		hRes = m_pPropertyStg->ReadMultiple(1, &propSpec, &propVar);
		if(SUCCEEDED(hRes))
		{
			if(PropertyInformation.lpwstrName != 0 && !ShouldExcludeCustomProperty(exclusions, CStdString(PropertyInformation.lpwstrName)))
			{
				WordPropertyTypes WordPropertyType;
				if(IsWordInternalCustomProperty(PropertyInformation, propVar))
					WordPropertyType = BUILT_IN_PROPERTY;
				else
					WordPropertyType = CUSTOM_PROPERTY;
				CStdString sPropertyValue((LPCTSTR)PropVariantToString(propVar));
				PopulatePropertyLists(WordPropertyType, CStdString(PropertyInformation.lpwstrName), sPropertyValue);
			}
		}
		else
		{
			CStdString sErr;
			sErr.Format(_T("Failed to read property id: %d, error code: %d"), propSpec.propid, hRes);
			LOG_WS_ERROR(sErr);
		}
	}
	pEnumProp->Release();
	ClosePropertySet();
}