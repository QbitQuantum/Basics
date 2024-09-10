String TimeStampString()
{
 	struct tm timeinfo;
	time_t rawtime;

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	char time_str[256];
	asctime_s(time_str, sizeof(time_str), &timeinfo);

	// chop of \n
	size_t len = strlen(time_str);
	time_str[len-1] = 0;

	return time_str;
}