int
clickmatch(File *f, int cl, int cr, int dir)
{
	int c;
	int nest = 1;

	while((c=(dir>0? Fgetc(f) : Fbgetc(f))) > 0)
		if(c == cr){
			if(--nest==0)
				return 1;
		}else if(c == cl)
			nest++;
	return cl=='\n' && nest==1;
}