/**
 * Check whether a string starts with a specific string.
 * This check is case sensitive.
 * 
 * This is a slibc extension.
 * 
 * @param   string   The string to inspect.
 * @param   desired  The desired beginning of the string.
 * @return           `string` if `string` begins with
 *                   `desired`, `NULL` otherwise.
 * 
 * @since  Always.
 */
wchar_t* (wcsstarts)(const wchar_t* string, const wchar_t* desired)
{
  size_t n = wcslen(string);
  size_t m = wcslen(desired);
  if (n < m)
    return NULL;
  return wmemcmp(string, desired, m) ? NULL : string;
}