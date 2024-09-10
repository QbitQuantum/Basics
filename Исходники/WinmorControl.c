VOID Poll()
{
	char Msg[256];
	int len;

	len = recvfrom(sock, Msg, 256, 0, &rx, &addrlen);

	if (len <= 0)
		return;

	Msg[len] = 0;

	if (_memicmp(Msg, "REMOTE:", 7) == 0)
		RestartTNC(&Msg[7]);

	if (_memicmp(Msg, "KILL ", 5) == 0)
		KillTNC(atoi(&Msg[5]));
	
}