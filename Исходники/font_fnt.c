static int
READBYTE(FILEP fp, unsigned char *cp)
{
#ifdef HAVE_FNTGZ_SUPPORT
	unsigned char buf[1];

	if (FREAD(fp, buf, 1) != 1)
		return 0;
	*cp = buf[0];
#else
	int c;

	if ((c = getc(fp)) == EOF)
		return 0;
	*cp = (unsigned char)c;
#endif
	return 1;
}