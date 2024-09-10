static size_t
multibyte_qmark_chars(char *buf, size_t len)
{
  if (MB_CUR_MAX <= 1)
    {
      return unibyte_qmark_chars(buf, len);
    }
  else
    {
      char const *p = buf;
      char const *plimit = buf + len;
      char *q = buf;

      while (p < plimit)
	switch (*p)
	  {
	  case ' ': case '!': case '"': case '#': case '%':
	  case '&': case '\'': case '(': case ')': case '*':
	  case '+': case ',': case '-': case '.': case '/':
	  case '0': case '1': case '2': case '3': case '4':
	  case '5': case '6': case '7': case '8': case '9':
	  case ':': case ';': case '<': case '=': case '>':
	  case '?':
	  case 'A': case 'B': case 'C': case 'D': case 'E':
	  case 'F': case 'G': case 'H': case 'I': case 'J':
	  case 'K': case 'L': case 'M': case 'N': case 'O':
	  case 'P': case 'Q': case 'R': case 'S': case 'T':
	  case 'U': case 'V': case 'W': case 'X': case 'Y':
	  case 'Z':
	  case '[': case '\\': case ']': case '^': case '_':
	  case 'a': case 'b': case 'c': case 'd': case 'e':
	  case 'f': case 'g': case 'h': case 'i': case 'j':
	  case 'k': case 'l': case 'm': case 'n': case 'o':
	  case 'p': case 'q': case 'r': case 's': case 't':
	  case 'u': case 'v': case 'w': case 'x': case 'y':
	  case 'z': case '{': case '|': case '}': case '~':
	    /* These characters are printable ASCII characters.  */
	    *q++ = *p++;
	    break;
	  default:
	    /* If we have a multibyte sequence, copy it until we
	       reach its end, replacing each non-printable multibyte
	       character with a single question mark.  */
	    {
	      mbstate_t mbstate;
	      memset (&mbstate, 0, sizeof mbstate);
	      do
		{
		  wchar_t wc;
		  size_t bytes;
		  int w;

		  bytes = mbrtowc (&wc, p, plimit - p, &mbstate);

		  if (bytes == (size_t) -1)
		    {
		      /* An invalid multibyte sequence was
			 encountered.  Skip one input byte, and
			 put a question mark.  */
		      p++;
		      *q++ = '?';
		      break;
		    }

		  if (bytes == (size_t) -2)
		    {
		      /* An incomplete multibyte character
			 at the end.  Replace it entirely with
			 a question mark.  */
		      p = plimit;
		      *q++ = '?';
		      break;
		    }

		  if (bytes == 0)
		    /* A null wide character was encountered.  */
		    bytes = 1;

		  w = wcwidth (wc);
		  if (w >= 0)
		    {
		      /* A printable multibyte character.
			 Keep it.  */
		      for (; bytes > 0; --bytes)
			*q++ = *p++;
		    }
		  else
		    {
		      /* An unprintable multibyte character.
			 Replace it entirely with a question
			 mark.  */
		      p += bytes;
		      *q++ = '?';
		    }
		}
	      while (! mbsinit (&mbstate));
	    }
	    break;
	  }

      /* The buffer may have shrunk.  */
      len = q - buf;
      return len;
    }
}