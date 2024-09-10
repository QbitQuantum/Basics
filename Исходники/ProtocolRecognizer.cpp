void cProtocolRecognizer::SendDisconnect(const AString & a_Reason)
{
	if (m_Protocol != nullptr)
	{
		m_Protocol->SendDisconnect(a_Reason);
	}
	else
	{
		// This is used when the client sends a server-ping, respond with the default packet:
		static const int Packet = 0xff;  // PACKET_DISCONNECT
		SendData((const char *)&Packet, 1);  // WriteByte()

		AString UTF16 = UTF8ToRawBEUTF16(a_Reason.c_str(), a_Reason.length());
		static const u_short Size = htons((u_short)(UTF16.size() / 2));
		SendData((const char *)&Size, 2);      // WriteShort()
		SendData(UTF16.data(), UTF16.size());  // WriteString()
	}
}