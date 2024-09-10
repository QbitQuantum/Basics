HRESULT
AsdkSheetSet::addCustomProperty(char* key,             // Property name
			  				    char* value,	       // Property value
								IAcSmComponent *pComp, // Component to add custom properties to
								PropertyFlags propertyFlag) // Property flag which specifies
														    // whether to inherit properties 
															// for all sheets in the sheet set
															// or to only apply at sheet set level
							   
{

	if(FAILED(isInitialized("addCustomProperty")))
		return E_FAIL;
		
	CComQIPtr<IAcSmComponent> pCmp;

	if (!pComp)
		// if null, create properties for sheet set
		pCmp = m_pSheetSet;
	else
		pCmp = pComp;

	// lock the the database first before doing any operation on it
    if (FAILED(LockDatabase()))
	{
		acutPrintf("\n Database lock failed!");
        return E_FAIL;
	}

	 // Add one custom property at the sheet set level
    CComPtr<IAcSmCustomPropertyBag> pBag = NULL;

    if(FAILED(pCmp->GetCustomPropertyBag(&pBag)))
    {
        acutPrintf("\nError: custom property bag.");
        return E_FAIL;
    }

    CComPtr<IAcSmCustomPropertyValue> pPropVal;
    if (FAILED(pPropVal.CoCreateInstance(L"AcSmComponents.AcSmCustomPropertyValue")))
    {
        acutPrintf("\nError: initializing custom property.");
        return E_POINTER;
    }

    if(FAILED(pPropVal->InitNew(pBag)))
    {
        acutPrintf("\nError: initializing custom property value.");
        return E_FAIL;
    }

	HRESULT hr;
    // set the property flag.
    if(FAILED(( hr = pPropVal->SetFlags((PropertyFlags)propertyFlag))))
    {
        acutPrintf("\nError: setting custom property flag.");
        return E_FAIL;
    } 

	// set the property name(key)
	CComBSTR propName(key);
    if(FAILED(pBag->SetProperty(propName, pPropVal)))
    {
        acutPrintf("\nError: attaching custom property to sheet set.");
        return E_FAIL;
    }

	// set the property value(for the key)
    CComVariant val(value);
    if(FAILED(pPropVal->SetValue(val)))
    {
        acutPrintf("\nError: setting custom property value.");
        return E_FAIL;
    }

	// Unlock database
	if (FAILED(UnlockDatabase())) 
	{
		acutPrintf("\n Cannot unlock database");
        return E_FAIL;
	}

	return S_OK;
}