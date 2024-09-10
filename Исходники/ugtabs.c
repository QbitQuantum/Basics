int tabler_init(CSOUND *csound, TABL *p) {

  int ndx, len;
  int mask;

  if (UNLIKELY((p->ftp = csound->FTnp2Find(csound, p->ftable)) == NULL))
      return csound->InitError(csound,
                               Str("table: could not find ftable %d"),
                               (int) *p->ftable);
  mask = p->ftp->lenmask;
  p->np2 = mask ? 0 : 1;
  len = p->ftp->flen;

  if (*p->mode)
      p->mul = len;
    else
      p->mul = 1;

  ndx = FLOOR((*p->ndx + *p->offset)*p->mul);
  if (*p->wrap) {
    if (p->np2) {
      while(ndx >= len) ndx -= len;
      while(ndx < 0)  ndx += len;
    }
    else ndx &= mask;
  } else {
    if (UNLIKELY(ndx >= len)) ndx = len - 1;
    else if (UNLIKELY(ndx < 0)) ndx = 0;
  }
  *p->sig = p->ftp->ftable[ndx];
  return OK;
}