/* Parse WCS into tokens separated by characters in DELIM.  If WCS is
   NULL, the last string wcstok() was called with is used.  */
wchar_t *
wcstok (wchar_t *wcs, const wchar_t *delim, wchar_t **save_ptr)
{
  wchar_t *result;

  if (wcs == NULL)
    {
      if (*save_ptr == NULL)
	{
	  __set_errno (EINVAL);
	  return NULL;
	}
      else
	wcs = *save_ptr;
    }

  /* Scan leading delimiters.  */
  wcs += wcsspn (wcs, delim);
  if (*wcs == L'\0')
    {
      *save_ptr = NULL;
      return NULL;
    }

  /* Find the end of the token.	 */
  result = wcs;
  wcs = wcspbrk (result, delim);
  if (wcs == NULL)
    /* This token finishes the string.	*/
    *save_ptr = NULL;
  else
    {
      /* Terminate the token and make *SAVE_PTR point past it.  */
      *wcs = L'\0';
      *save_ptr = wcs + 1;
    }
  return result;
}