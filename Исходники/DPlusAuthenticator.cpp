bool CDPlusAuthenticator::poll(const wxString& callsign, const wxString& hostname, unsigned int port, unsigned char id)
{
	CUDPReaderWriter socket(m_address, 0U);
	bool ret = socket.open();
	if (!ret)
		return false;

	unsigned char buffer[56U];
	::memset(buffer, ' ', 56U);

	buffer[0U] = 0x38U;
	buffer[1U] = 0x20U;
	buffer[2U] = 0x01U;
	buffer[3U] = 0x01U;

	for (unsigned int i = 0U; i < callsign.Len(); i++)
		buffer[i + 4U] = callsign.GetChar(i);

	buffer[12U] = 'D';
	buffer[13U] = 'V';
	buffer[14U] = '0';
	buffer[15U] = '1';
	buffer[16U] = '9';
	buffer[17U] = '9';
	buffer[18U] = '9';
	buffer[19U] = '9';

	for (unsigned int i = 0U; i < callsign.Len(); i++)
		buffer[i + 20U] = callsign.GetChar(i);

	buffer[28U] = 'W';
	buffer[29U] = 'X';
	buffer[30U] = 'I';
	buffer[31U] = 'B';
	buffer[32U] = id;

	buffer[40U] = 'D';
	buffer[41U] = 'H';
	buffer[42U] = 'S';
	buffer[43U] = '0';
	buffer[44U] = '2';
	buffer[45U] = '5';
	buffer[46U] = '7';

	in_addr address = socket.lookup(hostname);
	if (address.s_addr == INADDR_NONE) {
		socket.close();
		return false;
	}

	ret = socket.write(buffer, 56U, address, port);

	socket.close();

	return ret;
}