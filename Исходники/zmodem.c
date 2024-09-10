static void show_sendbuf(PFileVar fv)
{
	char *s;

	s = sendbuf;
	strncat_s(sendbuf, sizeof(sendbuf), "\015\012", _TRUNCATE);
	_lwrite(fv->LogFile, s, strlen(s));

	memset(sendbuf, 0, sizeof(sendbuf));
}