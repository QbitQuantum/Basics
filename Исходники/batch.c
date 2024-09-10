char *readbatchline(int *eflag, char *textline, int size)
{
  /*
   * Read and return the next executable line from the current batch file
   *
   * If no batch file is current or no further executable lines are found
   * return NULL.
   *
   * Here we also look out for FOR bcontext structures which trigger the
   * FOR expansion code.
   *
   * Set eflag to 0 if line is not to be echoed else 1
   */

  char *first;
  char *ip;

  if (bc == 0)               /* No batch */
    return 0;

  dprintf(("readbatchline ()\n"));
  assert(textline);
  assert(size > 1);
  assert(eflag);

  ip = "";                      /* make sure ip != NULL in the first
  									iteration of the loop */
  while (bc)
  {
    first = 0;               /* by default return "no file" */

    if (bc->forvar)             /* If its a FOR context... */
    {
      int forvarlen;
      char
       *fv1,
       *sp,      /* pointer to prototype command */
       *dp,          /* Place to expand protoype */
       *fv;				       /* Next list element */

      if (chkCBreak(BREAK_FORCMD) || bc->shiftlevel > bc->numParams)
        /* End of list or User break so... */
      {
        exit_batch();           /* just exit this context */
        continue;
      }

      fv1 = fv = getArgCur(0);

	if (bc->ffind) {          /* First already done fo do next */
		if(FINDNEXT(bc->ffind) != 0) {		/* no next file */
          free(bc->ffind);      /* free the buffer */
          bc->ffind = 0;
          bc->shiftlevel++;     /* On to next list element */
          continue;
        }
	  fv = bc->ffind->ff_name;
	} else
	{
      if (strpbrk(fv, "?*") == 0) {      /* element is not wild file */
        bc->shiftlevel++;       /* No -> use it and shift list */
        fv1 = "";				/* No additional info */
      } else
        /* Wild file spec, find first (or next) file name */
      {

	  /*  For first find, allocate a find first block */
          if ((bc->ffind = (struct ffblk *)malloc(sizeof(struct ffblk)))
           == 0)
          {
            error_out_of_memory();
            exit_batch();		/* kill this FOR context */
            break;
          }

         if(FINDFIRST(fv, bc->ffind, FA_NORMAL) == 0) {
         	/* found a file */
         	*dfnfilename(fv) = '\0';	/* extract path */
        	fv = bc->ffind->ff_name;
         } else {			/* if not found use the string itself */
#if 0
			/* To use the pattern is not compatible with MS COMMAND */
			++bc->shiftlevel;
			fv1 = "";				/* No additional info */
#else
          free(bc->ffind);      /* free the buffer */
          bc->ffind = 0;
          bc->shiftlevel++;     /* On to next list element */
          continue;
#endif
        }

      }
      }

      /* At this point, fv points to parameter string */
      /* fv1 is the string usually set to the path to the
      	found file, otherwise it points to "" */

       sp = bc->forproto;      /* pointer to prototype command */
       dp = textline;          /* Place to expand protoype */

       assert(sp);
       assert(bc->forvar);

      forvarlen = strlen(bc->forvar);
      while (*sp)
      {
        if (memcmp(sp, bc->forvar, forvarlen) == 0)
          dp = stpcpy(stpcpy(dp, fv1), fv), sp += forvarlen;
        else
          *dp++ = *sp++;        /* Else just copy */
      }

      *dp = '\0';

      assert(dp - textline <= size);

      *eflag = echo;

      first = textline;
      break;
    }

    if (!bc->bfile)
    {                           /* modifyable batchfiles */
      if ((bc->bfile = fopen(bc->bfnam, "rt")) == 0)
      {
        error_bfile_vanished(bc->bfnam);
        exit_batch();
        continue;
      }
      bc->bclose = 1;
      if (bc->brewind)
      {
        bc->brewind = 0;        /* fopen() position at start of file */
        bc->blinecnt = 0;
      }
      else if (fsetpos(bc->bfile, &bc->bpos))
      {                         /* end of file reached */
        /* so says MS COMMAND */
        exit_batch();
        continue;
      }
    }
    else if(bc->brewind) {
    	rewind(bc->bfile);
    	bc->brewind = 0;
    	bc->blinecnt = 0;
    }

    assert(ip != 0);
    ++bc->blinecnt;
    if (chkCBreak(BREAK_BATCHFILE)      /* User break */
        || fgets(textline, size, bc->bfile) == 0     /* End of file.... */
        || (ip = textlineEnd(textline, size)) == 0)  /* line too long */
    {
      if (!ip)
        error_long_batchline(bc->bfnam, bc->blinecnt);

      exit_batch();

      continue;
    }

    /* Strip leading spaces and trailing space/control chars */
    rtrimsp(textline);
    first = ltrimcl(textline);

    assert(first);

    /* ignore empty lines */
    if (!*first)
      continue;

    if (*first == ':')
    {
      /* if a label is searched for test if we reached it */
      if(bc->blabel) {
        /* label: the 1st word immediately following the colon ':' */
		for(ip = ++first; isgraph(*ip); ++ip)
			;
        *ip = '\0';
        if (stricmp(first, bc->blabel) == 0)
        {                       /* OK found */
          free(bc->blabel);
          bc->blabel = 0;
        }
      }
      continue;                 /* ignore label */
    }

    if (bc->blabel)
      continue;                 /* we search for a label! */

    if (*first == '@')          /* don't echo this line */
    {
    	first = ltrimcl(first + 1);
      *eflag = 0;
    }
    else
      *eflag = echo;

    break;
  }

  if (bc && bc->bclose)
  {                             /* modifyable batchfiles - ska */
    fgetpos(bc->bfile, &bc->bpos);
    fclose(bc->bfile);
    bc->bfile = 0;
    bc->bclose = 0;
  }

  return first;
}