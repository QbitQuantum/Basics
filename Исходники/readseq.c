int readSequence (FILE *fil, int *conv, 
                  char **seq, char **id, char **desc, int *length)
{
  char c ;
  int n ;
  static FILE *oldFil = 0 ;
  static int line ;
  int buflen ;

  if (fil != oldFil)
    { line = 1 ;
      oldFil = fil ;
    }
  
/* get id, descriptor */
  c = getc (fil) ;
  if (c == '>')			/* header line */
    { c = getc(fil) ;

      n = 0 ;			/* id */
      buflen = -32;
      while (!feof (fil) && c != ' ' && c != '\n' && c != '\t')
	{ if (id) add (c, id, &buflen, n++) ;
	  c = getc (fil) ;
	}
      if (id) add (0, id, &buflen, n) ;

				/* white space */
      while (!feof (fil) && (c == ' ' || c == '\t'))
	c = getc (fil) ;

      n = 0 ;			/* desc */
      buflen = -32 ;
      while (!feof (fil) && c != '\n')
	{ if (desc) add (c, desc, &buflen, n++) ;
	  c = getc (fil) ;
	}
      if (desc) add (0, desc, &buflen, n) ;

      ++line ;
    }
  else
    { ungetc (c, fil) ;		/* no header line */
      if (id) 
	*id = "" ;
      if (desc)
	*desc = "" ;
    }

  /* ensure whitespace ignored */

  conv[' '] = conv['\t'] = -1 ;
  conv['\n'] = -3 ;

  n = 0 ;			/* sequence */
  buflen = -1024 ;

  while (!feof (fil))
    { 
      c = getc (fil) ;
      if (c == '>')
	{ ungetc (c, fil) ;
	  break ;
	}

      if (c == EOF || c == EOF + 256) /* satisfies all compilers */
	break ;

    
      switch (conv[c]) {
        case -2:
          { if (id) 
              fprintf (stderr, "Bad char 0x%x = '%c' at line %d, base %d, sequence %s\n",
          	     c, c, line, n, *id) ;
            else
              fprintf (stderr, "Bad char 0x%x = '%c' at line %d, base %d\n",
          	     c, c, line, n) ;
            return 0 ;
          }
          break;
        case -3:
          ++line;
        case -1:
          break;
        default:
	  if (seq) add (conv[c], seq, &buflen, n++) ;
	  else ++n ;
      }
    }
  if (seq) add (0, seq, &buflen, n) ;

  if (length)
    *length = n ;

  return n ;
}