/**
 * Duplicate a string.
 * 
 * This is a slibc extension added for completeness.
 * It is only available if GNU extensions are available.
 * 
 * @param   string  The string to duplicate.
 * @param   maxlen  Truncate the string to this length, if it is longer.
 *                  A NUL wide character is guaranteed to always be
 *                  written upon successful completion.
 * @return          The new string. `NULL` is returned on error
 *                  and `errno` is set to indicate the error.
 * 
 * @throws  ENOMEM  The process could not allocate sufficient amount of memory.
 * 
 * @since  Always.
 */
wchar_t* wcsndup(const wchar_t* string, size_t maxlen)
{
  size_t n = wcsnlen(string, maxlen) + 1;
  wchar_t* r = malloc(n * sizeof(wchar_t));
  return r == NULL ? NULL : wmemcpy(r, string, n);
}