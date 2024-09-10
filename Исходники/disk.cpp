HRESULT CDisk::GetFormat(VARIANT *buf, DSK_FORMAT **bufout, unsigned length)
{
	long lBound, uBound;
	unsigned char HUGEP* FAR pData;
	SAFEARRAY *psa;
	HRESULT hr;
	unsigned n;
	DSK_FORMAT *fmt;

	if (V_VT(buf) != (VT_ARRAY | VT_UI1)) 
	{
		return Error("Passed parameter must be an array of unsigned characters", IID_IDisk, E_INVALIDARG);
	}
	psa = V_ARRAY(buf);
      // Check dimensions of the array.
	if (SafeArrayGetDim(psa) != 1)
	{
		return Error("Passed parameter must be a 1-dimensional array", IID_IDisk, E_INVALIDARG);
	}

	// Get array bounds.
	hr = SafeArrayGetLBound(psa, 1, &lBound);
	if (FAILED(hr))
	{
		return Error("Could not get array bounds", IID_IDisk, hr);
	}
	hr = SafeArrayGetUBound(psa, 1, &uBound);
	if (FAILED(hr))
	{
		return Error("Could not get array bounds", IID_IDisk, hr);
	}
	if (uBound + 1 - lBound < (long)length*4)
	{
		return Error("Passed array is too short", IID_IDisk, E_INVALIDARG);
	}
	// Get a pointer to the elements of the array.
	hr = SafeArrayAccessData(psa, (void HUGEP * FAR *)&pData);
	if (FAILED(hr))
	{
		return Error("Could not access array data", IID_IDisk, E_INVALIDARG);
	}
	*bufout = (DSK_FORMAT *)dsk_malloc(length * sizeof(DSK_FORMAT));
	if (!bufout) return MapError(DSK_ERR_NOMEM);
	fmt = bufout[0];
	for (n = 0; n < length; n++)
	{
		fmt->fmt_cylinder = *pData++;
		fmt->fmt_head     = *pData++;
		fmt->fmt_sector   = *pData++;
		fmt->fmt_secsize  = 128 << (*pData++);
		++fmt;
	}
	SafeArrayUnaccessData(psa);
	return S_OK;
}