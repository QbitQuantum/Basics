unsigned __int64 COcsWmi::GetRefElementClassObjectU64Value(LPCTSTR lpstrRefElement, LPCTSTR lpstrProperty)

{

	try

	{

		CComBSTR elementName = CComBSTR( lpstrRefElement);

		CComBSTR propName = CComBSTR( lpstrProperty);

		CString	csObject;

		VARIANT pVal;
		VariantInit(&pVal);

		CIMTYPE pType;

		IWbemClassObject *pClassObject;

		static unsigned __int64 u64Result;



		if (!m_pClassObject)

		{

			return 0;

		}



		VariantClear(&pVal);

		m_hResult = m_pClassObject->Get( BSTR( elementName), 0L, &pVal, &pType, NULL);

		if (FAILED( m_hResult))

			return 0;

		csObject = strCimValue( pVal, pType);

		if (csObject.IsEmpty())

			return 0;

		m_hResult = m_pIWbemServices->GetObject( CComBSTR( csObject),

												WBEM_FLAG_RETURN_WBEM_COMPLETE,

												NULL,

												&pClassObject,

												NULL);

		if (FAILED( m_hResult))

		{

			pClassObject->Release();

			return 0;

		}

		VariantClear(&pVal);

		m_hResult = pClassObject->Get( BSTR( propName), 0L, &pVal, &pType, NULL);

		if (FAILED( m_hResult))

			u64Result = 0;

		else

			u64Result = u64CimValue( pVal, pType);

		pClassObject->Release();

		return u64Result;

	}

	catch (CException *pEx)

	{

		pEx->Delete();

		m_hResult = WBEM_E_FAILED;

		return 0;

	}

}