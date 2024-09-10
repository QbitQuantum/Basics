/**
 * Duplicate a string.
 * 
 * This is a GNU-compliant slibc extension.
 * 
 * @param   string  The string to duplicate.
 * @return          The new string. `NULL` is returned on error
 *                  and `errno` is set to indicate the error.
 * 
 * @throws  ENOMEM  The process could not allocate sufficient amount of memory.
 * 
 * @since  Always.
 */
wchar_t* wcsdup(const wchar_t* string)
{
  size_t n = wcslen(string) + 1;
  wchar_t* r = malloc(n * sizeof(char));
  return r == NULL ? NULL : wmemcpy(r, string, n);
}