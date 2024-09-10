int setPLC_para(const char *abuf, int addr)
{
	unsigned char ebuf[32];
	int len, ret;

	if (abuf == NULL)
		return 0;

	memset(ebuf, 0, sizeof(ebuf));

	if (addr == OFFSET_PLC_MAC) {
		len = ETHER_ADDR_LEN;
		if (!isValidPara(abuf, len))
			return 0;

		ret = ether_atoe(abuf, ebuf);
	} else if (addr == OFFSET_PLC_NMK) {
		len = PLC_KEY_LEN;
		if (!isValidPara(abuf, len))
			return 0;

		ret = key_atoe(abuf, ebuf);
	} else
		return 0;

	if (ret) {
		FWrite(ebuf, addr, len);
		getPLC_para(addr);
		return 1;
	}
	else
		return 0;
}