int writemsg(FILE *fp, char * msgstr)
{
	char timestr[LOCAL_TIME_STR_LEN] = {0};
	getlocaltime(timestr);
	int ret = fprintf(fp, "%s %s", timestr, msgstr);
    return ret;
}