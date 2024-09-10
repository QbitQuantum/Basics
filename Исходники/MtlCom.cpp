void CComSafeArray::Create(VARTYPE vtSrc, DWORD dwDims, SAFEARRAYBOUND *rgsabound)
{
	ATLASSERT(dwDims > 0);
	ATLASSERT(rgsabound != NULL);

	// Validate the VARTYPE for SafeArrayCreate call
	ATLASSERT( !(vtSrc & VT_ARRAY) );
	ATLASSERT( !(vtSrc & VT_BYREF) );
	ATLASSERT( !(vtSrc & VT_VECTOR) );
	ATLASSERT(vtSrc != VT_EMPTY);
	ATLASSERT(vtSrc != VT_NULL);

	// Free up old safe array if necessary
	Clear();

	ATLTRY( parray = ::SafeArrayCreate(vtSrc, dwDims, rgsabound) );

	if (parray == NULL) {
		ATLTRACE2(atlTraceDBProvider, 0, "CComSafeArray::Create Error : OOM\n");
		return;
	}

	vt				= unsigned short (vtSrc | VT_ARRAY);
	m_dwDims		= dwDims;
	m_dwElementSize = GetElemSize();
}