static char *tstring(time_t t)
{
	static pstring buf;
	pstrcpy(buf, asctime(LocalTime(&t)));
	all_string_sub(buf," ","&nbsp;",sizeof(buf));
	return buf;
}