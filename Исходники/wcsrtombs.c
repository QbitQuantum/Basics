size_t
rpl_wcsrtombs (char *dest, const wchar_t **srcp, size_t len, mbstate_t *ps)
{
  if (ps == NULL)
    ps = &_gl_wcsrtombs_state;
# if WCSRTOMBS_NULL_ARG_BUG
  if (dest == NULL)
    {
      const wchar_t *temp_src = *srcp;

      return wcsrtombs (NULL, &temp_src, len, ps);
    }
  else
# endif
    return wcsrtombs (dest, srcp, len, ps);
}