int fwriteTIMEOUT1(PCStr(b),int s,int n,FILE *fp)
{	int rc;

	fRETURN_ONTIMEOUT(fp,0);
	rc = Fwrite(b,s,n,fp);
	DONE_SUCCESSFULLY();
	return rc;
}