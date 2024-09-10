UdpSession::UdpSession(IcqLink *link, const char *name, uint32 uin)
: IcqSession(link, name, uin)
{
	memset(&destAddr, 0, sizeof(destAddr));

	initSession();
}