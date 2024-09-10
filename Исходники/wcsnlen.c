/**
 * `wchar_t` version of `strnlen`.
 * 
 * @param   str     The string.
 * @param   maxlen  The number of bytes to inspect, at most.
 * @return          The number of `wchar_t`:s before the
 *                  first NUL character. `maxlen` if no
 *                  NUL character was found.
 * 
 * @since  Always.
 */
size_t wcsnlen(const wchar_t* str, size_t maxlen)
{
  const wchar_t* end = wmemchr(str, 0, maxlen);
  return end == NULL ? maxlen : (size_t)(end - str);
}