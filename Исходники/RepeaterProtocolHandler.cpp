bool CRepeaterProtocolHandler::writePoll(const wxString& text)
{
	unsigned char buffer[40U];

	buffer[0] = 'D';
	buffer[1] = 'S';
	buffer[2] = 'R';
	buffer[3] = 'P';

	buffer[4] = 0x0A;				// Poll with text

	unsigned int length = text.Length();

	for (unsigned int i = 0U; i < length; i++)
		buffer[5U + i] = text.GetChar(i);

	buffer[5U + length] = 0x00;

#if defined(DUMP_TX)
	CUtils::dump(wxT("Sending Poll"), buffer, 6U + length);
	return true;
#else
	return m_socket.write(buffer, 6U + length);
#endif
}