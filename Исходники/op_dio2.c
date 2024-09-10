Private bool valid_name(char * p)
{
 bool status = FALSE;

 if ((strcmp(p, ".") == 0) || (strcmp(p, "..") == 0)) return TRUE;

 if (strlen(p) > 0)
  {
   while(((*p == ' ') || IsGraph(*p)) && (strchr(df_restricted_chars, *p) == NULL))
    {
     p++;
    }
  status = (*p == '\0');
 }

 return status;
}