void DisplayFPStatusBits(char *tag)
{
	unsigned long status;

	status = _statusfp();
	if ((status != 0x00000000) && (status != 0x00000001))
	{
		if (tag != NULL)
			printf("%s ", tag);
		printf("FPU Status: %08.8X ( ", status);
		if (status & _SW_DENORMAL)
			printf("DENORMAL ");
		if (status & _SW_INVALID)
			printf("INVALID ");
		if (status & _SW_ZERODIVIDE)
			printf("DIV0 ");
		if (status & _SW_OVERFLOW)
			printf("OVERFLOW ");
		if (status & _SW_UNDERFLOW)
			printf("UNDERFLOW ");
		if (status & _SW_INEXACT)
			printf("INEXACT ");
		printf(")\n");
	}
}