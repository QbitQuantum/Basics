void
input_file_open (char *filename, /* "" means use stdin. Must not be 0.  */
		 int pre)
{
  int c;
  char buf[80];

  preprocess = pre;

  assert (filename != 0);	/* Filename may not be NULL.  */
  if (filename[0])
    {
      f_in = fopen (filename, FOPEN_RT);
      file_name = filename;
    }
  else
    {
      /* Use stdin for the input file.  */
      f_in = stdin;
      /* For error messages.  */
      file_name = _("{standard input}");
    }

  if (f_in)
    c = getc (f_in);

  if (f_in == NULL || ferror (f_in))
    {
#ifdef BFD_ASSEMBLER
      bfd_set_error (bfd_error_system_call);
#endif
      as_perror (_("Can't open %s for reading"), file_name);

      if (f_in)
	{
	  fclose (f_in);
	  f_in = NULL;
	}
      return;
    }

  if (c == '#')
    {
      /* Begins with comment, may not want to preprocess.  */
      c = getc (f_in);
      if (c == 'N')
	{
	  fgets (buf, 80, f_in);
	  if (!strncmp (buf, "O_APP", 5) && ISSPACE (buf[5]))
	    preprocess = 0;
	  if (!strchr (buf, '\n'))
	    ungetc ('#', f_in);	/* It was longer.  */
	  else
	    ungetc ('\n', f_in);
	}
      else if (c == 'A')
	{
	  fgets (buf, 80, f_in);
	  if (!strncmp (buf, "PP", 2) && ISSPACE (buf[2]))
	    preprocess = 1;
	  if (!strchr (buf, '\n'))
	    ungetc ('#', f_in);
	  else
	    ungetc ('\n', f_in);
	}
      else if (c == '\n')
	ungetc ('\n', f_in);
      else
	ungetc ('#', f_in);
    }
  else
    ungetc (c, f_in);
}