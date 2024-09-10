/* Search string for url. Fix up url if needed. */
static char        *
validate_url(char *url)
{
   char               *p;
   char               *ret = NULL;
   static char        *orig_ret = NULL;

   D(("In validate_url: url -->%s<--\n", url));

   if (!url)
      return NULL;

   if (orig_ret)
      free(orig_ret);

   ret = orig_ret = _Strdup(url);

   /* First, try searching for http://, in case there is a lot of text,
    * with an embedded url somewhere inside... */
   p = strstr(ret, "http://");
   if (p)
      ret = p;
   else
     {
	/* Ok. No "http://", maybe a "www." ? */
	p = strstr(ret, "http://");
	if (p)
	   ret = p;
     }

   /* Kill at end of line */
   p = strchr(ret, '\n');
   if (p)
      *p = '\0';

   /* Skip first spaces */
   p = ret;
   while (*p == ' ')
      p++;
   ret = p;

   /* Kill at next space */
   p = strchr(ret, ' ');
   if (p)
      *p = '\0';

   /* If just www.blah, add the http:// to avoid confusing nutscrape */
   if (*ret == 'w' && *(ret + 1) == 'w' && *(ret + 2) == 'w')
     {
	char               *temp = _Strjoin(NULL, "http://", ret, NULL);

	free(orig_ret);
	ret = _Strdup(temp);
	free(temp);
     }

   D(("In validate_url: ret -->%s<--\n", ret));

   /* Now some checks */
   if (strlen(ret) < 1)
      return 0;
   if (*ret == '-')
      return 0;

   return ret;
}