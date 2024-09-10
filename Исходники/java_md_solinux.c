void
CreateExecutionEnvironment(int *pargc, char ***pargv,
                           char jrepath[], jint so_jrepath,
                           char jvmpath[], jint so_jvmpath,
                           char jvmcfg[],  jint so_jvmcfg) {
  /*
   * First, determine if we are running the desired data model.  If we
   * are running the desired data model, all the error messages
   * associated with calling GetJREPath, ReadKnownVMs, etc. should be
   * output.  However, if we are not running the desired data model,
   * some of the errors should be suppressed since it is more
   * informative to issue an error message based on whether or not the
   * os/processor combination has dual mode capabilities.
   */
    jboolean jvmpathExists;

    /* Compute/set the name of the executable */
    SetExecname(*pargv);

    /* Check data model flags, and exec process, if needed */
    {
      char *arch        = (char *)GetArch(); /* like sparc or sparcv9 */
      char * jvmtype    = NULL;
      int  argc         = *pargc;
      char **argv       = *pargv;
      int running       = CURRENT_DATA_MODEL;

      int wanted        = running;      /* What data mode is being
                                           asked for? Current model is
                                           fine unless another model
                                           is asked for */
#ifdef SETENV_REQUIRED
      jboolean mustsetenv = JNI_FALSE;
      char *runpath     = NULL; /* existing effective LD_LIBRARY_PATH setting */
      char* new_runpath = NULL; /* desired new LD_LIBRARY_PATH string */
      char* newpath     = NULL; /* path on new LD_LIBRARY_PATH */
      char* lastslash   = NULL;
      char** newenvp    = NULL; /* current environment */
#ifdef __solaris__
      char*  dmpath     = NULL;  /* data model specific LD_LIBRARY_PATH,
                                    Solaris only */
#endif /* __solaris__ */
#endif  /* SETENV_REQUIRED */

      char** newargv    = NULL;
      int    newargc    = 0;

      /*
       * Starting in 1.5, all unix platforms accept the -d32 and -d64
       * options.  On platforms where only one data-model is supported
       * (e.g. ia-64 Linux), using the flag for the other data model is
       * an error and will terminate the program.
       */

      { /* open new scope to declare local variables */
        int i;

        newargv = (char **)JLI_MemAlloc((argc+1) * sizeof(char*));
        newargv[newargc++] = argv[0];

        /* scan for data model arguments and remove from argument list;
           last occurrence determines desired data model */
        for (i=1; i < argc; i++) {

          if (JLI_StrCmp(argv[i], "-J-d64") == 0 || JLI_StrCmp(argv[i], "-d64") == 0) {
            wanted = 64;
            continue;
          }
          if (JLI_StrCmp(argv[i], "-J-d32") == 0 || JLI_StrCmp(argv[i], "-d32") == 0) {
            wanted = 32;
            continue;
          }
          newargv[newargc++] = argv[i];

          if (IsJavaArgs()) {
            if (argv[i][0] != '-') continue;
          } else {
            if (JLI_StrCmp(argv[i], "-classpath") == 0 || JLI_StrCmp(argv[i], "-cp") == 0) {
              i++;
              if (i >= argc) break;
              newargv[newargc++] = argv[i];
              continue;
            }
            if (argv[i][0] != '-') { i++; break; }
          }
        }

        /* copy rest of args [i .. argc) */
        while (i < argc) {
          newargv[newargc++] = argv[i++];
        }
        newargv[newargc] = NULL;

        /*
         * newargv has all proper arguments here
         */

        argc = newargc;
        argv = newargv;
      }

      /* If the data model is not changing, it is an error if the
         jvmpath does not exist */
      if (wanted == running) {
        /* Find out where the JRE is that we will be using. */
        if (!GetJREPath(jrepath, so_jrepath, arch, JNI_FALSE) ) {
          JLI_ReportErrorMessage(JRE_ERROR1);
          exit(2);
        }
        JLI_Snprintf(jvmcfg, so_jvmcfg, "%s%slib%s%s%sjvm.cfg",
                     jrepath, FILESEP, FILESEP,  arch, FILESEP);
        /* Find the specified JVM type */
        if (ReadKnownVMs(jvmcfg, JNI_FALSE) < 1) {
          JLI_ReportErrorMessage(CFG_ERROR7);
          exit(1);
        }

        jvmpath[0] = '\0';
        jvmtype = CheckJvmType(pargc, pargv, JNI_FALSE);
        if (JLI_StrCmp(jvmtype, "ERROR") == 0) {
            JLI_ReportErrorMessage(CFG_ERROR9);
            exit(4);
        }

        if (!GetJVMPath(jrepath, jvmtype, jvmpath, so_jvmpath, arch, 0 )) {
          JLI_ReportErrorMessage(CFG_ERROR8, jvmtype, jvmpath);
          exit(4);
        }
        /*
         * we seem to have everything we need, so without further ado
         * we return back, otherwise proceed to set the environment.
         */
#ifdef SETENV_REQUIRED
        mustsetenv = RequiresSetenv(wanted, jvmpath);
        JLI_TraceLauncher("mustsetenv: %s\n", mustsetenv ? "TRUE" : "FALSE");

        if (mustsetenv == JNI_FALSE) {
            return;
        }
#else
        return;
#endif /* SETENV_REQUIRED */
      } else {  /* do the same speculatively or exit */
#ifdef DUAL_MODE
        if (running != wanted) {
          /* Find out where the JRE is that we will be using. */
          if (!GetJREPath(jrepath, so_jrepath, GetArchPath(wanted), JNI_TRUE)) {
            /* give up and let other code report error message */
            JLI_ReportErrorMessage(JRE_ERROR2, wanted);
            exit(1);
          }
          JLI_Snprintf(jvmcfg, so_jvmcfg, "%s%slib%s%s%sjvm.cfg",
                       jrepath, FILESEP, FILESEP, GetArchPath(wanted), FILESEP);
          /*
           * Read in jvm.cfg for target data model and process vm
           * selection options.
           */
          if (ReadKnownVMs(jvmcfg, JNI_TRUE) < 1) {
            /* give up and let other code report error message */
            JLI_ReportErrorMessage(JRE_ERROR2, wanted);
            exit(1);
          }
          jvmpath[0] = '\0';
          jvmtype = CheckJvmType(pargc, pargv, JNI_TRUE);
          if (JLI_StrCmp(jvmtype, "ERROR") == 0) {
            JLI_ReportErrorMessage(CFG_ERROR9);
            exit(4);
          }

          /* exec child can do error checking on the existence of the path */
          jvmpathExists = GetJVMPath(jrepath, jvmtype, jvmpath, so_jvmpath, GetArchPath(wanted), 0);
#ifdef SETENV_REQUIRED
          mustsetenv = RequiresSetenv(wanted, jvmpath);
#endif /* SETENV_REQUIRED */
        }
#else /* ! DUALMODE */
        JLI_ReportErrorMessage(JRE_ERROR2, wanted);
        exit(1);
#endif /* DUAL_MODE */
        }
#ifdef SETENV_REQUIRED
        if (mustsetenv) {
            /*
             * We will set the LD_LIBRARY_PATH as follows:
             *
             *     o          $JVMPATH (directory portion only)
             *     o          $JRE/lib/$LIBARCHNAME
             *     o          $JRE/../lib/$LIBARCHNAME
             *
             * followed by the user's previous effective LD_LIBRARY_PATH, if
             * any.
             */

#ifdef __solaris__
            /*
             * Starting in Solaris 7, ld.so.1 supports three LD_LIBRARY_PATH
             * variables:
             *
             * 1. LD_LIBRARY_PATH -- used for 32 and 64 bit searches if
             * data-model specific variables are not set.
             *
             * 2. LD_LIBRARY_PATH_64 -- overrides and replaces LD_LIBRARY_PATH
             * for 64-bit binaries.
             *
             * 3. LD_LIBRARY_PATH_32 -- overrides and replaces LD_LIBRARY_PATH
             * for 32-bit binaries.
             *
             * The vm uses LD_LIBRARY_PATH to set the java.library.path system
             * property.  To shield the vm from the complication of multiple
             * LD_LIBRARY_PATH variables, if the appropriate data model
             * specific variable is set, we will act as if LD_LIBRARY_PATH had
             * the value of the data model specific variant and the data model
             * specific variant will be unset.  Note that the variable for the
             * *wanted* data model must be used (if it is set), not simply the
             * current running data model.
             */

            switch (wanted) {
                case 0:
                    if (running == 32) {
                        dmpath = getenv("LD_LIBRARY_PATH_32");
                        wanted = 32;
                    } else {
                        dmpath = getenv("LD_LIBRARY_PATH_64");
                        wanted = 64;
                    }
                    break;

                case 32:
                    dmpath = getenv("LD_LIBRARY_PATH_32");
                    break;

                case 64:
                    dmpath = getenv("LD_LIBRARY_PATH_64");
                    break;

                default:
                    JLI_ReportErrorMessage(JRE_ERROR3, __LINE__);
                    exit(1); /* unknown value in wanted */
                    break;
            }

            /*
             * If dmpath is NULL, the relevant data model specific variable is
             * not set and normal LD_LIBRARY_PATH should be used.
             */
            if (dmpath == NULL) {
                runpath = getenv("LD_LIBRARY_PATH");
            } else {
                runpath = dmpath;
            }
#else /* ! __solaris__ */
            /*
             * If not on Solaris, assume only a single LD_LIBRARY_PATH
             * variable.
             */
            runpath = getenv("LD_LIBRARY_PATH");
#endif /* __solaris__ */

            /* runpath contains current effective LD_LIBRARY_PATH setting */

            jvmpath = JLI_StringDup(jvmpath);
            new_runpath = JLI_MemAlloc(((runpath != NULL) ? JLI_StrLen(runpath) : 0) +
                    2 * JLI_StrLen(jrepath) + 2 * JLI_StrLen(arch) +
                    JLI_StrLen(jvmpath) + 52);
            newpath = new_runpath + JLI_StrLen("LD_LIBRARY_PATH=");


            /*
             * Create desired LD_LIBRARY_PATH value for target data model.
             */
            {
                /* remove the name of the .so from the JVM path */
                lastslash = JLI_StrRChr(jvmpath, '/');
                if (lastslash)
                    *lastslash = '\0';

                sprintf(new_runpath, "LD_LIBRARY_PATH="
                        "%s:"
                        "%s/lib/%s:"
                        "%s/../lib/%s",
                        jvmpath,
#ifdef DUAL_MODE
                        jrepath, GetArchPath(wanted),
                        jrepath, GetArchPath(wanted)
#else /* !DUAL_MODE */
                        jrepath, arch,
                        jrepath, arch
#endif /* DUAL_MODE */
                        );


                /*
                 * Check to make sure that the prefix of the current path is the
                 * desired environment variable setting, though the RequiresSetenv
                 * checks if the desired runpath exists, this logic does a more
                 * comprehensive check.
                 */
                if (runpath != NULL &&
                        JLI_StrNCmp(newpath, runpath, JLI_StrLen(newpath)) == 0 &&
                        (runpath[JLI_StrLen(newpath)] == 0 || runpath[JLI_StrLen(newpath)] == ':') &&
                        (running == wanted) /* data model does not have to be changed */
#ifdef __solaris__
                        && (dmpath == NULL) /* data model specific variables not set  */
#endif /* __solaris__ */
                        ) {

                    return;

                }
            }

            /*
             * Place the desired environment setting onto the prefix of
             * LD_LIBRARY_PATH.  Note that this prevents any possible infinite
             * loop of execv() because we test for the prefix, above.
             */
            if (runpath != 0) {
                JLI_StrCat(new_runpath, ":");
                JLI_StrCat(new_runpath, runpath);
            }

            if (putenv(new_runpath) != 0) {
                exit(1); /* problem allocating memory; LD_LIBRARY_PATH not set
                    properly */
            }

            /*
             * Unix systems document that they look at LD_LIBRARY_PATH only
             * once at startup, so we have to re-exec the current executable
             * to get the changed environment variable to have an effect.
             */

#ifdef __solaris__
            /*
             * If dmpath is not NULL, remove the data model specific string
             * in the environment for the exec'ed child.
             */
            if (dmpath != NULL)
                (void)UnsetEnv((wanted == 32) ? "LD_LIBRARY_PATH_32" : "LD_LIBRARY_PATH_64");
#endif /* __solaris */

            newenvp = environ;
        }
#endif /* SETENV_REQUIRED */
        {
            char *newexec = execname;
#ifdef DUAL_MODE
            /*
             * If the data model is being changed, the path to the
             * executable must be updated accordingly; the executable name
             * and directory the executable resides in are separate.  In the
             * case of 32 => 64, the new bits are assumed to reside in, e.g.
             * "olddir/LIBARCH64NAME/execname"; in the case of 64 => 32,
             * the bits are assumed to be in "olddir/../execname".  For example,
             *
             * olddir/sparcv9/execname
             * olddir/amd64/execname
             *
             * for Solaris SPARC and Linux amd64, respectively.
             */

            if (running != wanted) {
                char *oldexec = JLI_StrCpy(JLI_MemAlloc(JLI_StrLen(execname) + 1), execname);
                char *olddir = oldexec;
                char *oldbase = JLI_StrRChr(oldexec, '/');


                newexec = JLI_MemAlloc(JLI_StrLen(execname) + 20);
                *oldbase++ = 0;
                sprintf(newexec, "%s/%s/%s", olddir,
                        ((wanted == 64) ? LIBARCH64NAME : ".."), oldbase);
                argv[0] = newexec;
            }
#endif /* DUAL_MODE */
            JLI_TraceLauncher("TRACER_MARKER:About to EXEC\n");
            (void) fflush(stdout);
            (void) fflush(stderr);
#ifdef SETENV_REQUIRED
            if (mustsetenv) {
                execve(newexec, argv, newenvp);
            } else {
                execv(newexec, argv);
            }
#else /* !SETENV_REQUIRED */
            execv(newexec, argv);
#endif /* SETENV_REQUIRED */
            JLI_ReportErrorMessageSys(JRE_ERROR4, newexec);

#ifdef DUAL_MODE
            if (running != wanted) {
                JLI_ReportErrorMessage(JRE_ERROR5, wanted, running);
#ifdef __solaris__
#ifdef __sparc
                JLI_ReportErrorMessage(JRE_ERROR6);
#else  /* ! __sparc__ */
                JLI_ReportErrorMessage(JRE_ERROR7);
#endif  /* __sparc */
#endif /* __solaris__ */
            }
#endif /* DUAL_MODE */

        }
        exit(1);
    }
}