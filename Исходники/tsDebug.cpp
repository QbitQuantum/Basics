_tsTraceMethodExt &_tsTraceMethodExt::returnCOMMsg(HRESULT hr, tscrypto::tsCryptoString fmt, ...)
{
	tscrypto::tsCryptoString sHr;
	va_list args;

	switch (hr)
	{
	case S_OK: sHr = "OK"; break;
	case S_FALSE: sHr = "FALSE"; break;
	case E_NOTIMPL: sHr = "Not Implemented"; break;
	case E_UNEXPECTED: sHr = "Unexpected operation"; break;
	case E_OUTOFMEMORY: sHr = "Out Of Memory"; break;
	case E_INVALIDARG: sHr = "Invalid Argument"; break;
	case E_NOINTERFACE: sHr = "No Interface"; break;
	case E_POINTER: sHr = "Invalid Pointer"; break;
	case E_HANDLE: sHr = "Invalid Handle"; break;
	case E_ABORT: sHr = "Aborted"; break;
	case E_FAIL: sHr = "General Failure"; break;
	case E_ACCESSDENIED: sHr = "Access Denied"; break;
	case E_PENDING: sHr = ""; break;
	default:
		sHr.Format("0x%08X", hr);
		break;
	}
	setErrorTo(FAILED(hr) != FALSE);
	va_start(args, fmt);
	m_outMessage.clear();
	m_outMessage.resize(MAX_TRACE_MSG_LEN);
#ifdef HAVE__VSNPRINTF_S
	_vsnprintf_s(m_outMessage.rawData(), m_outMessage.size(), m_outMessage.size(), fmt.c_str(), args);
#elif defined(HAVE_VSNPRINTF)
	vsnprintf(m_outMessage.rawData(), m_outMessage.size(), fmt.c_str(), args);
#elif defined(HAVE_VSPRINTF_S)
	vsprintf_s(m_outMessage.rawData(), m_outMessage.size(), fmt.c_str(), args);
#elif defined(HAVE_VSPRINTF)
	vsprintf(m_outMessage.rawData(), fmt.c_str(), args);
#else
#error Implement me
#endif
	m_outMessage.resize((uint32_t)TsStrLen(m_outMessage.c_str()));
	m_outMessage.Replace("~~", sHr.c_str());
	returns(hr);
	return *this;
}