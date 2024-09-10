static void
__tar_read_dir_file (void)
{
  dev_t dev;
  ino_t ino;
  char *strp;
  FILE *fp;
  char buf[512];
  static char *path = 0;

  if (path == 0)
    path = tar_xmalloc (PATH_MAX);
  time (&this_time);
  if (gnu_dumpfile[0] != '/')
    {
#ifdef HAVE_GETCWD
      if (!getcwd (path, PATH_MAX))
	ERROR ((TAREXIT_FAILURE, 0, _("Could not get current directory")));
#else
      char *getwd ();

      if (!getwd (path))
	ERROR ((TAREXIT_FAILURE, 0, _("Could not get current directory: %s"),
		path));
#endif

      /* If this doesn't fit, we're in serious trouble.  */

      strcat (path, "/");
      strcat (path, gnu_dumpfile);
      gnu_dumpfile = path;
    }
  fp = fopen (gnu_dumpfile, "r");
  if (fp == 0 && errno != ENOENT)
    {
      ERROR ((0, errno, _("Cannot open %s"), gnu_dumpfile));
      return;
    }
  if (!fp)
    return;
  fgets (buf, sizeof (buf), fp);
  if (!flag_new_files)
    {
      flag_new_files++;
      new_time = atol (buf);
    }
  while (fgets (buf, sizeof (buf), fp))
    {
      strp = &buf[strlen (buf)];
      if (strp[-1] == '\n')
	strp[-1] = '\0';
      strp = buf;
      dev = atol (strp);
      while (ISDIGIT (*strp))
	strp++;
      ino = atol (strp);
      while (ISSPACE (*strp))
	strp++;
      while (ISDIGIT (*strp))
	strp++;
      strp++;
      __tar_add_dir (__tar_un_quote_string (strp), dev, ino, (char *) 0);
    }
  fclose (fp);
}