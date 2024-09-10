int main (void)
{
	int argc;
	char **argv;
	char **envp;

		/* These variables are used by the WEL library */
	ghInstance = GetModuleHandle(NULL);
	eif_hInstance = GetModuleHandle(NULL);
	eif_hPrevInstance = NULL;
	eif_lpCmdLine = GetCommandLine();
	eif_nCmdShow = SW_SHOW;

		/* Initialization of the command line which is going to be passed to eiffel */
	get_argcargv (&argc, &argv);
		/* We get ANSI version of environment variables */
	envp = (char **) GetEnvironmentStringsA();

	eif_alloc_init();
#ifdef EIF_THREADS
	eif_thr_init_root();
#endif
	{
		GTCX
		struct ex_vect *exvect;
		jmp_buf exenv;
	
		egc_init_plug();
		initsig();
		initstk();
		exvect = exset((char *) 0, 0, (char *) 0);
		exvect->ex_jbuf = &exenv;
		if (setjmp(exenv))
			failure();
	
		eif_retrieve_root (&argc, argv);
		eif_rtinit(argc, argv, envp);
		eif_init_root();
		egc_rcdt_init();
		emain(argc, argv);
		free_argv (&argv);
		reclaim();
	}
	FreeEnvironmentStringsA ((LPSTR) envp);

	exit(0);
	return 0;
}