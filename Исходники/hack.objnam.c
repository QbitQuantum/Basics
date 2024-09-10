static char *
sitoa(int a)
{
	static char buf[13];

	Sprintf(buf, (a < 0) ? "%d" : "+%d", a);
	return (buf);
}