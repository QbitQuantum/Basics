int
start_emulator(char* emu, char *start_prog, char** argv, int start_detached)
{
    int result;
    static char console_mode[] = "tty:ccc";
    char* fd_type;
    char* title;

#ifdef HARDDEBUG
    fprintf(stderr,"emu = %s, start_prog = %s\n",emu, start_prog);
#endif

    fd_type = strchr(console_mode, ':');
    fd_type++;
    _flushall();
    
    /*
     * If no console, we will spawn the emulator detached.
     */

    if (start_detached) {
	char *buff;
	close(0);
	close(1);
	close(2);
	set_env("ERL_CONSOLE_MODE", "detached");
	set_env(DLL_ENV, emu);

	argv[0] = start_prog;
	argv = fnuttify_argv(argv);
#ifdef ARGS_HARDDEBUG
	{
	    char buffer[2048];
	    int i;
	    sprintf(buffer,"Start detached [%s]\n",start_prog);
	    for(i=0;argv[i] != NULL;++i) {
		strcat(buffer,"|");
		strcat(buffer,argv[i]);
		strcat(buffer,"|\n");
	    }
	    MessageBox(NULL, buffer,"Start detached",MB_OK);
	}
#endif	    
	result = spawnv(_P_DETACH, start_prog, argv);
	free_fnuttified(argv);
	if (result == -1) {
#ifdef ARGS_HARDDEBUG
	    MessageBox(NULL, "_spawnv failed","Start detached",MB_OK);
#endif
	    return 1;
	}
	SetPriorityClass((HANDLE) result, GetPriorityClass(GetCurrentProcess()));
    } else {
	int argc = 0;
#ifdef LOAD_BEAM_DYNAMICALLY
	HMODULE beam_module = load_win_beam_dll(emu);
#endif	

	/*
	 * Start the emulator.
	 */

	title = get_env("ERL_WINDOW_TITLE");
	if (title) {
	    SetConsoleTitle(title);
	}
	free_env_val(title);
	
	set_env("ERL_CONSOLE_MODE", console_mode);
	while (argv[argc] != NULL) {
	    ++argc;
	}
	if (keep_window) {
	    atexit(do_keep_window);
	}
#ifdef ARGS_HARDDEBUG
	{
	    char sbuf[2048] = "";
	    int i;
	    for (i = 0; i < argc; ++i) {
		strcat(sbuf,"|");
		strcat(sbuf, argv[i]);
		strcat(sbuf,"|\n");
	    }
	    MessageBox(NULL, sbuf, "erl", MB_OK);
	}
#endif
#ifdef LOAD_BEAM_DYNAMICALLY
	(*sys_primitive_init_p)(beam_module);
	(*erl_start_p)(argc,argv);
#else
	erl_start(argc, argv);
#endif
    }
    return 0;
}