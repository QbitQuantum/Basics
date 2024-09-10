STDMETHODIMP CMTDoubleVector::setValueVector(SAFEARRAY * pValues)
{

	VARTYPE varType;
	if( FAILED(SafeArrayGetVartype(pValues, &varType)) )
	{
		return Error( _T("setValueVector: Invalid result array") , __uuidof( IMTDoubleVector ), E_FAIL  );				
	}
	
	if( varType != VT_R8 )
	{
		return Error( _T("setValueVector: Invalid result array type.  Must be double") , __uuidof( IMTDoubleVector ), E_FAIL  );				
	}

	if( (pValues)->cDims != 1 )
	{
		return Error( _T("setValueVector: The array must have only one dimension") , __uuidof( IMTDoubleVector ), E_FAIL  );				
	}

	clear();	
	m_nbValues = pValues->rgsabound[0].cElements;	
	m_pValues = new double[m_nbValues];
	CopyMemory(m_pValues, pValues->pvData, sizeof(double)*m_nbValues);	
	
	updateListeners();
	return S_OK;
}