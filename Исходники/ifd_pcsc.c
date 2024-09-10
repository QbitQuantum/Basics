static int32_t pcsc_do_api(struct s_reader *pcsc_reader, const uchar *buf, uchar *cta_res, uint16_t *cta_lr, int32_t l)
{
	LONG rv;
	DWORD dwSendLength, dwRecvLength;

	*cta_lr = 0;
	if(!l)
	{
		rdr_log(pcsc_reader, "ERROR: Data length to be send to the pcsc_reader is %d", l);
		return ERROR;
	}

	char tmp[l * 3];
	dwRecvLength = CTA_RES_LEN;

	struct pcsc_data *crdr_data = pcsc_reader->crdr_data;
	if(crdr_data->dwActiveProtocol == SCARD_PROTOCOL_T0)
	{
		//  explanantion as to why we do the test on buf[4] :
		// Issuing a command without exchanging data :
		//To issue a command to the card that does not involve the exchange of data (either sent or received), the send and receive buffers must be formatted as follows.
		//The pbSendBuffer buffer must contain the CLA, INS, P1, and P2 values for the T=0 operation. The P3 value is not sent. (This is to differentiate the header from the case where 256 bytes are expected to be returned.)
		//The cbSendLength parameter must be set to four, the size of the T=0 header information (CLA, INS, P1, and P2).
		//The pbRecvBuffer will receive the SW1 and SW2 status codes from the operation.
		//The pcbRecvLength should be at least two and will be set to two upon return.
		if(buf[4])
			{ dwSendLength = l; }
		else
			{ dwSendLength = l - 1; }
		rdr_log_dbg(pcsc_reader, D_DEVICE, "sending %lu bytes to PCSC : %s", (unsigned long)dwSendLength, cs_hexdump(1, buf, l, tmp, sizeof(tmp)));
		rv = SCardTransmit(crdr_data->hCard, SCARD_PCI_T0, (LPCBYTE) buf, dwSendLength, NULL, (LPBYTE) cta_res, (LPDWORD) &dwRecvLength);
		*cta_lr = dwRecvLength;
	}
	else  if(crdr_data->dwActiveProtocol == SCARD_PROTOCOL_T1)
	{
		dwSendLength = l;
		rdr_log_dbg(pcsc_reader, D_DEVICE, "sending %lu bytes to PCSC : %s", (unsigned long)dwSendLength, cs_hexdump(1, buf, l, tmp, sizeof(tmp)));
		rv = SCardTransmit(crdr_data->hCard, SCARD_PCI_T1, (LPCBYTE) buf, dwSendLength, NULL, (LPBYTE) cta_res, (LPDWORD) &dwRecvLength);
		*cta_lr = dwRecvLength;
	}
	else
	{
		rdr_log_dbg(pcsc_reader, D_DEVICE, "PCSC invalid protocol (T=%lu)", (unsigned long)crdr_data->dwActiveProtocol);
		return ERROR;
	}

	rdr_log_dbg(pcsc_reader, D_DEVICE, "received %d bytes from PCSC with rv=%lx : %s", *cta_lr, (unsigned long)rv, cs_hexdump(1, cta_res, *cta_lr, tmp, sizeof(tmp)));

	rdr_log_dbg(pcsc_reader, D_DEVICE, "PCSC doapi (%lx ) (T=%d), %d", (unsigned long)rv, (crdr_data->dwActiveProtocol == SCARD_PROTOCOL_T0 ? 0 :  1), *cta_lr);

	if(rv  == SCARD_S_SUCCESS)
	{
		return OK;
	}
	else
	{
		return ERROR;
	}

}