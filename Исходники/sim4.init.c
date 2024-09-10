static int
get_next_seq(seq_p_t sp, unsigned int offset, int warnMultiSeq)
{
  const int lenStr = 24;
  unsigned int headerLen;
  char *buf = sp->rb.line;
  int res;
  while (sp->rb.lc > 0 && buf[0] != '>')
    buf = read_line_buf(&sp->rb, sp->fd);
  if (sp->rb.lc == 0)
    return -1;
  /* We have the FASTA header.  */
  if (sp->rb.lc + lenStr + 1 > sp->maxHead) {
    sp->maxHead = sp->rb.lc + lenStr + 1;
    sp->header = (char *) xrealloc(sp->header, sp->maxHead * sizeof(char));
  }
  headerLen = sp->rb.lc;
  memcpy(sp->header, buf, (sp->rb.lc + 1) * sizeof(char));
  sp->len = 0;
  buf = read_line_buf(&sp->rb, sp->fd);
  while (sp->rb.lc > 0 && buf[0] != '>') {
    unsigned char c;
    /* Make sure we have enough room for this additional line.  */
    if (sp->len + sp->rb.lc + 1 > sp->max) {
      sp->max = max(sp->len + sp->rb.lc + 1,
		    sp->max + 0x40000);
      sp->seq = (unsigned char *)
	xrealloc(sp->seq, sp->max * sizeof(unsigned char));
    }
    while ((c = *buf++) != 0) {
      if (isupper(c)) {
	sp->seq[sp->len++] = c;
      } else if (islower(c)) {
	sp->seq[sp->len++] = toupper(c);
      }
    }
    buf = read_line_buf(&sp->rb, sp->fd);
  }
  if (warnMultiSeq && sp->rb.lc > 0)
    fprintf(stderr, "\n"
	    "***  WARNING                                           ***\n"
	    "***  there appears to be several sequences in the DNA  ***\n"
	    "***  sequence file.  Only the first one will be used,  ***\n"
	    "***  which might not be what was intended.             ***\n"
	    "\n");
  sp->seq[sp->len] = 0;
  buf = strstr(sp->header, "; LEN=");
  if (buf) {
    char *s = buf + 6;
    headerLen -= 6;
    while (isdigit(*s)) {
      s += 1;
      headerLen -= 1;
    }
    while (*s)
      *buf++ = *s++;
  }
  buf = sp->header + headerLen - 1;
  while (iscntrl(*buf) || isspace(*buf))
    buf -= 1;
  res = snprintf(buf + 1, lenStr, "; LEN=%u\n", sp->len + offset);
  if (res < 0 || res >= lenStr)
    fatal("Sequence too long: %u\n", sp->len);
  return 0;
}