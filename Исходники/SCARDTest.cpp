void testGetATR(SCARDHANDLE* phCard)
{
	BYTE pbAtr[36];
	DWORD dwLen = 36;
	DWORD retval;

	retval = SCardGetAttrib(*phCard, SCARD_ATTR_ATR_STRING, pbAtr, &dwLen);

	printf ("trying to get the card's ATR by calling SCardGetAttrib\n");
	printf ("returned: ATR length = %d retval: 0x%08x\n",dwLen, retval);
	printf ("ATR = ");
	for(int i = 0; i < dwLen; i++)
	{
		printf(" 0x%02x",pbAtr[i]);
	}
	printf ("\n");

}