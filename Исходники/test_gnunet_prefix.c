int
main (int argc,
      char **argv)
{
  const char *basename;
  const char *dirname;

  basename = getenv ("GNUNET_PREFIX");
  if (NULL == basename)
  {
    fprintf (stderr,
	     _("Environment variable GNUNET_PREFIX not set\n"));
    fprintf (stderr,
	     _("Testcases will not work!\n"));
    return 1;
  }
  dirname = DIR_SEPARATOR_STR ".." DIR_SEPARATOR_STR "share" DIR_SEPARATOR_STR "gnunet" DIR_SEPARATOR_STR "config.d";
  {
    char tmp[strlen (basename) + strlen (dirname) + 1];
    sprintf (tmp, "%s%s", basename, dirname);
    if (0 != access (tmp, R_OK))
    {
      fprintf (stderr,
	       _("Failed to access `%s': %s\n"),
	       tmp,
	       STRERROR (errno));
      fprintf (stderr,
	       _("Check that you did run `make install' and that GNUNET_PREFIX='%s' is the correct prefix.\n"),
	       basename);
      fprintf (stderr,
	       _("Testcases will not work!\n"));
      return 2;
    }
  }
  return 0;
}