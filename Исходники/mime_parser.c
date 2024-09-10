static char *FindNextContent(char *ptr,
			     char *content_end,
			     interesting_mime_headers *SubMimeHeaders,
			     interesting_mime_headers *m)
{
	char *next_boundary;
	char  tmp;

	if (IsAsciiEncoding(SubMimeHeaders)) {
		tmp = *content_end;
		*content_end = '\0';

		/** 
		 * ok, if we have a content length of the mime part, 
		 * try skipping the content on the search for the next
		 * boundary. since we don't trust the content_length
		 * to be all accurate, and suspect it to lose one digit 
		 * per line with a line length of 80 chars, we need 
		 * to start searching a little before..
		 */
				   
		if ((SubMimeHeaders->content_length != -1) &&
		    (SubMimeHeaders->content_length > 10))
		{
			char *pptr;
			long lines;
					
			lines = SubMimeHeaders->content_length / 80;
			pptr = ptr + SubMimeHeaders->content_length - lines - 10;
			if (pptr < content_end)
				ptr = pptr;
		}
			
		next_boundary = strstr(ptr, m->b[startary].Key);
		*content_end = tmp;
	}
	else {
		char *srch;
		/** 
		 * ok, if we have a content length of the mime part, 
		 * try skipping the content on the search for the next
		 * boundary. since we don't trust the content_length
		 * to be all accurate, start searching a little before..
		 */
				   
		if ((SubMimeHeaders->content_length != -1) &&
		    (SubMimeHeaders->content_length > 10))
		{
			char *pptr;
			pptr = ptr + SubMimeHeaders->content_length - 10;
			if (pptr < content_end)
				ptr = pptr;
		}
		

		srch = next_boundary = NULL;
		for (srch = memchr(ptr, '-',  content_end - ptr);
		     (srch != NULL) && (srch < content_end); 
		     srch = memchr(srch, '-',  content_end - srch)) 
		{
			if (!memcmp(srch, 
				    m->b[startary].Key, 
				    m->b[startary].len)) 
			{
				next_boundary = srch;
				srch = content_end;
			}
			else srch ++;

		}

	}
	return next_boundary;
}