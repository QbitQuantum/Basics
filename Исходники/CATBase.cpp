// -----------------------------------------------------------------------------
// CATBase::IsAscii(const char*,const unsigned int)
// -----------------------------------------------------------------------------
bool CATBase::IsAscii( const char* pInput, const unsigned int iLength )
{
	LOG_LOW_FUNC_ENTRY("CATBase::IsAscii");
	bool bRet = true;
	const char* pPoint = pInput;
	for( unsigned int i = 0 ; i < iLength ; i++)
	{
		if(	!__isascii(*pPoint) )
		{
			bRet = false;
			break;
		}
		pPoint++;
	}
	return bRet;
}