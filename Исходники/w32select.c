static HGLOBAL
convert_to_handle_as_ascii (void)
{
  HGLOBAL htext = NULL;
  int nbytes;
  int truelen;
  unsigned char *src;
  unsigned char *dst;

  ONTRACE (fprintf (stderr, "convert_to_handle_as_ascii\n"));

  nbytes = SBYTES (current_text) + 1;
  src = SDATA (current_text);

  /* We need to add to the size the number of LF chars where we have
     to insert CR chars (the standard CF_TEXT clipboard format uses
     CRLF line endings, while Emacs uses just LF internally).  */

  truelen = nbytes + current_num_nls;

  if ((htext = GlobalAlloc (GMEM_MOVEABLE | GMEM_DDESHARE, truelen)) == NULL)
    return NULL;

  if ((dst = (unsigned char *) GlobalLock (htext)) == NULL)
    {
      GlobalFree (htext);
      return NULL;
    }

  /* convert to CRLF line endings expected by clipboard */
  while (1)
    {
      unsigned char *next;
      /* copy next line or remaining bytes including '\0' */
      next = _memccpy (dst, src, '\n', nbytes);
      if (next)
	{
	  /* copied one line ending with '\n' */
	  int copied = next - dst;
	  nbytes -= copied;
	  src += copied;
	  /* insert '\r' before '\n' */
	  next[-1] = '\r';
	  next[0] = '\n';
	  dst = next + 1;
	}
      else
	/* copied remaining partial line -> now finished */
	break;
    }

  GlobalUnlock (htext);

  return htext;
}