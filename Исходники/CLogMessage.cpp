STDMETHODIMP CLogMessage::get_ReceivedDate(DATE* pVal)
{
TRY_CATCH
	SYSTEMTIME sysTime = static_cast<SYSTEMTIME>(m_receivedDate);
	SystemTimeToVariantTime(&sysTime,pVal);
	return S_OK;
CATCH_LOG_COMERROR()
}