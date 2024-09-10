// Format a Windows system or Winsock error message given an error code.
static const char *
format_errmsg (unsigned int errcode, const char *prefix)
{
  static const size_t errmsgsize = 1024;
  static char errmsg[errmsgsize];

  sprintf (errmsg, "%s: ", prefix);
  size_t len = strlen (errmsg);
  char *next = &errmsg[len];
  size_t max_fmt = errmsgsize - len;
  if (0 != FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM |
                          FORMAT_MESSAGE_IGNORE_INSERTS,
                          0,
                          errcode,
                          0,                 // Use default language
                          next,
                          (DWORD)max_fmt,
                          0))
    {
      strcat (errmsg, "\n");
      return errmsg;
    }

  errno = errcode;
  char *msg = _strerror (prefix);
  sprintf (errmsg, "err %d: %s", errcode, msg);
  return errmsg;
}