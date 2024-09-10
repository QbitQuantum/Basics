 char* xbp__tempnam(const char *dir, const char *prefix)
 {
   char* p = strdup(dir);
   CORRECT_SEP_STR(p);
   char* res = _tempnam(p, prefix);
   free(p);
   return strdup(res);
 }