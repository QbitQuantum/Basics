/*----------------------------------------------------------------------------*/
static int procMCRRead(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	P_GLUE_INFO_T prGlueInfo;
	PARAM_CUSTOM_MCR_RW_STRUC_T rMcrInfo;
	UINT_32 u4BufLen;
	char *p = page;
	UINT_32 u4Count;
	WLAN_STATUS rStatus = WLAN_STATUS_SUCCESS;


	ASSERT(data);

	/* Kevin: Apply PROC read method 1. */
	if (off != 0) {
		return 0;	/* To indicate end of file. */
	}

	prGlueInfo = (P_GLUE_INFO_T) netdev_priv((struct net_device *)data);

	rMcrInfo.u4McrOffset = u4McrOffset;

	rStatus = kalIoctl(prGlueInfo,
			   wlanoidQueryMcrRead,
			   (PVOID) & rMcrInfo, sizeof(rMcrInfo), TRUE, TRUE, TRUE, &u4BufLen);


	SPRINTF(p, ("MCR (0x%08lxh): 0x%08lx\n", rMcrInfo.u4McrOffset, rMcrInfo.u4McrData));

	u4Count = (UINT_32) (p - page);

	*eof = 1;

	return (int)u4Count;

}				/* end of procMCRRead() */