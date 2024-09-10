long CALLBACK NETsendPadData(void *pData, int Size) {
	if (PadSendSize == -1) {
		PadSendSize = Size;

		if (SEND(&PadSendSize, 1, PSE_NET_BLOCKING) == -1)
			return -1;

		if (RECV(&PadRecvSize, 1, PSE_NET_BLOCKING) == -1)
			return -1;
	}

	memcpy(&PadSendData[PadCount], pData, Size);
	if (SEND(pData, PadSendSize, PSE_NET_BLOCKING) == -1)
		return -1;

	return 0;
}