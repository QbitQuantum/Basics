void SendID()
{
	unsigned char *s;

	s="MA-DAQ (c) 11/11/2011 www.inf.u-szeged.hu/noise";
	do
	{
		if (SIn()==27) break;
		SOut(*s);
		if (*s) s++;
	} while (*s);
}