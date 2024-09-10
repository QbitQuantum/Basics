static int test_tempdir(const char *temp_dir)
{
  char *tpath = NULL;
  int fd = -1;
  int rv = asprintf(&tpath, "%s/tmp.XXXXXX", temp_dir);

#ifdef _WIN32
  _mktemp_s(tpath, strlen(tpath));
  fd = open(tpath, O_CREAT|O_WRONLY);
#else
  fd = mkstemp(tpath);
#endif

  if (fd == -1) {
    free(tpath);
    return 1;
  }

  rv = write(fd, "!", 1);
  if (rv != 1) {
    close(fd);
#ifdef _WIN32
    _unlink(tpath);
#endif
    free(tpath);
    return 1;
  }

  close(fd);
#ifdef _WIN32
  _unlink(tpath);
#endif
  free(tpath);
  return 0;
}