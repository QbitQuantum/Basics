int					/* O - 1 on success, 0 on error */
translate_messages(cups_array_t *cat,	/* I - Message catalog */
                   const char *lang)	/* I - Output language... */
{
 /*
  * Google provides a simple translation/language tool for translating
  * from one language to another.  It is far from perfect, however it
  * can be used to get a basic translation done or update an existing
  * translation when no other resources are available.
  *
  * Translation requests are sent as HTTP POSTs to
  * "http://translate.google.com/translate_t" with the following form
  * variables:
  *
  *   Name      Description                         Value
  *   --------  ----------------------------------  ----------------
  *   hl        Help language?                      "en"
  *   ie        Input encoding                      "UTF8"
  *   langpair  Language pair                       "en|" + language
  *   oe        Output encoding                     "UTF8"
  *   text      Text to translate                   translation string
  */

  int		ret;			/* Return value */
  _cups_message_t *m;			/* Current message */
  int		tries;			/* Number of tries... */
  http_t	*http;			/* HTTP connection */
  http_status_t	status;			/* Status of POST request */
  char		*idptr,			/* Pointer into msgid */
		buffer[65536],		/* Input/output buffer */
		*bufptr,		/* Pointer into buffer */
		*bufend,		/* Pointer to end of buffer */
		length[16];		/* Content length */
  int		bytes;			/* Number of bytes read */


 /*
  * Connect to translate.google.com...
  */

  puts("Connecting to translate.google.com...");

  if ((http = httpConnect("translate.google.com", 80)) == NULL)
  {
    perror("Unable to connect to translate.google.com");
    return (0);
  }

 /*
  * Scan the current messages, requesting a translation of any untranslated
  * messages...
  */

  for (m = (_cups_message_t *)cupsArrayFirst(cat), ret = 1;
       m;
       m = (_cups_message_t *)cupsArrayNext(cat))
  {
   /*
    * Skip messages that are already translated...
    */

    if (m->str && m->str[0])
      continue;

   /*
    * Encode the form data into the buffer...
    */

    snprintf(buffer, sizeof(buffer),
             "hl=en&ie=UTF8&langpair=en|%s&oe=UTF8&text=", lang);
    bufptr = buffer + strlen(buffer);
    bufend = buffer + sizeof(buffer) - 5;

    for (idptr = m->id; *idptr && bufptr < bufend; idptr ++)
      if (*idptr == ' ')
        *bufptr++ = '+';
      else if (*idptr < ' ' || *idptr == '%')
      {
        sprintf(bufptr, "%%%02X", *idptr & 255);
	bufptr += 3;
      }
      else if (*idptr != '&')
        *bufptr++ = *idptr;

    *bufptr++ = '&';
    *bufptr = '\0';

    sprintf(length, "%d", (int)(bufptr - buffer));

   /*
    * Send the request...
    */

    printf("\"%s\" = ", m->id);
    fflush(stdout);

    tries = 0;

    do
    {
      httpClearFields(http);
      httpSetField(http, HTTP_FIELD_CONTENT_TYPE,
                   "application/x-www-form-urlencoded");
      httpSetField(http, HTTP_FIELD_CONTENT_LENGTH, length);

      if (httpPost(http, "/translate_t"))
      {
	httpReconnect(http);
	httpPost(http, "/translate_t");
      }

      httpWrite2(http, buffer, bufptr - buffer);

      while ((status = httpUpdate(http)) == HTTP_CONTINUE);

      if (status != HTTP_OK && status != HTTP_ERROR)
        httpFlush(http);

      tries ++;
    }
    while (status == HTTP_ERROR && tries < 10);

    if (status == HTTP_OK)
    {
     /*
      * OK, read the translation back...
      */

      bufptr = buffer;
      bufend = buffer + sizeof(buffer) - 1;

      while ((bytes = httpRead2(http, bufptr, bufend - bufptr)) > 0)
        bufptr += bytes;

      if (bytes < 0)
      {
       /*
        * Read error, abort!
	*/

        puts("READ ERROR!");
	ret = 0;
	break;
      }

      *bufptr = '\0';

     /*
      * Find the div containing translation
      */

      if ((bufptr = strstr(buffer, "<div id=result_box")) == NULL)
      {
       /*
        * No textarea, abort!
	*/

        puts("NO div id=result_box!");
	ret = 0;
	break;
      }

      if ((bufptr = strchr(bufptr, '>')) == NULL)
      {
       /*
        * textarea doesn't end, abort!
	*/

        puts("DIV SHORT DATA!");
	ret = 0;
	break;
      }

      bufptr ++;

      if ((bufend = strstr(bufptr, "</div>")) == NULL)
      {
       /*
        * textarea doesn't close, abort!
	*/

        puts("/DIV SHORT DATA!");
	ret = 0;
	break;
      }

      *bufend = '\0';

     /*
      * Copy the translation...
      */

      m->str = strdup(bufptr);

     /*
      * Convert character entities to regular chars...
      */

      for (bufptr = strchr(m->str, '&');
           bufptr;
	   bufptr = strchr(bufptr + 1, '&'))
      {
        if (!strncmp(bufptr, "&lt;", 4))
	{
	  *bufptr = '<';
	  _cups_strcpy(bufptr + 1, bufptr + 4);
	}
        else if (!strncmp(bufptr, "&gt;", 4))
	{
	  *bufptr = '>';
	  _cups_strcpy(bufptr + 1, bufptr + 4);
	}
        else if (!strncmp(bufptr, "&amp;", 5))
	  _cups_strcpy(bufptr + 1, bufptr + 5);
      }

      printf("\"%s\"\n", m->str);
    }
    else if (status == HTTP_ERROR)
    {
      printf("NETWORK ERROR (%s)!\n", strerror(httpError(http)));
      ret = 0;
      break;
    }
    else
    {
      printf("HTTP ERROR %d!\n", status);
      ret = 0;
      break;
    }
  }

  httpClose(http);

  return (ret);
}