int PackSetInfoGWQuick(char *pdubuf, char *mac, char *password, PKT_SET_INFO_GW_QUICK *setting, char *key, int klen)
{
	DWORD tid;
	char tmpbuf[INFO_PDU_LENGTH];
	
	tid = PackCmdHdr(tmpbuf, NET_CMD_ID_QUICKGW_EX, mac, password);

	memcpy(tmpbuf+sizeof(IBOX_COMM_PKT_HDR_EX), setting, sizeof(PKT_SET_INFO_GW_QUICK));

#ifdef ENCRYPTION
	Encrypt(klen, key, tmpbuf, INFO_PDU_LENGTH, pdubuf);
#else
	memcpy(pdubuf, tmpbuf, INFO_PDU_LENGTH);
#endif
	return (tid);
}