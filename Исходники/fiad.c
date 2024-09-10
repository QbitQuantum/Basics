int	openfiad(char *filename, int *handle)
{
	struct  tifile *ff;
	char	path[80];
	char	dosname[14];
	char	fdrname[12];
	char	tiname[12];
	int	ti;
	struct	fdrstruc *fdr;


	_fmode=O_BINARY;

	if ((ti=*handle=getfreeti(0))!=-1)
	{
	ff=&tifiles[ti];
	fdr=&ff->fdr;

	if (split(filename,path,tiname))
	{
		memset(fdrname,0x20,10);
		memcpy(fdrname,tiname,strlen(tiname));
		ti2dos(tiname,dosname);
		strcat(path,dosname);
		if ((_dos_open(path,O_RDWR|O_BINARY,&ff->doshandle))==0)
		{
			if (read(ff->doshandle,fdr,128)==128)
			{
				noansi(fdr->name);
				if (memicmp(fdr,fdrname,10)==0 &&
				    ((fdr->flags&F_VARIABLE) ? fdr->reclen : 1))
				{
					tifiles[ti].inuse=1;
						Error=0;
						return 1;
				}
			}
			Error=NOTTIEMUL;
			close(ff->doshandle);
			return 0;
		}
		else
		{
			Error=BADFILE;
			close(ff->doshandle);
			return 0;
		}
	}
	}
	return 0;			// split sets Error
}