DOUBLE
C_STRTOD (char const *nptr, char **endptr)
{
  DOUBLE r;

#ifdef LC_ALL_MASK

  locale_t locale = c_locale ();
  if (!locale)
    {
      if (endptr)
	*endptr = (char *) nptr;
      return 0; /* errno is set here */
    }

  r = STRTOD_L (nptr, endptr, locale);

#else

  char *saved_locale = setlocale (LC_NUMERIC, NULL);

  if (saved_locale)
    {
      saved_locale = strdup (saved_locale);
      if (saved_locale == NULL)
	{
	  if (endptr)
	    *endptr = (char *) nptr;
	  return 0; /* errno is set here */
	}
      setlocale (LC_NUMERIC, "C");
    }

  r = STRTOD (nptr, endptr);

  if (saved_locale)
    {
      int saved_errno = errno;

      setlocale (LC_NUMERIC, saved_locale);
      free (saved_locale);
      errno = saved_errno;
    }

#endif

  return r;
}