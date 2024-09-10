/* Fast boyer-moore search. */
static size_t
bmexec (kwset_t kws, char const *text, size_t size)
{
  struct kwset const *kwset;
  register unsigned char const *d1;
  register char const *ep, *sp, *tp;
  register int d, gc, i, len, md2;

  kwset = (struct kwset const *) kws;
  len = kwset->mind;

  if (len == 0)
    return 0;
  if (len > size)
    return -1;
  if (len == 1)
    {
      tp = memchr (text, kwset->target[0], size);
      return tp ? tp - text : -1;
    }

  d1 = kwset->delta;
  sp = kwset->target + len;
  gc = U(sp[-2]);
  md2 = kwset->mind2;
  tp = text + len;

  /* Significance of 12: 1 (initial offset) + 10 (skip loop) + 1 (md2). */
  if (size > 12 * len)
    /* 11 is not a bug, the initial offset happens only once. */
    for (ep = text + size - 11 * len;;)
      {
	while (tp <= ep)
	  {
	    d = d1[U(tp[-1])], tp += d;
	    d = d1[U(tp[-1])], tp += d;
	    if (d == 0)
	      goto found;
	    d = d1[U(tp[-1])], tp += d;
	    d = d1[U(tp[-1])], tp += d;
	    d = d1[U(tp[-1])], tp += d;
	    if (d == 0)
	      goto found;
	    d = d1[U(tp[-1])], tp += d;
	    d = d1[U(tp[-1])], tp += d;
	    d = d1[U(tp[-1])], tp += d;
	    if (d == 0)
	      goto found;
	    d = d1[U(tp[-1])], tp += d;
	    d = d1[U(tp[-1])], tp += d;
	  }
	break;
      found:
	if (U(tp[-2]) == gc)
	  {
	    for (i = 3; i <= len && U(tp[-i]) == U(sp[-i]); ++i)
	      ;
	    if (i > len)
	      return tp - len - text;
	  }
	tp += md2;
      }

  /* Now we have only a few characters left to search.  We
     carefully avoid ever producing an out-of-bounds pointer. */
  ep = text + size;
  d = d1[U(tp[-1])];
  while (d <= ep - tp)
    {
      d = d1[U((tp += d)[-1])];
      if (d != 0)
	continue;
      if (U(tp[-2]) == gc)
	{
	  for (i = 3; i <= len && U(tp[-i]) == U(sp[-i]); ++i)
	    ;
	  if (i > len)
	    return tp - len - text;
	}
      d = md2;
    }

  return -1;
}