/*
 * Mark character usage in *f based on the hexadecimal bitmap found in
 * string s.  A two-digit offset separated by a colon gives the initial
 * character code.  We have no way of knowing how many times each character
 * is used or how many strings get created when showing the characters so
 * we just estimate two usages per character and one string per pair of
 * usages.
 */
static void
includechars(fontdesctype *f, char *s)
{
   int b, c, d;
   int l = strlen(s);

   while (l > 0 && (s[l-1] == '\n' || s[l-1] == '\r'))
      s[--l] = 0;
   if (!ISXDIGIT(s[0]) || !ISXDIGIT(s[1]) || s[2]!=':'
         || strspn(s+3,"0123456789ABCDEFabcdef") < l-3) {
      fprintf(stderr, "%s\n", s);
      error("Bad syntax in included font usage table");
      return;
   }
   c = (xdig[(int)(s[0])] << 4) + xdig[(int)(s[1])];
   s += 2;
   while (*++s) {
      d = xdig[(int)*s];
      for (b=8; b!=0; b>>=1) {
         if ((d&b)!=0) {
            pagecost ++;
            (void) prescanchar(&f->chardesc[c]);
         }
         if (++c==256) return;
      }
   }
}