void CXTPCalendarCustomProperties::_Load(CXTPPropExchange* pPX)
{
	if (!pPX || !pPX->IsLoading())
	{
		ASSERT(FALSE);
		return;
	}
	m_mapProperties.RemoveAll();

	CXTPPropExchangeSection secProps(pPX->GetSection(_T("CustomProperties")));

	long nVersion;
	PX_Long(&secProps, _T("Version"), nVersion, XTP_CUSTOM_PROP_DATA_VER);

	if (nVersion != XTP_CUSTOM_PROP_DATA_VER)
	{
		TRACE(_T("ERROR! XTPCalendarCustomProperties: Unsupported data file version. (%d) \n"), nVersion);
		return;
	}

	CXTPPropExchangeEnumeratorPtr pEnumerator(secProps->GetEnumerator(_T("CustomProperty")));
	POSITION posStorage = pEnumerator->GetPosition();

	while (posStorage)
	{
		CString strName;
		COleVariant varValue;

		CXTPPropExchangeSection secProp(pEnumerator->GetNext(posStorage));
		PX_String(&secProp, _T("Name"), strName);
		PX_Variant(&secProp, _T("Value"), varValue, COleVariant((long)0));

		long lVt;
		PX_Long(&secProp, _T("VariantType"), lVt, VT_EMPTY);
		if (lVt != VT_EMPTY && varValue.vt != lVt)
		{
			LCID lcidID = pPX->m_lcidDateTime;
			if (lcidID == XTP_LOCALE_ISO8601)
			{
				lcidID = LOCALE_NEUTRAL;
			}
			COleVariant varValue2;

			HRESULT hr = VariantChangeTypeEx(&varValue2, &varValue,
										lcidID, 0, (VARTYPE)lVt);
			if (FAILED(hr))
			{
				hr = VariantChangeType(&varValue2, &varValue, 0, (VARTYPE)lVt);
			}
			if (FAILED(hr))
			{
				hr = VariantChangeType(&varValue2, &varValue, VARIANT_NOUSEROVERRIDE, (VARTYPE)lVt);
			}

			if (SUCCEEDED(hr))
			{
				varValue = varValue2;
			}
			else if (varValue.vt == VT_BSTR && (lVt == VT_R4 || lVt == VT_R8 || lVt == VT_DATE))
			{
				CString strValue = varValue.bstrVal;
				strValue.Replace(_T(','), _T('.'));
				double dblVal = atof(XTP_CT2CA(strValue));

				if (lVt == VT_R4)
				{
					varValue = (float)dblVal;
				}
				else if (lVt == VT_R8)
				{
					varValue = (double)dblVal;
				}
				else if (lVt == VT_DATE)
				{
					varValue = COleDateTime((DATE)dblVal);
				}
			}
			else
			{
				ASSERT(FALSE);
			}
		}

		SetProperty(strName, varValue);
	}
}