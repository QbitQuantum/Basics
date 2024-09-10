int
main(const int argc, const char *argv[], const char **envp)
{
  unsigned int i;

  FILE *out = stdout;
  int retcode;

  char *hook_env = getenv("GPHOTO_HOOK");
  char *filename = (hook_env!=NULL)?hook_env:"./test-hook.sh";
  
  /* We want this to be writable, so we explicitly define it as char[] */
  char params[7] = "params";
  char * const child_argv[] = {
    params,
    NULL,
  };
  
  /* envars not to copy */
  static const char * const varlist[] = {
    "ACTION", "ARGUMENT", NULL
  };

  unsigned int envi = 0;
  char **child_envp;

  /* count number of environment variables currently set */
  unsigned int envar_count;
  for (envar_count=0; envp[envar_count] != NULL; envar_count++) {
    /* printf("%3d: \"%s\"\n", envar_count, envp[envar_count]); */
  }
  
  fprintf(out, "Before spawn...\n");
  fflush(out);

  /* Initialize environment. Start with newly defined vars, then copy
   * all the existing ones.
   * Total amount of char* is
   *     number of existing envars (envar_count)
   *   + max number of new envars (2)
   *   + NULL list terminator (1)
   */
  child_envp = calloc(envar_count+2+1,sizeof(child_envp[0]));
  ASSERT(child_envp != NULL);

  /* own envars */
  child_envp[envi++] = alloc_envar("ARGUMENT", "/etc/shadow ;-P");
  child_envp[envi++] = alloc_envar("ACTION", "download");

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
      child_envp[envi] = strdup(envp[i]);
      ASSERT(child_envp[envi] != NULL);
      ++envi;
    }
  }

  /* Run the child program */
  retcode = spawnve(filename, child_argv, child_envp);

  fprintf(out, "After spawn, retcode=%d\n", retcode);
  fflush(out);

  /* Free memory */
  for (i=0; child_envp[i] != NULL; i++) {
    free(child_envp[i]);
  }
  free(child_envp);

  return retcode;
}