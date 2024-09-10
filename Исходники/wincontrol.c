boolean TS_AddExtension(char ** ppszExtList, char * psz)
{
   char *   pExt;
   
   if (!ppszExtList || !psz)
      return FALSE;

   if (*ppszExtList)
      pExt = REALLOC(*ppszExtList, STRLEN(*ppszExtList) + STRLEN(psz) + STRLEN(MP_EXT_SEPARATOR) + 1);
   else
      pExt = MALLOC(STRLEN(psz) + STRLEN(MP_EXT_SEPARATOR) + 1);

   if (!pExt)
      return FALSE;

   STRCAT(pExt, psz);
   STRCAT(pExt, MP_EXT_SEPARATOR);
   *ppszExtList = pExt;
   return TRUE;
}