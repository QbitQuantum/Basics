BOOL CUdpCast::CheckStarting()
{
	CCriSecLock locallock(m_csCheck);

	if(m_enState == SS_STOPPED)
	{
		m_enState = SS_STARTING;
		::_ReadWriteBarrier();
	}
	else
	{
		SetLastError(SE_ILLEGAL_STATE, __FUNCTION__, ERROR_INVALID_OPERATION);
		return FALSE;
	}

	return TRUE;
}