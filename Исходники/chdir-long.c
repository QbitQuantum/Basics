int
chdir_long (char *dir)
{
  int e = chdir (dir);
  if (e == 0 || errno != ENAMETOOLONG)
    return e;

  {
    size_t len = strlen (dir);
    char *dir_end = dir + len;
    struct cd_buf cdb;
    size_t n_leading_slash;

    cdb_init (&cdb);

    /* If DIR is the empty string, then the chdir above
       must have failed and set errno to ENOENT.  */
    assert (0 < len);
    assert (PATH_MAX <= len);

    /* Count leading slashes.  */
    n_leading_slash = strspn (dir, "/");

    /* Handle any leading slashes as well as any name that matches
       the regular expression, m!^//hostname[/]*! .  Handling this
       prefix separately usually results in a single additional
       cdb_advance_fd call, but it's worthwhile, since it makes the
       code in the following loop cleaner.  */
    if (n_leading_slash == 2)
      {
        int err;
        /* Find next slash.
           We already know that dir[2] is neither a slash nor '\0'.  */
        char *slash = memchr (dir + 3, '/', dir_end - (dir + 3));
        if (slash == NULL)
          {
            errno = ENAMETOOLONG;
            return -1;
          }
        *slash = '\0';
        err = cdb_advance_fd (&cdb, dir);
        *slash = '/';
        if (err != 0)
          goto Fail;
        dir = find_non_slash (slash + 1);
      }
    else if (n_leading_slash)
      {
        if (cdb_advance_fd (&cdb, "/") != 0)
          goto Fail;
        dir += n_leading_slash;
      }

    assert (*dir != '/');
    assert (dir <= dir_end);

    while (PATH_MAX <= dir_end - dir)
      {
        int err;
        /* Find a slash that is PATH_MAX or fewer bytes away from dir.
           I.e. see if there is a slash that will give us a name of
           length PATH_MAX-1 or less.  */
        char *slash = memrchr (dir, '/', PATH_MAX);
        if (slash == NULL)
          {
            errno = ENAMETOOLONG;
            return -1;
          }

        *slash = '\0';
        assert (slash - dir < PATH_MAX);
        err = cdb_advance_fd (&cdb, dir);
        *slash = '/';
        if (err != 0)
          goto Fail;

        dir = find_non_slash (slash + 1);
      }

    if (dir < dir_end)
      {
        if (cdb_advance_fd (&cdb, dir) != 0)
          goto Fail;
      }

    if (cdb_fchdir (&cdb) != 0)
      goto Fail;

    cdb_free (&cdb);
    return 0;

   Fail:
    {
      int saved_errno = errno;
      cdb_free (&cdb);
      errno = saved_errno;
      return -1;
    }
  }
}