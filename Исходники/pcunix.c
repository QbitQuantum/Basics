char *
getdate()
{
	static char datestr[7];
	register struct tm *lt = getlt();

	Sprintf(datestr, "%2d%2d%2d",
		lt->tm_year, lt->tm_mon + 1, lt->tm_mday);
	if(datestr[2] == ' ') datestr[2] = '0';
	if(datestr[4] == ' ') datestr[4] = '0';
	return(datestr);
}