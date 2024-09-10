void
do_ranlib (const char *archive)
{
  FILE *infp;

  if (NULL == (infp = fopen (archive, "rb")))
    {
      fprintf (stderr, "asranlib: %s: ", archive);
      perror (NULL);
      exit (1);
    }

  if (!get_symbols (infp, archive))
    {
      fprintf (stderr, "asranlib: %s: Malformed archive\n", archive);
      fclose (infp);
      exit (1);
    }
  else if (!list && !print_index)
    {
      FILE *outfp;
      struct symbol_s *symp;
      char buf[4];
      int str_length;
      int pad;
      int nsym;
      int symtab_size;
      char tmpfile[] = "arXXXXXX";
      struct stat stat_buf;
      int can_stat;

#ifdef _WIN32
      if (NULL == _mktemp (tmpfile) || NULL == (outfp = fopen (tmpfile, "wb")))
        {
          fclose (infp);
          fprintf (stderr, "asranlib: %s: ", tmpfile);
          perror (NULL);
          exit (1);
        }
#else
      if ((pad = mkstemp (tmpfile)) < 0)
        {
          fclose (infp);
          fprintf (stderr, "asranlib: %s: ", tmpfile);
          perror (NULL);
          exit (1);
        }

      if (NULL == (outfp = fdopen (pad, "wb")))
        {
          close (pad);
          fclose (infp);
          perror ("asranlib");
          exit (1);
        }
#endif

      /* calculate the size of symbol table */
      for (str_length = 0, nsym = 0, symp = symlist; symp; ++nsym, symp = symp->next)
        {
          str_length += strlen (symp->name) + 1;
        }

      symtab_size = 4 + 4 * nsym + str_length;

      fprintf (outfp, ARMAG AR_SYMBOL_TABLE_NAME "%-12d%-6d%-6d%-8d%-10d" ARFMAG, (int) time (NULL), 0, 0, 0, symtab_size);

      if (symtab_size & 1)
        {
          pad = 1;
          ++symtab_size;
        }
      else
        pad = 0;

      symtab_size += SARMAG + ARHDR_LEN;

      sputl (nsym, buf);
      fwrite (buf, 1, sizeof (buf), outfp);

      for (symp = symlist; symp; symp = symp->next)
        {
          sputl (symp->offset + symtab_size, buf);
          fwrite (buf, 1, sizeof (buf), outfp);
        }

      for (symp = symlist; symp; symp = symp->next)
        {
          fputs (symp->name, outfp);
          putc ('\0', outfp);
        }

      if (pad)
        putc ('\n', outfp);

      fseek (infp, first_member_offset, SEEK_SET);

      while (EOF != (pad = getc (infp)))
        putc (pad, outfp);

      fclose (outfp);

      if (0 != fstat(fileno(infp), &stat_buf))
        {
          fprintf (stderr, "asranlib: can't stat %s: ", archive);
          perror (NULL);
          can_stat = 0;
        }
      else
        can_stat = 1;

      fclose (infp);

      if (0 != remove (archive))
        {
          fprintf (stderr, "asranlib: can't remove %s: ", archive);
          perror (NULL);
        }
      else if (0 != rename (tmpfile, archive))
        {
          fprintf (stderr, "asranlib: can't rename %s to %s: ", tmpfile, archive);
          perror (NULL);
        }
      else if (!can_stat || 0 != chmod (archive, stat_buf.st_mode))
        {
          fprintf (stderr, "asranlib: can't chmod %s: ", archive);
          perror (NULL);
        }
    }
  else
    fclose (infp);
}