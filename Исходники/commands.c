int system_main(int ac,const char *av[])
{	const char *nav[256]; /**/
	CStr(nab,0x10000);
	int nac,ai;

	if( File_is(av[1]) /* should search in PATH ... */ ){
		Execvp("system",av[1],&av[1]);
	}else{
		nac = decomp_args(nav,256,av[1],AVStr(nab));
		for( ai = 2; ai < ac; ai++ ){
			if( elnumof(nav)-1 <= nac)
				break;
			nav[nac++] = av[ai];
		}
		nav[nac] = 0;
		Execvp("system",nav[0],nav);
	}
	return 0;
}