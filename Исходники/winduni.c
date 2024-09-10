void
ascii_print (FILE *e, const char *s, rc_uint_type length)
{
  while (1)
    {
      char ch;

      if (length == 0)
	return;
      if ((bfd_signed_vma) length > 0)
	--length;

      ch = *s;

      if (ch == 0 && (bfd_signed_vma) length < 0)
	return;

      ++s;

      if ((ch & 0x7f) == ch)
	{
	  if (ch == '\\')
	    fputs ("\\\\", e);
	  else if (ch == '"')
	    fputs ("\"\"", e);
	  else if (ISPRINT (ch))
	    putc (ch, e);
	  else
	    {
	      switch (ch)
		{
		case ESCAPE_A:
		  fputs ("\\a", e);
		  break;

		case ESCAPE_B:
		  fputs ("\\b", e);
		  break;

		case ESCAPE_F:
		  fputs ("\\f", e);
		  break;

		case ESCAPE_N:
		  fputs ("\\n", e);
		  break;

		case ESCAPE_R:
		  fputs ("\\r", e);
		  break;

		case ESCAPE_T:
		  fputs ("\\t", e);
		  break;

		case ESCAPE_V:
		  fputs ("\\v", e);
		  break;

		default:
		  fprintf (e, "\\%03o", (unsigned int) ch);
		  break;
		}
	    }
	}
      else
	fprintf (e, "\\%03o", (unsigned int) ch & 0xff);
    }
}