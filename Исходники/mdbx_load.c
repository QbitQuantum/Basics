int main(int argc, char *argv[]) {
  int i, rc;
  MDBX_env *env = NULL;
  MDBX_txn *txn = NULL;
  MDBX_cursor *mc = NULL;
  MDBX_dbi dbi;
  char *envname = NULL;
  int envflags = MDBX_UTTERLY_NOSYNC, putflags = 0;
  int append = 0;
  MDBX_val prevk;

  prog = argv[0];
  if (argc < 2)
    usage();

  /* -a: append records in input order
   * -f: load file instead of stdin
   * -n: use NOSUBDIR flag on env_open
   * -s: load into named subDB
   * -N: use NOOVERWRITE on puts
   * -T: read plaintext
   * -V: print version and exit
   */
  while ((i = getopt(argc, argv, "af:ns:NTV")) != EOF) {
    switch (i) {
    case 'V':
      printf("%s (%s, build %s)\n", mdbx_version.git.describe,
             mdbx_version.git.datetime, mdbx_build.datetime);
      exit(EXIT_SUCCESS);
      break;
    case 'a':
      append = 1;
      break;
    case 'f':
      if (freopen(optarg, "r", stdin) == NULL) {
        fprintf(stderr, "%s: %s: reopen: %s\n", prog, optarg,
                mdbx_strerror(errno));
        exit(EXIT_FAILURE);
      }
      break;
    case 'n':
      envflags |= MDBX_NOSUBDIR;
      break;
    case 's':
      subname = mdbx_strdup(optarg);
      break;
    case 'N':
      putflags = MDBX_NOOVERWRITE | MDBX_NODUPDATA;
      break;
    case 'T':
      mode |= NOHDR | PRINT;
      break;
    default:
      usage();
    }
  }

  if (optind != argc - 1)
    usage();

#if defined(_WIN32) || defined(_WIN64)
  SetConsoleCtrlHandler(ConsoleBreakHandlerRoutine, true);
#else
#ifdef SIGPIPE
  signal(SIGPIPE, signal_handler);
#endif
#ifdef SIGHUP
  signal(SIGHUP, signal_handler);
#endif
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);
#endif /* !WINDOWS */

  dbuf.iov_len = 4096;
  dbuf.iov_base = mdbx_malloc(dbuf.iov_len);

  /* read first header for mapsize= */
  if (!(mode & NOHDR))
    readhdr();

  envname = argv[optind];
  rc = mdbx_env_create(&env);
  if (rc) {
    fprintf(stderr, "mdbx_env_create failed, error %d %s\n", rc,
            mdbx_strerror(rc));
    return EXIT_FAILURE;
  }

  mdbx_env_set_maxdbs(env, 2);

  if (envinfo.mi_maxreaders)
    mdbx_env_set_maxreaders(env, envinfo.mi_maxreaders);

  if (envinfo.mi_mapsize) {
    if (envinfo.mi_mapsize > SIZE_MAX) {
      fprintf(stderr, "mdbx_env_set_mapsize failed, error %d %s\n", rc,
              mdbx_strerror(MDBX_TOO_LARGE));
      return EXIT_FAILURE;
    }
    mdbx_env_set_mapsize(env, (size_t)envinfo.mi_mapsize);
  }

#ifdef MDBX_FIXEDMAP
  if (info.mi_mapaddr)
    envflags |= MDBX_FIXEDMAP;
