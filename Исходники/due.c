integer e_rdue(Void)
{
	if(f__curunit->url==1 || f__recpos==f__curunit->url)
		return(0);
	FSEEK(f__cf,(OFF_T)(f__curunit->url-f__recpos),SEEK_CUR);
	if(FTELL(f__cf)%f__curunit->url)
		err(f__elist->cierr,200,"syserr");
	return(0);
}