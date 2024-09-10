/**
 * Create a tempfile with the given prefix (e.g. "wireshark").
 *
 * @param namebuf If not NULL, receives the full path of the temp file.
 *                Should NOT be freed.
 * @param pfx A prefix for the temporary file.
 * @param sfx [in] A file extension for the temporary file. NULL can be passed
 *                 if no file extension is needed
 * @return The file descriptor of the new tempfile, from mkstemps().
 */
int
create_tempfile(char **namebuf, const char *pfx, const char *sfx)
{
  static struct _tf {
    char *path;
    size_t len;
  } tf[MAX_TEMPFILES];
  static int idx;

  const char *tmp_dir;
  int old_umask;
  int fd;
  time_t current_time;
  char timestr[14 + 1];
  gchar *tmp_file;
  gchar *safe_pfx;
  gchar sep[2] = {0, 0};

  /* The characters in "delimiters" come from:
   * http://msdn.microsoft.com/en-us/library/aa365247%28VS.85%29.aspx.
   * Add to the list as necessary for other OS's.
   */
  const gchar *delimiters = "<>:\"/\\|?*"
    "\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a"
    "\x0b\x0c\x0d\x0e\x0f\x10\x11\x12\x13\x14"
    "\x15\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f";

  /* Sanitize the pfx to resolve bug 7877 */
  safe_pfx = g_strdup(pfx);
  safe_pfx = g_strdelimit(safe_pfx, delimiters, '-');

  idx = (idx + 1) % MAX_TEMPFILES;

  /*
   * Allocate the buffer if it's not already allocated.
   */
  if (tf[idx].path == NULL) {
    tf[idx].len = INITIAL_PATH_SIZE;
    tf[idx].path = (char *)g_malloc(tf[idx].len);
  }

  tmp_dir = g_get_tmp_dir();

#ifdef _WIN32
  _tzset();
#endif
  current_time = time(NULL);
  /* We trust the OS not to return a time before the Epoch. */
  strftime(timestr, sizeof(timestr), "%Y%m%d%H%M%S", localtime(&current_time));
  sep[0] = G_DIR_SEPARATOR;
  tmp_file = g_strconcat(tmp_dir, sep, safe_pfx, "_", timestr, "_", TMP_FILE_SUFFIX, sfx, NULL);
  g_free(safe_pfx);
  if (strlen(tmp_file) > tf[idx].len) {
    tf[idx].len = strlen(tmp_file) + 1;
    tf[idx].path = (char *)g_realloc(tf[idx].path, tf[idx].len);
  }
  g_strlcpy(tf[idx].path, tmp_file, tf[idx].len);
  g_free(tmp_file);

  if (namebuf) {
    *namebuf = tf[idx].path;
  }
  /* The Single UNIX Specification doesn't say that "mkstemps()"
     creates the temporary file with mode rw-------, so we
     won't assume that all UNIXes will do so; instead, we set
     the umask to 0077 to take away all group and other
     permissions, attempt to create the file, and then put
     the umask back. */
  old_umask = ws_umask(0077);
  fd = mkstemps(tf[idx].path, sfx ? (int) strlen(sfx) : 0);
  ws_umask(old_umask);
  return fd;
}