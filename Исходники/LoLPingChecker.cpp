void Refresh()
{
	*BUFFER = '\0';
	Ping[0].clear();
	hIcmpFile = IcmpCreateFile();
	ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(BUFFER);
	ReplyBuffer = static_cast<VOID*>(malloc(ReplySize));
	dwRetVal = IcmpSendEcho(hIcmpFile, EUW, BUFFER, sizeof(BUFFER), nullptr, ReplyBuffer, ReplySize, 1000);
	auto pEchoReply = static_cast<PICMP_ECHO_REPLY>(ReplyBuffer);
	Ping[0] << pEchoReply->RoundTripTime;
}