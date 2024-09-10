/* Process FS's buffer so that line wrapping is done from POINT_OFFS to the
   end of its buffer.  This code is mostly from glibc stdio/linewrap.c.  */
void
__argp_fmtstream_update (argp_fmtstream_t fs)
{
  char *buf, *nl;
  size_t len;

  /* Scan the buffer for newlines.  */
  buf = fs->buf + fs->point_offs;
  while (buf < fs->p)
    {
      size_t r;

      if (fs->point_col == 0 && fs->lmargin != 0)
	{
	  /* We are starting a new line.  Print spaces to the left margin.  */
	  const size_t pad = fs->lmargin;
	  if (fs->p + pad < fs->end)
	    {
	      /* We can fit in them in the buffer by moving the
		 buffer text up and filling in the beginning.  */
	      memmove (buf + pad, buf, fs->p - buf);
	      fs->p += pad; /* Compensate for bigger buffer. */
	      memset (buf, ' ', pad); /* Fill in the spaces.  */
	      buf += pad; /* Don't bother searching them.  */
	    }
	  else
	    {
	      /* No buffer space for spaces.  Must flush.  */
	      size_t i;
	      for (i = 0; i < pad; i++)
		{
		  if (_IO_fwide (fs->stream, 0) > 0)
		    putwc_unlocked (L' ', fs->stream);
		  else
		    putc_unlocked (' ', fs->stream);
		}
	    }
	  fs->point_col = pad;
	}

      len = fs->p - buf;
      nl = memchr (buf, '\n', len);

      if (fs->point_col < 0)
	fs->point_col = 0;

      if (!nl)
	{
	  /* The buffer ends in a partial line.  */

	  if (fs->point_col + len < fs->rmargin)
	    {
	      /* The remaining buffer text is a partial line and fits
		 within the maximum line width.  Advance point for the
		 characters to be written and stop scanning.  */
	      fs->point_col += len;
	      break;
	    }
	  else
	    /* Set the end-of-line pointer for the code below to
	       the end of the buffer.  */
	    nl = fs->p;
	}
      else if (fs->point_col + (nl - buf) < (ssize_t) fs->rmargin)
	{
	  /* The buffer contains a full line that fits within the maximum
	     line width.  Reset point and scan the next line.  */
	  fs->point_col = 0;
	  buf = nl + 1;
	  continue;
	}

      /* This line is too long.  */
      r = fs->rmargin - 1;

      if (fs->wmargin < 0)
	{
	  /* Truncate the line by overwriting the excess with the
	     newline and anything after it in the buffer.  */
	  if (nl < fs->p)
	    {
	      memmove (buf + (r - fs->point_col), nl, fs->p - nl);
	      fs->p -= buf + (r - fs->point_col) - nl;
	      /* Reset point for the next line and start scanning it.  */
	      fs->point_col = 0;
	      buf += r + 1; /* Skip full line plus \n. */
	    }
	  else
	    {
	      /* The buffer ends with a partial line that is beyond the
		 maximum line width.  Advance point for the characters
		 written, and discard those past the max from the buffer.  */
	      fs->point_col += len;
	      fs->p -= fs->point_col - r;
	      break;
	    }
	}
      else
	{
	  /* Do word wrap.  Go to the column just past the maximum line
	     width and scan back for the beginning of the word there.
	     Then insert a line break.  */

	  char *p, *nextline;
	  int i;

	  p = buf + (r + 1 - fs->point_col);
	  while (p >= buf && !isblank (*p))
	    --p;
	  nextline = p + 1;	/* This will begin the next line.  */

	  if (nextline > buf)
	    {
	      /* Swallow separating blanks.  */
	      if (p >= buf)
		do
		  --p;
		while (p >= buf && isblank (*p));
	      nl = p + 1;	/* The newline will replace the first blank. */
	    }
	  else
	    {
	      /* A single word that is greater than the maximum line width.
		 Oh well.  Put it on an overlong line by itself.  */
	      p = buf + (r + 1 - fs->point_col);
	      /* Find the end of the long word.  */
	      do
		++p;
	      while (p < nl && !isblank (*p));
	      if (p == nl)
		{
		  /* It already ends a line.  No fussing required.  */
		  fs->point_col = 0;
		  buf = nl + 1;
		  continue;
		}
	      /* We will move the newline to replace the first blank.  */
	      nl = p;
	      /* Swallow separating blanks.  */
	      do
		++p;
	      while (isblank (*p));
	      /* The next line will start here.  */
	      nextline = p;
	    }

	  /* Note: There are a bunch of tests below for
	     NEXTLINE == BUF + LEN + 1; this case is where NL happens to fall
	     at the end of the buffer, and NEXTLINE is in fact empty (and so
	     we need not be careful to maintain its contents).  */

	  if ((nextline == buf + len + 1
	       ? fs->end - nl < fs->wmargin + 1
	       : nextline - (nl + 1) < fs->wmargin)
	      && fs->p > nextline)
	    {
	      /* The margin needs more blanks than we removed.  */
	      if (fs->end - fs->p > fs->wmargin + 1)
		/* Make some space for them.  */
		{
		  size_t mv = fs->p - nextline;
		  memmove (nl + 1 + fs->wmargin, nextline, mv);
		  nextline = nl + 1 + fs->wmargin;
		  len = nextline + mv - buf;
		  *nl++ = '\n';
		}
	      else
		/* Output the first line so we can use the space.  */
		{
#ifdef _LIBC
		  __fxprintf (fs->stream, "%.*s\n",
			      (int) (nl - fs->buf), fs->buf);
#else
		  if (nl > fs->buf)
		    fwrite_unlocked (fs->buf, 1, nl - fs->buf, fs->stream);
		  putc_unlocked ('\n', fs->stream);
#endif

		  len += buf - fs->buf;
		  nl = buf = fs->buf;
		}
	    }
	  else
	    /* We can fit the newline and blanks in before
	       the next word.  */
	    *nl++ = '\n';

	  if (nextline - nl >= fs->wmargin
	      || (nextline == buf + len + 1 && fs->end - nextline >= fs->wmargin))
	    /* Add blanks up to the wrap margin column.  */
	    for (i = 0; i < fs->wmargin; ++i)
	      *nl++ = ' ';
	  else
	    for (i = 0; i < fs->wmargin; ++i)
	      if (_IO_fwide (fs->stream, 0) > 0)
		putwc_unlocked (L' ', fs->stream);
	      else
		putc_unlocked (' ', fs->stream);

	  /* Copy the tail of the original buffer into the current buffer
	     position.  */
	  if (nl < nextline)
	    memmove (nl, nextline, buf + len - nextline);
	  len -= nextline - buf;

	  /* Continue the scan on the remaining lines in the buffer.  */
	  buf = nl;

	  /* Restore bufp to include all the remaining text.  */
	  fs->p = nl + len;

	  /* Reset the counter of what has been output this line.  If wmargin
	     is 0, we want to avoid the lmargin getting added, so we set
	     point_col to a magic value of -1 in that case.  */
	  fs->point_col = fs->wmargin ? fs->wmargin : -1;
	}
    }

  /* Remember that we've scanned as far as the end of the buffer.  */
  fs->point_offs = fs->p - fs->buf;
}