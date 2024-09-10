int main(int argc, char** argv, char** envp)
{
   int i, j, loglevel;
   const char *toolname = NULL;
   const char *clientname = NULL;
   int clientname_arg = 0;
   const char *archname = NULL;
   const char *arch;
   const char *default_arch;
   cpu_type_t default_cputype;
   char *toolfile;
   char launcher_name[PATH_MAX+1];
   char* new_line;
   char* set_cwd;
   char* cwd;
   char** new_env;
   char **new_argv;
   int new_argc;

   /* Start the debugging-log system ASAP.  First find out how many 
      "-d"s were specified.  This is a pre-scan of the command line.
      At the same time, look for the tool name. */
   loglevel = 0;
   for (i = 1; i < argc; i++) {
      if (argv[i][0] != '-') {
         clientname = argv[i];
         clientname_arg = i;
         break;
      }
      if (0 == strcmp(argv[i], "--")) {
         if (i+1 < argc) {
            clientname = argv[i+1];
            clientname_arg = i;
         }
         break;
      }
      if (0 == strcmp(argv[i], "-d")) 
         loglevel++;
      if (0 == strncmp(argv[i], "--tool=", 7)) 
         toolname = argv[i] + 7;
      if (0 == strncmp(argv[i], "--arch=", 7))
         archname = argv[i] + 7;
   }

   /* ... and start the debug logger.  Now we can safely emit logging
      messages all through startup. */
   VG_(debugLog_startup)(loglevel, "Stage 1");

   /* Make sure we know which tool we're using */
   if (toolname) {
      VG_(debugLog)(1, "launcher", "tool '%s' requested\n", toolname);
   } else {
      VG_(debugLog)(1, "launcher", 
                       "no tool requested, defaulting to 'memcheck'\n");
      toolname = "memcheck";
   }

   /* Find the real executable if clientname is an app bundle. */
   if (clientname) {
      struct stat st;
      if (0 == stat(clientname, &st)  &&  (st.st_mode & S_IFDIR)) {
         char *copy = strdup(clientname);
         char *appname = basename(copy);
         char *dot = strrchr(appname, '.');
         if (dot) {
            char *newclient;
            *dot = '\0';
            asprintf(&newclient, "%s/Contents/MacOS/%s", clientname, appname);
            VG_(debugLog)(1, "launcher", "Using executable in app bundle: %s\n", newclient);
            clientname = newclient;
            argv[clientname_arg] = newclient;
         }
         free(copy);
      }
   }

   /* Establish the correct VALGRIND_LIB. */
   {  const char *cp;
      cp = getenv(VALGRIND_LIB);
      valgrind_lib = ( cp == NULL ? VG_LIBDIR : cp );
      VG_(debugLog)(1, "launcher", "valgrind_lib = %s\n", valgrind_lib);
   }

   /* Find installed architectures. Use vgpreload_core-<platform>.so as the
    * indicator of whether the platform is installed. */
   for (i = 0; i < valid_archs_count; i++) {
      char *vgpreload_core;
      asprintf(&vgpreload_core, "%s/vgpreload_core-%s-darwin.so", valgrind_lib, valid_archs[i].valgrind_name);
      if (access(vgpreload_core, R_OK|X_OK) != 0) {
         VG_(debugLog)(1, "launcher", "arch '%s' IS NOT installed\n", valid_archs[i].valgrind_name);
         bzero(&valid_archs[i], sizeof(valid_archs[i]));
      } else {
         VG_(debugLog)(1, "launcher", "arch '%s' IS installed\n", valid_archs[i].valgrind_name);
      }
      free(vgpreload_core);
   }

   /* Find the "default" arch (VGCONF_ARCH_PRI from configure). 
      This is the preferred arch from fat files and the fallback. */
   default_arch = NULL;
   default_cputype = 0;
   for (i = 0; i < valid_archs_count; i++) {
      if (!valid_archs[i].cputype) continue;
      if (0 == strncmp(VG_PLATFORM, valid_archs[i].valgrind_name, 
                       strlen(valid_archs[i].valgrind_name))) 
      {
         default_arch = valid_archs[i].valgrind_name;
         default_cputype = valid_archs[i].cputype;
         break;
      }
   }
   if (i == valid_archs_count) barf("Unknown/uninstalled VG_PLATFORM '%s'", VG_PLATFORM);
   assert(NULL != default_arch);
   assert(0 != default_cputype);

   /* Work out what arch to use, or use the default arch if not possible. */
   if (archname != NULL) {
      // --arch from command line
      arch = NULL;
      for (i = 0; i < valid_archs_count; i++) {
         if (0 == strcmp(archname, valid_archs[i].apple_name)  ||  
             0 == strcmp(archname, valid_archs[i].valgrind_name))
         {
            arch = valid_archs[i].valgrind_name;
            break;
         }
      }
      if (i == valid_archs_count) barf("Unknown --arch '%s'", archname);
      assert(NULL != arch);
      VG_(debugLog)(1, "launcher", "using arch '%s' from --arch=%s\n", 
                    arch, archname);
   } 
   else if (clientname == NULL) {
      // no client executable; use default as fallback
      VG_(debugLog)(1, "launcher", 
                       "no client specified, defaulting arch to '%s'\n",
                        default_arch);
      arch = default_arch;
   } 
   else if ((arch = select_arch(clientname, default_cputype,default_arch))) {
      // arch from client executable
      VG_(debugLog)(1, "launcher", "selected arch '%s'\n", arch);
   } 
   else {
      // nothing found in client executable; use default as fallback
      VG_(debugLog)(1, "launcher", 
                       "no arch detected, defaulting arch to '%s'\n",
                       default_arch);
      arch = default_arch;
   }
   
   cwd = getcwd(NULL, 0);
   if (!cwd) barf("Current directory no longer exists.");

   /* Figure out the name of this executable (viz, the launcher), so
      we can tell stage2.  stage2 will use the name for recursive
      invokations of valgrind on child processes. */
   memset(launcher_name, 0, PATH_MAX+1);
   for (i = 0; envp[i]; i++) 
       ; /* executable path is after last envp item */
   /* envp[i] == NULL ; envp[i+1] == executable_path */
   if (envp[i+1][0] != '/') {
      strcpy(launcher_name, cwd);
      strcat(launcher_name, "/");
   }
   if (strlen(launcher_name) + strlen(envp[i+1]) > PATH_MAX)
      barf("launcher path is too long");
   strcat(launcher_name, envp[i+1]);
   VG_(debugLog)(1, "launcher", "launcher_name = %s\n", launcher_name);

   /* tediously augment the env: VALGRIND_LAUNCHER=launcher_name */
   asprintf(&new_line, VALGRIND_LAUNCHER "=%s", launcher_name);

   /* tediously augment the env: VALGRIND_STARTUP_PWD_%PID_XYZZY=current_working_dir */
   asprintf(&set_cwd, "VALGRIND_STARTUP_PWD_%u_XYZZY=%s", getppid(), cwd);

   // Note that Apple binaries get a secret fourth arg, "char* apple", which
   // contains the executable path.  Don't forget about it.
   for (j = 0; envp[j]; j++)
      ;
   new_env = malloc((j+4) * sizeof(char*));
   if (new_env == NULL)
      barf("malloc of new_env failed.");
   for (i = 0; i < j; i++)
      new_env[i] = envp[i];
   new_env[i++] = new_line;
   new_env[i++] = set_cwd;
   new_env[i++] = NULL;
   new_env[i  ] = envp[i-2]; // the 'apple' arg == the executable_path
   assert(i == j+3);

   /* tediously edit env: hide dyld options from valgrind's captive dyld */
   for (i = 0; envp[i]; i++) {
      if (0 == strncmp(envp[i], "DYLD_", 5)) {
         envp[i][0] = 'V';  /* VYLD_; changed back by initimg-darwin */
      }
   }

   /* tediously edit argv: remove --arch= */
   new_argv = malloc((1+argc) * sizeof(char *));
   for (i = 0, new_argc = 0; i < argc; i++) {
      if (0 == strncmp(argv[i], "--arch=", 7)) {
         // skip
      } else {
         new_argv[new_argc++] = argv[i];
      }
   }
   new_argv[new_argc++] = NULL;

   /* Build the stage2 invokation, and execve it.  Bye! */
   asprintf(&toolfile, "%s/%s-%s-darwin", valgrind_lib, toolname, arch);
   if (access(toolfile, R_OK|X_OK) != 0) {
      barf("tool '%s' not installed (%s) (%s)", toolname, toolfile, strerror(errno));
   }

   VG_(debugLog)(1, "launcher", "launching %s\n", toolfile);

   execve(toolfile, new_argv, new_env);

   fprintf(stderr, "valgrind: failed to start tool '%s' for platform '%s-darwin': %s\n",
                   toolname, arch, strerror(errno));

   exit(1);
}