// strnicmp that does not respect the locale: for ascii comparisons only
int
strnicmp_ignore_locale(const char *s1, const char *s2, size_t length)
   {
   LOCALE_DEF;
   if (USE_LOCALE)
      return STRNICMP(s1, s2, length);

   while (length-- > 0)
      {
      char c1 = *s1++;
      char c2 = *s2++;
      int diff = tolower_ignore_locale(c1) - tolower_ignore_locale(c2);
      if (diff != 0)
         {
         return diff;
         }
      else
         {
         if('\0' == c1)
            {
            return 0;
            }
         }
      }
      return 0;
   }