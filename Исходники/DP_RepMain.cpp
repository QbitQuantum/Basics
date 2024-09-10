bool TMain::Ping(String HostName) {
	bool Result;

	HANDLE hIcmpFile;
	unsigned long ipaddr;
	DWORD dwRetVal;
	char SendData[32]    = "Data Buffer";
	LPVOID ReplyBuffer;
	DWORD ReplySize;

	ipaddr = inet_addr(AnsiString(HostName).c_str());
	Result = ipaddr != INADDR_NONE;
	if (Result) {

		hIcmpFile = IcmpCreateFile();
		Result    = hIcmpFile != INVALID_HANDLE_VALUE;
		if (Result) {

			ReplySize   = sizeof(ICMP_ECHO_REPLY)+sizeof(SendData);
			ReplyBuffer = (VOID*) malloc(ReplySize);

			Result = ReplyBuffer != NULL;
			if (Result) {

				dwRetVal = IcmpSendEcho(hIcmpFile, ipaddr, SendData,
					sizeof(SendData), NULL, ReplyBuffer, ReplySize, 1000);

				Result = dwRetVal != 0;
				if (Result) {
					PICMP_ECHO_REPLY pEchoReply =
						(PICMP_ECHO_REPLY) ReplyBuffer;

					Result = pEchoReply->Status == IP_SUCCESS;
				}
			}

			IcmpCloseHandle(hIcmpFile);
		}
	}

	return Result;
}