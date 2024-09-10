CDPlusHandler::CDPlusHandler(IReflectorCallback* handler, const wxString& repeater, const wxString& reflector, CDPlusProtocolHandler* protoHandler, const in_addr& address, unsigned int port) :
m_repeater(repeater),
m_callsign(m_dplusLogin),
m_reflector(reflector),
m_handler(protoHandler),
m_yourAddress(address),
m_yourPort(port),
m_myPort(0U),
m_direction(DIR_OUTGOING),
m_linkState(DPLUS_LINKING),
m_destination(handler),
m_time(),
m_pollTimer(1000U, 1U),			// 1s
m_pollInactivityTimer(1000U, 30U),
m_tryTimer(1000U, 1U),
m_tryCount(0U),
m_dPlusId(0x00U),
m_dPlusSeq(0x00U),
m_inactivityTimer(1000U, 2U),
m_header(NULL)
{
	wxASSERT(protoHandler != NULL);
	wxASSERT(handler != NULL);
	wxASSERT(port > 0U);

	m_myPort = protoHandler->getPort();

	m_pollInactivityTimer.start();
	m_tryTimer.start();

	m_time = ::time(NULL);

	wxChar band = repeater.GetChar(LONG_CALLSIGN_LENGTH - 1U);
	m_callsign.SetChar(LONG_CALLSIGN_LENGTH - 1U, band);
}