static int
update_usersfile (const char *usersfile,
		  const char *username,
		  const char *otp,
		  FILE * infh,
		  char **lineptr,
		  size_t * n, char *timestamp, uint64_t new_moving_factor)
{
  FILE *outfh, *lockfh;
  int rc;
  char *newfilename, *lockfile;

  /* Rewind input file. */
  {
    int pos;

    pos = fseeko (infh, 0L, SEEK_SET);
    if (pos == -1)
      return OATH_FILE_SEEK_ERROR;
    clearerr (infh);
  }

  /* Open lockfile. */
  {
    int l;

    l = asprintf (&lockfile, "%s.lock", usersfile);
    if (lockfile == NULL || ((size_t) l) != strlen (usersfile) + 5)
      return OATH_PRINTF_ERROR;

    lockfh = fopen (lockfile, "w");
    if (!lockfh)
      {
	free (lockfile);
	return OATH_FILE_CREATE_ERROR;
      }
  }

  /* Lock the lockfile. */
  {
    struct flock l;

    memset (&l, 0, sizeof (l));
    l.l_whence = SEEK_SET;
    l.l_start = 0;
    l.l_len = 0;
    l.l_type = F_WRLCK;

    while ((rc = fcntl (fileno (lockfh), F_SETLKW, &l)) < 0 && errno == EINTR)
      continue;
    if (rc == -1)
      {
	fclose (lockfh);
	free (lockfile);
	return OATH_FILE_LOCK_ERROR;
      }
  }

  /* Open the "new" file. */
  {
    int l;

    l = asprintf (&newfilename, "%s.new", usersfile);
    if (newfilename == NULL || ((size_t) l) != strlen (usersfile) + 4)
      {
	fclose (lockfh);
	free (lockfile);
	return OATH_PRINTF_ERROR;
      }

    outfh = fopen (newfilename, "w");
    if (!outfh)
      {
	free (newfilename);
	fclose (lockfh);
	free (lockfile);
	return OATH_FILE_CREATE_ERROR;
      }
  }

  rc = update_usersfile2 (username, otp, infh, outfh, lineptr, n,
			  timestamp, new_moving_factor);

  fclose (lockfh);
  fclose (outfh);

  {
    int tmprc1, tmprc2;

    tmprc1 = rename (newfilename, usersfile);
    free (newfilename);

    tmprc2 = unlink (lockfile);
    free (lockfile);

    if (tmprc1 == -1)
      return OATH_FILE_RENAME_ERROR;
    if (tmprc2 == -1)
      return OATH_FILE_UNLINK_ERROR;
  }

  return rc;
}