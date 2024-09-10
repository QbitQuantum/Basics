integer s_wsue(cilist *a)
{
	int n;
	if(!f__init) f_init();
	if(n=c_sue(a)) return(n);
	f__reading=0;
	f__reclen=0;
	if(f__curunit->uwrt != 1 && f__nowwriting(f__curunit))
		err(a->cierr, errno, "write start");
	f__recloc=FTELL(f__cf);
	FSEEK(f__cf,(OFF_T)sizeof(uiolen),SEEK_CUR);
	return(0);
}