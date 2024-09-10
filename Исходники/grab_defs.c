int
read_some(char *buf, int n, int start_ch, int copy)
     /* if copy is not 0 then copy characters to stdout while scanning
	to find start_ch.   When you find it, read n characters into buf,
	return the number of characters read into buf, but these characters
	MUST be free of start_ch.
	*/
               
                         
{ int ch;
  int prev = 0;
  while (1)
    { ch =GETC(stdin);
      if (ch == EOF) return -1;
      if (copy) {putc(ch,stdout);
		 if (prev == '\n' && ch == '{')
		   { fprintf(stderr,"Error(at char %d):found \\n{ inside section to copy\n",pos) ;
		     exit(1);}
		 prev = ch;
	       }
    AGAIN:
      if (ch == start_ch)
	{ int i = 0;
	  while (i < n)
	    { ch = GETC(stdin);
	      if (ch == EOF) return i;
	      if (copy) {putc(ch,stdout);
			 if (prev == '\n' && ch == '{')
			   { fprintf(stderr,"Error(at char %d):found \\n{ inside section to copy",pos) ;
			     exit(1);}
			 prev = ch;
		       }

	      if (ch == start_ch) goto AGAIN;
	      buf[i++] = ch;
	    }
	  return i;
	}}}