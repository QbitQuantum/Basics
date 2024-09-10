int
fnmatch (const char *pattern, const char *string, int flags)
{
# if HANDLE_MULTIBYTE
#  define ALLOCA_LIMIT 2000
  if (__builtin_expect (MB_CUR_MAX, 1) != 1)
    {
      mbstate_t ps;
      size_t patsize;
      size_t strsize;
      size_t totsize;
      wchar_t *wpattern;
      wchar_t *wstring;
      int res;

      /* Calculate the size needed to convert the strings to
         wide characters.  */
      memset (&ps, '\0', sizeof (ps));
      patsize = mbsrtowcs (NULL, &pattern, 0, &ps) + 1;
      if (__builtin_expect (patsize != 0, 1))
        {
          assert (mbsinit (&ps));
          strsize = mbsrtowcs (NULL, &string, 0, &ps) + 1;
          if (__builtin_expect (strsize != 0, 1))
            {
              assert (mbsinit (&ps));
              totsize = patsize + strsize;
              if (__builtin_expect (! (patsize <= totsize
                                       && totsize <= SIZE_MAX / sizeof (wchar_t)),
                                    0))
                {
                  errno = ENOMEM;
                  return -1;
                }

              /* Allocate room for the wide characters.  */
              if (__builtin_expect (totsize < ALLOCA_LIMIT, 1))
                wpattern = (wchar_t *) alloca (totsize * sizeof (wchar_t));
              else
                {
                  wpattern = malloc (totsize * sizeof (wchar_t));
                  if (__builtin_expect (! wpattern, 0))
                    {
                      errno = ENOMEM;
                      return -1;
                    }
                }
              wstring = wpattern + patsize;

              /* Convert the strings into wide characters.  */
              mbsrtowcs (wpattern, &pattern, patsize, &ps);
              assert (mbsinit (&ps));
              mbsrtowcs (wstring, &string, strsize, &ps);

              res = internal_fnwmatch (wpattern, wstring, wstring + strsize - 1,
                                       flags & FNM_PERIOD, flags);

              if (__builtin_expect (! (totsize < ALLOCA_LIMIT), 0))
                free (wpattern);
              return res;
            }
        }
    }

# endif /* HANDLE_MULTIBYTE */

  return internal_fnmatch (pattern, string, string + strlen (string),
                           flags & FNM_PERIOD, flags);
}