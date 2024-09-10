int wmain(int argc, wchar_t **wcargv)
{
    char** argv;
#else
int main(int argc, char** argv)
{
#endif
    int eargv_size;
    int eargc_base;		/* How many arguments in the base of eargv. */
    char* emulator;
    char *env;
    int i;
    int need_shell = 0;

#ifdef __WIN32__
    int len;
    /* Convert argv to utf8 */
    argv = malloc((argc+1) * sizeof(char*));
    for (i=0; i<argc; i++) {
	len = WideCharToMultiByte(CP_UTF8, 0, wcargv[i], -1, NULL, 0, NULL, NULL);
	argv[i] = malloc(len*sizeof(char));
	WideCharToMultiByte(CP_UTF8, 0, wcargv[i], -1, argv[i], len, NULL, NULL);
    }
    argv[argc] = NULL;
#endif

    env = get_env("DIALYZER_EMULATOR");
    emulator = env ? env : get_default_emulator(argv[0]);

    if (strlen(emulator) >= MAXPATHLEN)
        error("Value of environment variable DIALYZER_EMULATOR is too large");

    /*
     * Allocate the argv vector to be used for arguments to Erlang.
     * Arrange for starting to pushing information in the middle of
     * the array, to allow easy addition of commands in the beginning.
     */

    eargv_size = argc*4+100;
    eargv_base = (char **) emalloc(eargv_size*sizeof(char*));
    eargv = eargv_base;
    eargc = 0;
    push_words(emulator);
    eargc_base = eargc;
    eargv = eargv + eargv_size/2;
    eargc = 0;

    free_env_val(env);

    /*
     * Push initial arguments.
     */

    for (i = 1; i < argc; i++) {
       if (strcmp(argv[i], "--wx") == 0) {
           PUSH("-smp"); /* wx currently requires SMP enabled */
           break;
       }
    }

    if (argc > 1 && strcmp(argv[1], "-smp") == 0) {
	PUSH("-smpauto");
	argc--, argv++;
    }

    if (argc > 2 && strcmp(argv[1], "+S") == 0) {
	PUSH3("-smp", "+S", argv[2]);
	argc--, argv++;
	argc--, argv++;
    }

    if (argc > 2 && strcmp(argv[1], "+P") == 0) {
	PUSH2("+P", argv[2]);
	argc--, argv++;
	argc--, argv++;
    } else PUSH2("+P", "1000000");

    if (argc > 2 && strcmp(argv[1], "+sbt") == 0) {
	PUSH2("+sbt", argv[2]);
	argc--, argv++;
	argc--, argv++;
    }

    PUSH("+B");
    PUSH2("-boot", "start_clean");
    PUSH3("-run", "dialyzer", "plain_cl");
    PUSH("-extra");

    /*
     * Push everything except --shell.
     */

    while (argc > 1) {
	if (strcmp(argv[1], "--shell") == 0) {
	    need_shell = 1;
	} else {
	    PUSH(argv[1]);
	}
	argc--, argv++;
    }

    if (!need_shell) {
	UNSHIFT("-noinput");
    }

    /*
     * Move up the commands for invoking the emulator and adjust eargv
     * accordingly.
     */

    while (--eargc_base >= 0) {
	UNSHIFT(eargv_base[eargc_base]);
    }
    
    /*
     * Invoke Erlang with the collected options.
     */

    PUSH(NULL);
    return run_erlang(eargv[0], eargv);
}