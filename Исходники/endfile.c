t_runc(alist *a)
#endif
{
  OFF_T loc, len;
  unit *b;
  int rc;
  FILE *bf;
#ifdef NO_TRUNCATE
  FILE *tf;
#endif

  b = &f__units[a->aunit];
  if(b->url)
         return(0);       /*don't truncate direct files*/
  loc=FTELL(bf = b->ufd);
  FSEEK(bf,(OFF_T)0,SEEK_END);
  len=FTELL(bf);
  if (loc >= len || b->useek == 0)
         return(0);
#ifdef NO_TRUNCATE
  if (b->ufnm == NULL)
         return 0;
  rc = 0;
  fclose(b->ufd);
  if (!loc) {
         if (!(bf = FOPEN(b->ufnm, f__w_mode[b->ufmt])))
                rc = 1;
         if (b->uwrt)
                b->uwrt = 1;
         goto done;
         }
  if (!(bf = FOPEN(b->ufnm, f__r_mode[0]))
   || !(tf = tmpfile())) {
#ifdef NON_UNIX_STDIO
 bad:
#endif
         rc = 1;
         goto done;
         }
  if (copy(bf, (long)loc, tf)) {
 bad1:
         rc = 1;
         goto done1;
         }
  if (!(bf = FREOPEN(b->ufnm, f__w_mode[0], bf)))
         goto bad1;
  rewind(tf);
  if (copy(tf, (long)loc, bf))
         goto bad1;
  b->uwrt = 1;
  b->urw = 2;
#ifdef NON_UNIX_STDIO
  if (b->ufmt) {
         fclose(bf);
         if (!(bf = FOPEN(b->ufnm, f__w_mode[3])))
                goto bad;
         FSEEK(bf,(OFF_T)0,SEEK_END);
         b->urw = 3;
         }
#endif
done1:
  fclose(tf);
done:
  f__cf = b->ufd = bf;
#else /* NO_TRUNCATE */
  if (b->urw & 2)
         fflush(b->ufd); /* necessary on some Linux systems */
#ifndef FTRUNCATE
#define FTRUNCATE ftruncate
#endif
  rc = FTRUNCATE(fileno(b->ufd), loc);
  /* The following FSEEK is unnecessary on some systems, */
  /* but should be harmless. */
  FSEEK(b->ufd, (OFF_T)0, SEEK_END);
#endif /* NO_TRUNCATE */
  if (rc)
         err(a->aerr,111,"endfile");
  return 0;
  }