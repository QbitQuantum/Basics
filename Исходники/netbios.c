BOOL IsNetBiosInstalled(void)
    {
    unsigned int wNBRetCode;
    NCB ncbTest;
    DWORD dwHandler;

    /* Make sure interrupt vector 5C is not NULL */
    dwHandler = (DWORD)(_dos_getvect(NB_INTERRUPT));
    if ((dwHandler == 0) || (dwHandler >= 0xF0000000))
	return FALSE;

    /* Issue an invalid command, expecting a meaningful error code */
    memset(&ncbTest, 0, sizeof(NCB));
    ncbTest.ncb_command = 0xFF;
    wNBRetCode = NetBios(&ncbTest);

    switch (wNBRetCode)
	{
	case NRC_ILLCMD:
	/* case NB_ERR_BAD_ADAPTER: (?) */
	    return TRUE;

	default:
	    /* Return codes 0x40 to 0x4F mean "Unusual network condition"
			    0x50 to 0xFE mean "Adapter malfunction"
		These mean NetBIOS is there */
	    if ((wNBRetCode >= 0x40) && (wNBRetCode <= 0xFE))
		return TRUE;
	    else
		return FALSE;
	}
    }