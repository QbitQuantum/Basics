static gboolean _rox_buffer_looks_like_text (const void  *data,
					    const size_t len)
{
  gchar *end;

  if (g_utf8_validate (data, len, (const gchar**)&end))
  {
    /* g_utf8_validate allows control characters */
    int i;
    for (i = 0; i < len; i++)
    {
      unsigned char c = ((const guchar *) data)[i];
      if (c < 32 && c != '\r' && c != '\n' && c != '\t')
	return FALSE;
    }
    return TRUE;

  } else {
    /* Check whether the string was truncated in the middle of
     * a valid UTF8 char, or if we really have an invalid
     * UTF8 string
     */
    gint remaining_bytes = len;

    remaining_bytes -= (end-((gchar*)data));

    if (g_utf8_get_char_validated(end, remaining_bytes) == -2)
      return TRUE;
#if defined(HAVE_WCTYPE_H) && defined (HAVE_MBRTOWC)
    else {
      size_t wlen;
      wchar_t wc;
      gchar *src, *end;
      mbstate_t state;

      src = data;
      end = data+len;
                       
      memset (&state, 0, sizeof (state));
      while (src < end) {
	/* Don't allow embedded zeros in textfiles */
	if (*src == 0)
	  return FALSE;
                               
	wlen = mbrtowc(&wc, src, end - src, &state);

	if (wlen == (size_t)(-1)) {
	  /* Illegal mb sequence */
	  return FALSE;
	}
                               
	if (wlen == (size_t)(-2)) {
	  /* No complete mb char before end
	   * Probably a cut off char which is ok */
	  return TRUE;
	}

	if (wlen == 0) {
	  /* Don't allow embedded zeros in textfiles */
	  return FALSE;
	}
        
	if (!iswspace (wc)  && !iswprint(wc)) {
	  /* Not a printable or whitspace
	   * Probably not a text file */
	  return FALSE;
	}
	
	src += wlen;
      }
      return TRUE;
    }
#endif /* defined(HAVE_WCTYPE_H) && defined (HAVE_MBRTOWC) */
  }
  return FALSE;
}