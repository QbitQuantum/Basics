static string
maketex (kpathsea kpse, kpse_file_format_type format, string* args)
{
  /* New implementation, use fork/exec pair instead of popen, since
   * the latter is virtually impossible to make safe.
   */
  unsigned len;
  string *s;
  string ret = NULL;
  string fn;
#if defined(WIN32)
  char   fullbin[256], *wrp;

  wrp = kpathsea_var_value(kpse, "SELFAUTOLOC");
  if(wrp == NULL) {
     fprintf(stderr, "I cannot get SELFAUTOLOC\n");
     exit(100);
  }

  strcpy(fullbin, wrp);
  free(wrp);
  for(wrp=fullbin; *wrp; wrp++) {
     if(*wrp == '/') *wrp = '\\';
  }
  strcat(fullbin, "\\");
  strcat(fullbin, args[0]);
#endif
  if (!kpse->make_tex_discard_errors) {
    fprintf (stderr, "\nkpathsea: Running");
    for (s = &args[0]; *s != NULL; s++)
      fprintf (stderr, " %s", *s);
    fputc('\n', stderr);
  }

#if defined (AMIGA)
  /* Amiga has a different interface. */
  {
    string cmd;
    string newcmd;
    cmd = xstrdup(args[0]);
    for (s = &args[1];  *s != NULL; s++) {
      newcmd = concat(cmd, *s);
      free (cmd);
      cmd = newcmd;
    }
    ret = system(cmd) == 0 ? getenv ("LAST_FONT_CREATED"): NULL;
    free (cmd);
  }
#elif defined (MSDOS) && !defined(__DJGPP__)
#error Implement new MSDOS mktex call interface here
#else /* WIN32 or Unix */
  {
#if defined (WIN32)
    /* spawnvp(_P_NOWAIT, ...) and pipe --ak 2002/12/15 */

    unsigned long nexitcode = STILL_ACTIVE;
    HANDLE hchild;
    int hstdout, childpipe[2];
    int hstderr = -1;
    FILE *Hnul = NULL;

    fn = NULL;

    if(_pipe(childpipe, 1024, O_TEXT | _O_NOINHERIT) == -1) {
      perror("kpathsea: pipe()");
      goto labeldone;
    }

    hstdout = _dup(fileno(stdout));
    if(_dup2(childpipe[1], fileno(stdout)) != 0) {
      close(hstdout);
      close(childpipe[0]);
      close(childpipe[1]);
      goto labeldone;
    }

    close(childpipe[1]);

    if(kpse->make_tex_discard_errors) {
      Hnul = fopen("nul", "w");
      if(!Hnul) {
        perror("kpathsea: fopen(\"nul\")");
      }
      else {
        hstderr = _dup(fileno(stderr));
        _dup2(fileno(Hnul), fileno(stderr));
      }
    }
    fprintf(stderr, "\nThe command name is %s\n", fullbin);
    hchild = (HANDLE)_spawnvp(_P_NOWAIT, fullbin, (const char * const *) args);

    _dup2(hstdout, fileno(stdout));
    close(hstdout);

    if(hchild == (HANDLE)(-1)) {
      close(childpipe[0]);
      goto labeldone;
    }

    if(hchild) {
      char buf[1024+1];
      int num;

      fn = xstrdup("");
      while(nexitcode == STILL_ACTIVE) {
        num = read(childpipe[0], buf, sizeof(buf)-1);
        if(num) {
          string newfn;
          buf[num] = '\0';
          newfn = concat(fn, buf);
          free(fn);
          fn = newfn;
        }
        if(!GetExitCodeProcess(hchild, &nexitcode)) {
          fn = NULL;
          close(childpipe[0]);
          goto labeldone;
        }
      }
      close(childpipe[0]);
    }

 labeldone:
    if(kpse->make_tex_discard_errors && Hnul) {
       _dup2(hstderr, fileno(stderr));
       close(hstderr);
       fclose(Hnul);
    }
#else /* !WIN32 */
    /* Standard input for the child.  Set to /dev/null */
    int childin;
    /* Standard output for the child, what we're interested in. */
    int childout[2];
    /* Standard error for the child, same as parent or /dev/null */
    int childerr;
    /* Child pid. */
    pid_t childpid;

    /* Open the channels that the child will use. */
    /* A fairly horrible uses of gotos for here for the error case. */
    if ((childin = open("/dev/null", O_RDONLY)) < 0) {
      perror("kpathsea: open(\"/dev/null\", O_RDONLY)");
      goto error_childin;
    }
    if (pipe(childout) < 0) {
      perror("kpathsea: pipe()");
      goto error_childout;
    }
    if ((childerr = open("/dev/null", O_WRONLY)) < 0) {
      perror("kpathsea: open(\"/dev/null\", O_WRONLY)");
      goto error_childerr;
    }
    if ((childpid = fork()) < 0) {
      perror("kpathsea: fork()");
      close(childerr);
     error_childerr:
      close(childout[0]);
      close(childout[1]);
     error_childout:
      close(childin);
     error_childin:
      fn = NULL;
    } else if (childpid == 0) {
      /* Child
       *
       * We can use vfork, provided we're careful about what we
       * do here: do not return from this function, do not modify
       * variables, call _exit if there is a problem.
       *
       * Complete setting up the file descriptors.
       * We use dup(2) so the order in which we do this matters.
       */
      close(childout[0]);
      /* stdin -- the child will not receive input from this */
      if (childin != 0) {
        close(0);
        if (dup(childin) != 0) {
          perror("kpathsea: dup(2) failed for stdin");
          close(childin);
          _exit(1);
        }
        close(childin);
      }
      /* stdout -- the output of the child's action */
      if (childout[1] != 1) {
        close(1);
        if (dup(childout[1]) != 1) {
          perror("kpathsea: dup(2) failed for stdout");
          close(childout[1]);
          _exit(1);
        }
        close(childout[1]);
      }
      /* stderr -- use /dev/null if we discard errors */
      if (childerr != 2) {
        if (kpse->make_tex_discard_errors) {
          close(2);
          if (dup(childerr) != 2) {
            perror("kpathsea: dup(2) failed for stderr");
            close(childerr);
            _exit(1);
          }
        }
        close(childerr);
      }
      /* FIXME: We could/should close all other file descriptors as well. */
      /* exec -- on failure a call of _exit(2) it is the only option */
      if (execvp(args[0], args))
        perror(args[0]);
      _exit(1);
    } else {
      /* Parent */
      char buf[1024+1];
      int num;

      /* Clean up child file descriptors that we won't use anyway. */
      close(childin);
      close(childout[1]);
      close(childerr);
      /* Get stdout of child from the pipe. */
      fn = xstrdup("");
      while ((num = read(childout[0],buf,sizeof(buf)-1)) != 0) {
        if (num == -1) {
          if (errno != EINTR) {
            perror("kpathsea: read()");
            break;
          }
        } else {
          string newfn;
          buf[num] = '\0';
          newfn = concat(fn, buf);
          free(fn);
          fn = newfn;
        }
      }
      /* End of file on pipe, child should have exited at this point. */
      close(childout[0]);
      /* We don't really care about the exit status at this point. */
      wait(NULL);
    }
#endif /* !WIN32 */

    if (fn) {
      len = strlen(fn);

      /* Remove trailing newlines and returns.  */
      while (len && (fn[len - 1] == '\n' || fn[len - 1] == '\r')) {
        fn[len - 1] = '\0';
        len--;
      }

      ret = len == 0 ? NULL : kpathsea_readable_file (kpse, fn);
      if (!ret && len > 1) {
        WARNING2 ("kpathsea: %s output `%s' instead of a filename",
                  args[0], fn);
      }

      /* Free the name if we're not returning it.  */
      if (fn != ret)
        free (fn);
    }
  }
#endif /* WIN32 or Unix */

  if (ret == NULL)
      misstex (kpse, format, args);
  else
      kpathsea_db_insert (kpse, ret);

  return ret;
}