#endif

  rc = mdbx_env_open(env, envname, envflags, 0664);
  if (rc) {
    fprintf(stderr, "mdbx_env_open failed, error %d %s\n", rc,
            mdbx_strerror(rc));
    goto env_close;
  }

  kbuf.iov_len = mdbx_env_get_maxkeysize(env);
  if (kbuf.iov_len >= SIZE_MAX / 4) {
    fprintf(stderr, "mdbx_env_get_maxkeysize failed, returns %zu\n",
            kbuf.iov_len);
    goto env_close;
  }
  kbuf.iov_len = (kbuf.iov_len + 1) * 2;
  kbuf.iov_base = malloc(kbuf.iov_len * 2);
  k0buf.iov_len = kbuf.iov_len;
  k0buf.iov_base = (char *)kbuf.iov_base + kbuf.iov_len;
  prevk.iov_base = k0buf.iov_base;

  while (!Eof) {
    if (user_break) {
      rc = MDBX_EINTR;
      break;
    }

    rc = mdbx_txn_begin(env, NULL, 0, &txn);
    if (rc) {
      fprintf(stderr, "mdbx_txn_begin failed, error %d %s\n", rc,
              mdbx_strerror(rc));
      goto env_close;
    }

    rc = mdbx_dbi_open_ex(txn, subname, dbi_flags | MDBX_CREATE, &dbi,
                          append ? anyway_greater : NULL,
                          append ? anyway_greater : NULL);
    if (rc) {
      fprintf(stderr, "mdbx_open failed, error %d %s\n", rc, mdbx_strerror(rc));
      goto txn_abort;
    }

    rc = mdbx_cursor_open(txn, dbi, &mc);
    if (rc) {
      fprintf(stderr, "mdbx_cursor_open failed, error %d %s\n", rc,
              mdbx_strerror(rc));
      goto txn_abort;
    }

    int batch = 0;
    prevk.iov_len = 0;
    while (1) {
      MDBX_val key;
      rc = readline(&key, &kbuf);
      if (rc) /* rc == EOF */
        break;

      MDBX_val data;
      rc = readline(&data, &dbuf);
      if (rc) {
        fprintf(stderr, "%s: line %" PRIiSIZE ": failed to read key value\n",
                prog, lineno);
        goto txn_abort;
      }

      int appflag = 0;
      if (append) {
        appflag = MDBX_APPEND;
        if (dbi_flags & MDBX_DUPSORT) {
          if (prevk.iov_len == key.iov_len &&
              memcmp(prevk.iov_base, key.iov_base, key.iov_len) == 0)
            appflag = MDBX_APPEND | MDBX_APPENDDUP;
          else
            memcpy(prevk.iov_base, key.iov_base, prevk.iov_len = key.iov_len);
        }
      }
      rc = mdbx_cursor_put(mc, &key, &data, putflags | appflag);
      if (rc == MDBX_KEYEXIST && putflags)
        continue;
      if (rc) {
        fprintf(stderr, "mdbx_cursor_put failed, error %d %s\n", rc,
                mdbx_strerror(rc));
        goto txn_abort;
      }
      batch++;
      if (batch == 100) {
        rc = mdbx_txn_commit(txn);
        if (rc) {
          fprintf(stderr, "%s: line %" PRIiSIZE ": txn_commit: %s\n", prog,
                  lineno, mdbx_strerror(rc));
          goto env_close;
        }
        rc = mdbx_txn_begin(env, NULL, 0, &txn);
        if (rc) {
          fprintf(stderr, "mdbx_txn_begin failed, error %d %s\n", rc,
                  mdbx_strerror(rc));
          goto env_close;
        }
        rc = mdbx_cursor_open(txn, dbi, &mc);
        if (rc) {
          fprintf(stderr, "mdbx_cursor_open failed, error %d %s\n", rc,
                  mdbx_strerror(rc));
          goto txn_abort;
        }
        batch = 0;
      }
    }
    rc = mdbx_txn_commit(txn);
    txn = NULL;
    if (rc) {
      fprintf(stderr, "%s: line %" PRIiSIZE ": txn_commit: %s\n", prog, lineno,
              mdbx_strerror(rc));
      goto env_close;
    }
    mdbx_dbi_close(env, dbi);

    /* try read next header */
    if (!(mode & NOHDR))
      readhdr();
  }

txn_abort:
  mdbx_txn_abort(txn);
env_close:
  mdbx_env_close(env);

  return rc ? EXIT_FAILURE : EXIT_SUCCESS;
}