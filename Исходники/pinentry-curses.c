static CH *
utf8_to_local (char *lc_ctype, char *string)
{
  mbstate_t ps;
  size_t len;
  char *local;
  const char *p;
  wchar_t *wcs = NULL;
  char *old_ctype = NULL;

  local = pinentry_utf8_to_local (lc_ctype, string);
  if (!local)
    return NULL;

  old_ctype = strdup (setlocale (LC_CTYPE, NULL));
  setlocale (LC_CTYPE, lc_ctype? lc_ctype : "");

  p = local;
  memset (&ps, 0, sizeof(mbstate_t));
  len = mbsrtowcs (NULL, &p, strlen (string), &ps);
  if (len == (size_t)-1)
    {
      free (local);
      goto leave;
    }
  wcs = calloc (len + 1, sizeof(wchar_t));
  if (!wcs)
    {
      free (local);
      goto leave;
    }

  p = local;
  memset (&ps, 0, sizeof(mbstate_t));
  mbsrtowcs (wcs, &p, len, &ps);

  free (local);

 leave:
  if (old_ctype)
    {
      setlocale (LC_CTYPE, old_ctype);
      free (old_ctype);
    }

  return wcs;
}