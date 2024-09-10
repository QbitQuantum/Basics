void getDefaultDevmodeC(char *printSetup, LPHANDLE phPrinter,  char **device)
{
	int		size,r1;

	size		= ((int*)printSetup)[0];
	printSetup	+=4;
	r1 = DocumentProperties(NULL,phPrinter,((char*)device)+4,
							(DEVMODE*)printSetup,NULL,DM_OUT_BUFFER);
	ClosePrinter(phPrinter);
}