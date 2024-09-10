static char *
mbstrstr (const char *haystack, const char *needle)
{
#if DO_MULTIBYTE
  if (MB_CUR_MAX > 1)
    {
      size_t hlen = strlen (haystack);
      size_t nlen = strlen (needle);
      mbstate_t mbstate;
      size_t step;

      memset (&mbstate, 0, sizeof (mbstate_t));
      while (hlen >= nlen)
        {
          if (memcmp (haystack, needle, nlen) == 0)
            return (char *) haystack;
          step = mbrlen (haystack, hlen, &mbstate);
          if (step <= 0)
            break;
          haystack += step;
          hlen -= step;
        }
      return NULL;
    }
#endif
  return strstr (haystack, needle);
}