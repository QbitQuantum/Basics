/* Return the windows error message, or the passed in error message on
   failure. */
static const char *
loadlibraryerror (const char *default_errmsg)
{
  size_t len;
  LOCALFREE (error_message);

  FormatMessageA (FORMAT_MESSAGE_ALLOCATE_BUFFER |
                  FORMAT_MESSAGE_FROM_SYSTEM |
                  FORMAT_MESSAGE_IGNORE_INSERTS,
                  NULL,
                  GetLastError (),
                  0,
                  (char *) &error_message,
                  0, NULL);

  /* Remove trailing CRNL */
  len = LT_STRLEN (error_message);
  if (len && error_message[len - 1] == '\n')
    error_message[--len] = LT_EOS_CHAR;
  if (len && error_message[len - 1] == '\r')
    error_message[--len] = LT_EOS_CHAR;

  return len ? error_message : default_errmsg;
}