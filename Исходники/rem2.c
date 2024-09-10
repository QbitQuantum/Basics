static int isnewid(BUFFER *id, char rsa1234, long timestamp)
/* return values:
 *   0: ignore message, no error
 *   1: ok, process message
 *  -1: bad message, send reply
 */
{
  FILE *f=NULL, *rf=NULL, *tf;
  int ret = 1;
  long now, old = 0;
  int old_day, now_day, ri, rj, flag;
  char queue[30][LINELEN];
  struct tm *gt;
  time_t od;
  LOCK *i = NULL;
  LOCK *j = NULL;
  idlog_t idbuf;
  struct {
    long time;
    int r[5];
  } rs;

  if (REMAIL == 0)
    return (1); /* don't keep statistics for the client */

  now = time(NULL);

  if ((f = mix_openfile(IDLOG, "rb+")) != NULL) {
    fread(&idbuf,1,sizeof(idlog_t),f);
    old = idbuf.time;
  } else {
    if (IDEXP == 0) {
      if (timestamp > 0 && timestamp <= now - 7 * SECONDSPERDAY) {
	errlog(LOG, "Ignoring old message.\n");
	return (0);
      }
    } else {
      if ((f = mix_openfile(IDLOG, "wb")) != NULL) {
	memset(idbuf.id,0,sizeof(idbuf.id));
	idbuf.time = now;
	fwrite(&idbuf,1,sizeof(idlog_t),f);
	memcpy(idbuf.id,id->data,sizeof(idbuf.id));
	idbuf.time = now;
	fwrite(&idbuf,1,sizeof(idlog_t),f);
	fclose(f);
        f=NULL;
	errlog(NOTICE, "Creating %s\n", IDLOG);
      } else {
	errlog(ERRORMSG, "Can't create %s\n", IDLOG);
      }
      return (1);
    }
  }

  if (now - old < 5 * SECONDSPERDAY)	/* never reject messages less than */
    old = now - 5 * SECONDSPERDAY;	/* 5 days old (== minimum IDEXP) */

  if (timestamp > 0 && timestamp <= old) {
    errlog(LOG, "Ignoring old message.\n");
    ret = 0;
    goto end;
  }
  i = lockfile(IDLOG);
  while (fread(&idbuf, 1, sizeof(idlog_t), f) == sizeof(idlog_t)) {
    if (!memcmp(idbuf.id, id->data, sizeof(idbuf.id))) {
      char idstr[33];
      id_encode(id->data, idstr);
      errlog(LOG, "Ignoring redundant message: %s.\n", idstr);
      ret = 0;
      goto end;
    }
  }
  if (timestamp > now) {
    errlog(LOG, "Ignoring message with future timestamp.\n");
    ret = -1;
    goto end;
  }
  if (ftell(f)%sizeof(idlog_t)) fseek(f,0-(ftell(f)%sizeof(idlog_t)),SEEK_CUR); /* make sure that we're on sizeof(idlog_t) byte boundary */
  memcpy(idbuf.id,id->data,sizeof(idbuf.id));
  idbuf.time = now;
  fwrite(&idbuf,1,sizeof(idlog_t),f);

  /* What key lengths are being used? */
  /* XXXXX TODO: The rest of this function is new code
   * that uses line endings and has not been tested on Windows.
   */
  if ((rf = mix_openfile(RSASTATSFILE, "rb+")) == NULL) {
    /* create it */
    if ((rf = mix_openfile(RSASTATSFILE, "wb+")) == NULL) {
        ret=-1;
        goto end;
    }
    memset(&rs, 0, sizeof(rs));
    fwrite(&rs,1,sizeof(rs),rf);
  } else {
    j = lockfile(RSASTATSFILE);
    fread(&rs,1,sizeof(rs),rf);
    fseek(rf,0,0);
    old = rs.time;
    old_day = old/SECONDSPERDAY;
    if (old_day<15706) old_day=15706;
    now_day = now/SECONDSPERDAY;
    if (old_day == now_day) {
        /* add current item to stats  */
        rs.r[rsa1234]++;
        fwrite(&rs,1,sizeof(rs),rf);
    } else {
        /* write text and restart the daily file */
        if ((tf = mix_openfile(RSATEXTFILE, "a")) != NULL) {
            od=old_day * (SECONDSPERDAY);
            gt = gmtime(&od);
            fprintf(tf, "%04d-%02d-%02d %6d %6d %6d %6d\n",
                 1900+gt->tm_year, 1+gt->tm_mon, gt->tm_mday,
                 rs.r[1], rs.r[2], rs.r[3], rs.r[4]);
            fclose(tf);
            ri=0,rj=0,flag=0;
            if ((tf = mix_openfile(RSATEXTFILE, "r")) != NULL) {
                while ( fgets (queue[ri], LINELEN, tf) ) {
                    queue[ri][LINELEN-1]='\0';
                    ri++; ri %= 30;
                    if (!ri) flag=1;
                }
                fclose(tf);
            }
            rj=ri;
            if (flag) {
                errlog(NOTICE, "rotating file %s from line %d\n", RSATEXTFILE, ri);
                if ((tf = mix_openfile(RSATEXTFILE, "w")) != NULL) {
                    do  {
                        fprintf(tf, "%s", queue[ri]);
                        ri++; ri %= 30;
                    } while (ri != rj);
                    fclose(tf);
                }
            }
        }
        memset(&rs, 0, sizeof(rs));
        rs.time = now_day * SECONDSPERDAY;
        rs.r[rsa1234]++;
        fwrite(&rs,1,sizeof(rs),rf);
    }
  }

end:
  if (i) unlockfile(i);
  if (j) unlockfile(j);
  if (f) fclose(f);
  if (rf) fclose(rf);
  return (ret);
}