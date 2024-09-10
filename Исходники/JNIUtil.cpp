/**
 * Initialize the environment for all requests.
 * @param env   the JNI environment for this request
 */
bool JNIUtil::JNIGlobalInit(JNIEnv *env)
{
  // This method has to be run only once during the run a program.
  static bool run = false;
  svn_error_t *err;
  if (run) // already run
    return true;

  run = true;

  // Do not run this part more than one time.  This leaves a small
  // time window when two threads create their first SVNClient and
  // SVNAdmin at the same time, but I do not see a better option
  // without APR already initialized
  if (g_inInit)
    return false;

  g_inInit = true;
  g_initEnv = env;

  apr_status_t status;



  /* Initialize the APR subsystem, and register an atexit() function
   * to Uninitialize that subsystem at program exit. */
  status = apr_initialize();
  if (status)
    {
      if (stderr)
        {
          char buf[1024];
          apr_strerror(status, buf, sizeof(buf) - 1);
          fprintf(stderr,
                  "%s: error: cannot initialize APR: %s\n",
                  "svnjavahl", buf);
        }
      return FALSE;
    }

  /* This has to happen before any pools are created. */
  if ((err = svn_dso_initialize2()))
    {
      if (stderr && err->message)
        fprintf(stderr, "%s", err->message);

      svn_error_clear(err);
      return FALSE;
    }

  if (0 > atexit(apr_terminate))
    {
      if (stderr)
        fprintf(stderr,
                "%s: error: atexit registration failed\n",
                "svnjavahl");
      return FALSE;
    }

  /* Create our top-level pool. */
  g_pool = svn_pool_create(NULL);

  apr_allocator_t* allocator = apr_pool_allocator_get(g_pool);

  if (allocator)
    {
      /* Keep a maximum of 1 free block, to release memory back to the JVM
         (and other modules). */
      apr_allocator_max_free_set(allocator, 1);
    }

  svn_utf_initialize2(FALSE, g_pool); /* Optimize character conversions */
  svn_fs_initialize(g_pool); /* Avoid some theoretical issues */
  svn_ra_initialize(g_pool);

  /* We shouldn't fill the JVMs memory with FS cache data unless explictly
     requested. */
  {
    svn_cache_config_t settings = *svn_cache_config_get();
    settings.cache_size = 0;
    settings.file_handle_count = 0;
    settings.single_threaded = FALSE;
    svn_cache_config_set(&settings);
  }

#ifdef ENABLE_NLS
#ifdef WIN32
  {
    WCHAR ucs2_path[MAX_PATH];
    char *utf8_path;
    const char *internal_path;
    apr_pool_t *pool;
    apr_status_t apr_err;
    apr_size_t inwords, outbytes;
    unsigned int outlength;

    pool = svn_pool_create(g_pool);
    /* get dll name - our locale info will be in '../share/locale' */
    inwords = sizeof(ucs2_path) / sizeof(ucs2_path[0]);
    HINSTANCE moduleHandle = GetModuleHandle("libsvnjavahl-1");
    GetModuleFileNameW(moduleHandle, ucs2_path, inwords);
    inwords = lstrlenW(ucs2_path);
    outbytes = outlength = 3 * (inwords + 1);
    utf8_path = reinterpret_cast<char *>(apr_palloc(pool, outlength));
    apr_err = apr_conv_ucs2_to_utf8((const apr_wchar_t *) ucs2_path,
                                    &inwords, utf8_path, &outbytes);
    if (!apr_err && (inwords > 0 || outbytes == 0))
      apr_err = APR_INCOMPLETE;
    if (apr_err)
      {
        if (stderr)
          fprintf(stderr, "Can't convert module path to UTF-8");
        return FALSE;
      }
    utf8_path[outlength - outbytes] = '\0';
    internal_path = svn_dirent_internal_style(utf8_path, pool);
    /* get base path name */
    internal_path = svn_dirent_dirname(internal_path, pool);
    internal_path = svn_dirent_join(internal_path, SVN_LOCALE_RELATIVE_PATH,
                                  pool);
    bindtextdomain(PACKAGE_NAME, internal_path);
    svn_pool_destroy(pool);
  }
#else
  bindtextdomain(PACKAGE_NAME, SVN_LOCALE_DIR);
#endif
#endif

#if defined(WIN32) || defined(__CYGWIN__)
  /* See http://svn.apache.org/repos/asf/subversion/trunk/notes/asp-dot-net-hack.txt */
  /* ### This code really only needs to be invoked by consumers of
     ### the libsvn_wc library, which basically means SVNClient. */
  if (getenv("SVN_ASP_DOT_NET_HACK"))
    {
      err = svn_wc_set_adm_dir("_svn", g_pool);
      if (err)
        {
          if (stderr)
            {
              fprintf(stderr,
                      "%s: error: SVN_ASP_DOT_NET_HACK failed: %s\n",
                      "svnjavahl", err->message);
            }
          svn_error_clear(err);
          return FALSE;
        }
    }
#endif

  svn_error_set_malfunction_handler(svn_error_raise_on_malfunction);

  // Build all mutexes.
  g_finalizedObjectsMutex = new JNIMutex(g_pool);
  if (isExceptionThrown())
    return false;

  g_logMutex = new JNIMutex(g_pool);
  if (isExceptionThrown())
    return false;

  // initialized the thread local storage
  if (!JNIThreadData::initThreadData())
    return false;

  setEnv(env);
  if (isExceptionThrown())
    return false;

  g_initEnv = NULL;
  g_inInit = false;
  return true;
}