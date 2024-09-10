int
Test_CardConnecting()
{
	int trycnt;
	long result;

	printf("==============================================================\n");
	printf("Part B : Card Connect/Disconnect\n");
	printf("==============================================================\n");
	trycnt = 0;
	printf("Testing");
	while(trycnt < 5)
	{
		trycnt++;
		printf("...");
#ifdef LINUX_OS
		fflush(stdout);
#endif
		result = SCardConnect(	 ScardContext,
							 ScardReaderState[CurrentReader].szReader,
							 SCARD_SHARE_EXCLUSIVE,
							 SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,
							 &ScardHandle[CurrentReader],
							 &ScardProtocol[CurrentReader]);

		if(result != SCARD_S_SUCCESS)
		{
			MyPrintf(strlen("Testing"), strlen("..."), trycnt * 2 - 1, "Failed\n");
			PRINTERR(("SCardConnect Fail : %08X\n", result));
			return FALSE;
		}
		
		printf("...");
#ifdef LINUX_OS
		fflush(stdout);
#endif
		result = SCardDisconnect(ScardHandle[CurrentReader],
										   SCARD_UNPOWER_CARD);

		if(result != SCARD_S_SUCCESS)
		{
			MyPrintf(strlen("Testing"), strlen("..."), trycnt * 2, "Failed\n");
			PRINTERR(("SCardDisconnect Fail : %08X\n", result));
			return FALSE;
		}
	}
	MyPrintf(strlen("Testing"), strlen("..."), trycnt * 2, "Passed\n");

	printf("\n                Part B Test Successfully\n\n");

	return TRUE;
}