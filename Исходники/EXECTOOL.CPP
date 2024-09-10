// =====================
	void dbout(void)
// =====================
{
char tmp[2000];
char mtime[100];
FILE  *fp;

	_strtime(mtime);

	sprintf(tmp,"%s: %s",mtime,dbuf);
	printf(dbuf);

	if (gdebug)
	{
		fp=fopen(glogfile,"at");
		if (!fp)
		{
		    printf("!!Cannot open logfile <%s>!!\n",glogfile);
		}
		else
		{
		    fprintf(fp,tmp);
			fclose(fp);
		}
	}
	strcpy(dbuf,"");
	return;
}