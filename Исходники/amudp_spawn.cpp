/* ------------------------------------------------------------------------------------ 
 *  spawn jobs on local machine
 * ------------------------------------------------------------------------------------ */
extern int AMUDP_SPMDLocalSpawn(int nproc, int argc, char **argv, char **extra_env) {
  /* just a simple fork/exec */
  int i;

  if (!AMUDP_SPMDSpawnRunning) {
    AMUDP_Err("Spawn functions should never be run directly - only passed to AMUDP_SPMDStartup()"); 
    return FALSE;
  }

  /* Temporarily assume values from extra_env[] (which we modify in-place) */
  char **save_env = NULL;
  int envc = 0;
  if (extra_env && extra_env[0]) {
    for (envc=0; extra_env[envc]; ++envc) {/*empty*/}
    save_env = (char **)AMUDP_malloc(sizeof(char *)*envc);
    for (i=0;i<envc;++i) {
      char *var = extra_env[i];
      char *delim = strchr(var,'=');
      AMUDP_assert(delim);
      *delim = '\0';
      save_env[i] = getenv(var);
      setenv(var,delim+1,1);
    }
  }

  for (i = 0; i < nproc; i++) {
    #if PLATFORM_OS_MSWINDOWS && !PLATFORM_OS_CYGWIN
      if (_spawnv(_P_NOWAIT, argv[0], argv) == -1)
        AMUDP_FatalErr("failed _spawnv()");
    #elif PLATFORM_ARCH_CRAYX1
      { char **nargv = (char **)AMUDP_malloc(sizeof(char *)*(argc+2));
        nargv[0] = argv[0];
        memcpy(nargv+1,argv,argc*sizeof(char *));
        nargv[argc+1] = NULL;
        if (execsp(nargv, environ, NULL) == -1)
          AMUDP_FatalErr("failed execsp()");
      }
    #else
      int forkRet = fork();
      if (forkRet == -1) {
        perror("fork");
        return FALSE;
      } else if (forkRet != 0) continue;  /*  this is the parent, will go back to the top of the loop */
      else {  /*  this is the child - exec the new process */
        /*  could close some resources here (like AMUDP_SPMDListenSocket) but not strictly necessary */

        #if 0
          /*  put new process in a separate process group */
          if (setsid() == -1) perror("setsid"); 
        #endif

        /*  exec the program, with the given arguments  */
        execv(argv[0], argv);

        /*  if execv returns, an error occurred */
        perror("execv");
        _exit(1); /*  use _exit() to prevent corrupting parent's io buffers */
      } /*  child */
    #endif
  }

  /* Restore saved environment var(s) */
  for (i=0;i<envc;++i) {
    char *name = extra_env[i];
    if (save_env[i]) {
      setenv(name,save_env[i],1);
    } else {
      unsetenv(name);
    }
    /* Revert our in-place modification of extra_env[]: */
    name[strlen(name)] = '=';
  }
  AMUDP_free(save_env);

  return TRUE;
}