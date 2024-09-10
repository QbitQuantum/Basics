static long sendAPDU(SCARDHANDLE hCard, const char *apdu,
	unsigned char *recvBuf, DWORD *recvBufLen,
	const char *chipNr, int idx, bool doDump)
{
	unsigned char sendBuf[280];
	size_t        sendBufLen = sizeof(sendBuf);

	// Hex string -> byte array
	if (0 == hex2bin(apdu, sendBuf, &sendBufLen))
	{
		// Check the APDU
		if (sendBufLen < 4)
		{
			printf("ERR: APDU should be at least 4 bytes\n");
			DebugMessage("ERR: APDU should be at least 4 bytes\n");
		}
		else if (sendBufLen > 5 && (5 + sendBuf[4] != sendBufLen))
		{
			printf("ERR: wrong P3 byte in case 3 APDU\n");
			DebugMessage("ERR: wrong P3 byte in case 3 APDU\n");
		}
		else
		{
			if (doDump)
				dumphex2("  - sending ", sendBuf, sendBufLen);

#if TRANSMIT_DEBUG
			long ret = SCardTransmit2(hCard, &g_rgSCardT0Pci, sendBuf, (DWORD) sendBufLen, NULL, recvBuf, recvBufLen);
#else
			long ret = SCardTransmit(hCard, &g_rgSCardT0Pci, sendBuf, (DWORD) sendBufLen, NULL, recvBuf, recvBufLen);
#endif
			CHECK_PCSC_RET("SCardTransmit", ret);

			if (SCARD_S_SUCCESS == ret)
			{
				if (doDump)
				{
					dumphex2("    received ", recvBuf, *recvBufLen);
					printf("\n");
					DebugMessage("\n");
				}

				if (NULL != chipNr)
					StoreAPDUs(chipNr, idx, sendBuf, sendBufLen, recvBuf, *recvBufLen);

				return 0; // success
			}
		}
	}

	return -1; // failed
}