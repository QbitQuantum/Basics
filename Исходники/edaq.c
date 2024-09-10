void SendID()
{
	unsigned char *s;

	s="EduDAQ (c) 02/05/2009 www.noise.physx.u-szeged.hu";
	do
	{
		if (SIn()==27) break;
		SOut(*s);
		if (*s) s++;
	} while (*s);
}