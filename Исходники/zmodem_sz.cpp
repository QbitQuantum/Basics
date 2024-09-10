/*
 * generate and transmit pathname block consisting of
 *  pathname (null terminated),
 *  file length, mode time and file mode in octal
 *  as provided by the Unix fstat call.
 *  N.B.: modifies the passed name, may extend it!
 */
int wctxpn(const char *name)
{

  char *p, *q;

//DSERIAL.println("\nwctxpn");

  strcpy(txbuf,name);
  p = q = txbuf + strlen(txbuf)+1;
  //Pete (El Supremo) fix bug - was 1024, should be TXBSIZE??
  while (q < (txbuf + TXBSIZE))
    *q++ = 0;
//  if (!Ascii && (in!=stdin) && *name && fstat(fileno(in), &f)!= -1)
  if (!Ascii)
    // I will have to figure out how to convert the uSD date/time format to a UNIX epoch
//    sprintf(p, "%lu %lo %o 0 %d %ld", fout.fileSize(), 0L,0600, Filesleft, Totalleft);
// Avoid sprintf to save memory for small boards.  This sketch doesn't know what time it is anyway
    ultoa(fout.fileSize(), p, 10);
    strcat_P(p, PSTR(" 0 0 0 "));
    q = p + strlen(p);
    ultoa(Filesleft, q, 10);
    strcat_P(q, PSTR(" "));
    q = q + strlen(q);
    ultoa(Totalleft, q, 10);

  Totalleft -= fout.fileSize();
//DSERIAL.print(F("wctxpn sf = "));
//DSERIAL.print(sf);
//DSERIAL.print(F("  length = "));
//DSERIAL.println(Totalleft);
  if (--Filesleft <= 0)
    Totalleft = 0;
  if (Totalleft < 0)
    Totalleft = 0;

  /* force 1k blocks if name won't fit in 128 byte block */
  //Pete (El Supremo) This can't be right??!
  if (txbuf[125])
//    blklen=1024;
    blklen = TXBSIZE;
  else {          /* A little goodie for IMP/KMD */
    blklen = 128;
    txbuf[127] = (fout.fileSize() + 127) >>7;
    txbuf[126] = (fout.fileSize() + 127) >>15;
  }
  return zsendfile(txbuf, 1+strlen(p)+(p-txbuf));
}