/*--------------------------------------------------------------------------*/
void C2F(mtell) (int *fd, double *offset, int *err)
{     
	FILE *fa= GetFileOpenedInScilab(*fd);
	if ( fa == (FILE *) 0 ) 
	{
		char *filename = GetFileNameOpenedInScilab(*fd);
		if (filename)
		{
			sciprint(_("%s: Error while opening, reading or writing '%s'.\n"),"mtell",filename);
		}
		else
		{
			sciprint(_("%s: Error while opening, reading or writing.\n"),"mtell");
		}
		
		*err=1;
		return;
	}
	*err = 0;
	#ifdef _MSC_VER
		#if _WIN64 
			*offset = (double) _ftelli64(fa) ;
		#else
			*offset = (double) ftell(fa) ;
		#endif
	#else
	*offset = (double) ftell(fa) ;
	#endif
}