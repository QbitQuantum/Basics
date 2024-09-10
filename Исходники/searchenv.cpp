void searchenv(char *filename, int fnsz, char *envname, char *pathname, int pthsz)
{
   static char pbuf[5000];
   char *p, *np;
   size_t len;
//   char *strpbrk(), *strtok(), *getenv();

   strcpy_s(pathname, pthsz, filename);
   if (_access(pathname, 0) != -1)
      return;

   /* ----------------------------------------------------------------------
         The file doesn't exist in the current directory. If a specific
      path was requested (ie. file contains \ or /) or if the environment
      isn't set, return a NULL, else search for the file on the path.
   ---------------------------------------------------------------------- */
   _dupenv_s(&p, &len, envname);
   if (len==0)
   {
      *pathname = '\0';
      return;
   }

   strncpy_s(pbuf, sizeof(pbuf), p, sizeof(pbuf));
   np = nullptr;
   if (p = strtok_s(pbuf, ";", &np))
   {
      do
      {
		  if (p[strlen(p)-1]=='\\')
	         sprintf_s(pathname, pthsz-1, "%0.90s%s", p, filename);
		  else
	         sprintf_s(pathname, pthsz, "%0.90s\\%s", p, filename);

         if (_access(pathname, 0) >= 0)
            return;
      }
      while(p = strtok_s(NULL, ";", &np));
   }
   *pathname = 0;
}