static int
internal_run_hook(const char *const hook_script, 
		  const char *const action, const char *const argument,
		  char **envp)
{
#ifdef CALL_VIA_SYSTEM
	int retcode;

	/* run hook using system(3) */
	internal_putenv("ACTION", action);
	internal_putenv("ARGUMENT", argument);
	
	retcode = system(hook_script);
	if (retcode != 0) {
		fprintf(stderr, "Hook script returned error code %d (0x%x)\n",
			retcode, retcode);
		return 1;
	}
	return 0;
#else
	/* spawnve() based implementation of internal_run_hook()
	 *
	 * Most of the code here creates and destructs the
	 * char *child_argv[] and char *child_envp[] to be passed to 
	 * spawnve() and thus execve().
	 *
	 * Error handling is simple:
	 *  * If malloc() or calloc() fail, abort the whole program.
	 */

	/* A note on program memory layout:
	 *
	 * child_argv and child_envp MUST be in writable memory, so we
	 * malloc() them.
	 */
	
	char *my_hook_script = strdup(hook_script);
	unsigned int i;

	/* run hook using execve(2) */
	char **child_argv = calloc(2, sizeof(child_argv[0]));

	/* envars not to copy */
	const char *const varlist[] = {
		"ACTION", "ARGUMENT", NULL
	};

	/* environment variables for child process, and index going through them */
	char **child_envp;
	unsigned int envi = 0;

	int retcode;
	
	/* count number of environment variables currently set */
	unsigned int envar_count;
	for (envar_count=0; envp[envar_count] != NULL; envar_count++) {
		/* printf("%3d: \"%s\"\n", envar_count, envp[envar_count]); */
	}

	ASSERT(my_hook_script != NULL);
	child_argv[0] = my_hook_script;

	/* Initialize environment. Start with newly defined vars, then copy
	 * all the existing ones. calloc() does the initialization with NULL.
	 * Total amount of char* is
	 *     number of existing envars (envar_count)
	 *   + max number of new envars (2)
	 *   + NULL list terminator (1)
	 */
	child_envp = calloc(envar_count+((sizeof(varlist)/sizeof(varlist[0]))-1)+1, 
			    sizeof(child_envp[0]));
	ASSERT(child_envp != NULL);

	/* own envars */
	if (NULL != action) {
		char *envar = alloc_envar("ACTION", action);
		ASSERT(envar != NULL);
		child_envp[envi++] = envar;
	}
	if (NULL != argument) {
		char *envar = alloc_envar("ARGUMENT", argument);
		ASSERT(envar != NULL);
		child_envp[envi++] = envar;
	}
	
	/* copy envars except for those in varlist */
	for (i=0; i<envar_count; i++) {
		int skip = 0;
		unsigned int n;
		for (n=0; varlist[n] != NULL; n++) {
			const char *varname = varlist[n];
			const char *start = strstr(envp[i], varname);
			if ((envp[i] == start) &&  (envp[i][strlen(varname)] == '=')) {
				skip = 1;
				break;
			}
		}
		if (!skip) {
			child_envp[envi++] = strdup(envp[i]);
		}
	}
	
	/* Actually run the hook script */
	retcode = spawnve(hook_script, child_argv, child_envp);
		
	/* Free all memory */
	for (i=0; child_envp[i] != NULL; i++) {
		free(child_envp[i]);
	}
	free(child_envp);
	for (i=0; child_argv[i] != NULL; i++) {
		free(child_argv[i]);
	}
	free(child_argv);

	/* And finally return to caller */
	if (retcode != 0) {
		fprintf(stderr, "Hook script returned error code %d (0x%x)\n",
			retcode, retcode);
		return 1;
	}
	return 0;
#endif
}