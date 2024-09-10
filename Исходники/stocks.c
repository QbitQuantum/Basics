yahoo_source find_yahoo_source(char *symbol)
{
  char *ptr;
  int i;
  int test;

  ptr = strrchr(symbol, '.');

  /* If no extension we suppose it is a US stock */
  if (!ptr) return YAHOO_US;

  /* extension is found */

  /* Test if it is canadian stock */
  for (i=0; i<YAHOO_US_EXT_NB; i++)
    {

#ifdef __UNIX__
      test = strcasecmp(yahoo_us_ext[i], ptr);
#elif __WINDOWS__
      test = _mbsnbicmp(yahoo_us_ext[i], ptr, strlen(yahoo_us_ext[i]));
#endif

      if (!test) return YAHOO_US;
    }

  /* We suppose now it is a European stock */
  return YAHOO_EUROPE;
}