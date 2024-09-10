bool CDExtraGatewayRepeaterProtocolHandler::writeText(const wxString& text, LINK_STATUS status, const wxString& reflector)
{
	unsigned char data[40U];

	data[0] = 'D';
	data[1] = 'S';
	data[2] = 'R';
	data[3] = 'P';

	data[4] = 0x00;

	::memset(data + 5U, ' ', 20U);

	for (unsigned int i = 0U; i < text.Length() && i < 20U; i++)
		data[i + 5U] = text.GetChar(i);

	data[25U] = (unsigned char)status;

	::memset(data + 26U, ' ', 8U);

	if (status != LS_NONE) {
		for (unsigned int i = 0U; i < reflector.Length() && i < 8U; i++)
			data[i + 26U] = reflector.GetChar(i);
	}

#if defined(DUMP_TX)
	CUtils::dump(wxT("Sending Text"), data, 34U);
	return true;
#else
	return m_socket.write(data, 34U);
#endif
}