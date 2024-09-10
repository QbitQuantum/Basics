HRESULT CetfarduinoAin::SetDaqHwInfo() {
	// ----------------------------------
	// Set allowed InputRanges
	// ----------------------------------
	// The SAFEARRAYBOUND is used to create a multi dimensional array    
	SAFEARRAYBOUND rgsabound[2];  //the number of dimensions
    rgsabound[0].lLbound = 0;
	rgsabound[0].cElements = _validInputRanges.size(); // bipolar and unipolar - size of dimension 1
    rgsabound[1].lLbound = 0;
    rgsabound[1].cElements = 2;     // upper and lower range values - size of dimension 2
	
    SAFEARRAY* ps = SafeArrayCreate(VT_R8, 2, rgsabound); //use the SafeArrayBound to create the array
    if (ps == NULL) 
		throw "Failure to create SafeArray.";
	
	CComVariant vinrange;
    vinrange.parray = ps;
    vinrange.vt = VT_ARRAY | VT_R8;
    double *inRange, *min, *max;
    HRESULT hr = SafeArrayAccessData(ps, (void**)&inRange);
    if (FAILED(hr)) 
    {
        SafeArrayDestroy(ps);
        throw "Failure to access SafeArray data.";
    }       
	min = inRange;
	max = inRange + _validInputRanges.size();
	
	// Iterate through the validRanges, and transfer the Input Ranges.
	for (RangeList::iterator it = _validInputRanges.begin(); it != _validInputRanges.end(); ++it) {
		*min++ = it->minVal;
		*max++ = it->maxVal;
	}
    SafeArrayUnaccessData(ps);
    RETURN_HRESULT(_DaqHwInfo->put_MemberValue(CComBSTR(L"inputranges"), vinrange));

	// Polarity
	// Za sad je predvidjeno samo Unipolarni polaritet...
	RETURN_HRESULT(_DaqHwInfo->put_MemberValue(CComBSTR(L"polarity"), CComVariant(L"Unipolar")));

	// Description
	char driverDescrip[] = "Etf Arduino Driver: Analog Input";
	RETURN_HRESULT(_DaqHwInfo->put_MemberValue(CComBSTR(L"vendordriverdescription"), CComVariant(driverDescrip)));

	return S_OK;
}