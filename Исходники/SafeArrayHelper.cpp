///////////////////////////////////////////////////////////////////////////////
// Create : Creates a SafeArray object
bool CSafeArrayHelper::Create(VARTYPE  vt, UINT  cDims, UINT lBound, UINT cCount)
{
	Destroy();

	if (cDims == 1)	// this is somewhat faster...
		m_pSA = SafeArrayCreateVector(vt, lBound, cCount);
	else
	{
		SAFEARRAYBOUND rgsabound[1] = { 0 };
		rgsabound[0].lLbound = lBound;
		rgsabound[0].cElements = cCount;
		m_pSA = SafeArrayCreate(vt, cDims, rgsabound);
	}
	return (m_pSA != NULL);
}