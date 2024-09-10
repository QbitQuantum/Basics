static void PutString(char *pszStr, int bCR)
{
   int rval;
   char  *pszBS;

   if (g_bRedirected)
   {
      rval = (bCR ? puts(pszStr) : fputs(pszStr, stdout));
      if (rval)
      {
         fputs("\nCannot write to stdout.\n", stderr);
         exit(-1);
      }
   }
   else
   {
      pszBS = strchr(pszStr, '\b');
      while (pszBS)
      {
         *pszBS = '\0';
         OutText(pszStr);
         fputchar('\b');
         pszStr = pszBS + 1;
         pszBS = strchr(pszStr, '\b');
      }
      OutText(pszStr);
      if (bCR)
         OutText("\r\n");
   }
}