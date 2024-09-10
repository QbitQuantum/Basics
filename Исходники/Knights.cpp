void CKnights::ConstructChatPacket(Packet & data, const char * format, ...)
{
	char buffer[128];
	va_list ap;
	va_start(ap, format);
	vsnprintf(buffer, 128, format, ap);
	va_end(ap);

	data.Initialize(WIZ_CHAT);
	data  << uint8(KNIGHTS_CHAT)	// clan chat opcode
		  << uint8(1)				// nation
		  << int16(-1)				// session ID
		  << uint8(0)				// character name length
		  << buffer;				// chat message
}