/* difference of two utc times in seconds */
double
cmml_utc_diff (CMML_UTC *t2, CMML_UTC *t1)
{
  double diffsec;

  diffsec = (t2->tm_hsec - t1->tm_hsec)/100;
  diffsec += (t2->tm_sec - t1->tm_sec);
  diffsec += 60.0*(t2->tm_min - t1->tm_min);
  diffsec += 3600.0*(t2->tm_hour - t1->tm_hour);
  diffsec += 24.0*3600*(t2->tm_mday - t1->tm_mday);
  /* presuming there are 30.4375 days in each month (=365.25/12)*/
  diffsec += 30.4375*24*3600*(t2->tm_mon - t1->tm_mon);
  diffsec += 12.0*30*24*3600*(t2->tm_year - t1->tm_year);

#ifdef DEBUG
  fprintf(stderr, "t1: Year=%d\tMonth=%d\tDay=%d\n", 
	  t1->tm_year, t1->tm_mon, t1->tm_mday);
  fprintf(stderr, "Hour=%d\tMinutes=%d\tSec=%d\tHSec=%d\n",
	  t1->tm_hour, t1->tm_min, t1->tm_sec, t1->tm_hsec);
  fprintf(stderr, "t2: Year=%d\tMonth=%d\tDay=%d\n", 
	  t2->tm_year, t2->tm_mon, t2->tm_mday);
  fprintf(stderr, "Hour=%d\tMinutes=%d\tSec=%d\tHSec=%d\n",
	  t2->tm_hour, t2->tm_min, t2->tm_sec, t2->tm_hsec);
  fprintf(stderr, "diffsec = %f\n", diffsec);
#endif

  return diffsec;

  /* seems like the system time functions don't work */
#if 0
  time_t time1, time2;
  struct tm tmptm1;
  struct tm tmptm2;
  double diffreturn;

  if (t1 == NULL || t2 == NULL) {
    return -1;
  }

  /* transform t1 to struct tm and seconds from EPOCH */
  tmptm1.tm_sec  = t1->tm_sec;
  tmptm1.tm_min  = t1->tm_min;
  tmptm1.tm_hour = t1->tm_hour;
  tmptm1.tm_mday = t1->tm_mday;
  tmptm1.tm_mon  = t1->tm_mon-1;
  tmptm1.tm_year = t1->tm_year-1900;
  time1 = mktime(&tmptm1);
#ifdef DEBUG
  fprintf(stderr,"time1 %ld\n", time1);
  fprintf(stderr, "Year=%d(%d)\tMonth=%d(%d)\tDay=%d(%d)\n", 
	  tmptm1.tm_year, t1->tm_year, tmptm1.tm_mon, t1->tm_mon, tmptm1.tm_mday, t1->tm_mday);
  fprintf(stderr, "Hour=%d(%d)\tMinutes=%d(%d)\tSec=%d(%d)\tHSec=0(%d)\n",
	  tmptm1.tm_hour, t1->tm_hour, tmptm1.tm_min, t1->tm_min, tmptm1.tm_sec, t1->tm_sec, 
	  t1->tm_hsec);
#endif

  /* convert t2 to struct tm and seconds from EPOCH */
  tmptm2.tm_sec  = t2->tm_sec;
  tmptm2.tm_min  = t2->tm_min;
  tmptm2.tm_hour = t2->tm_hour;
  tmptm2.tm_mday = t2->tm_mday;
  tmptm2.tm_mon  = t2->tm_mon-1;
  tmptm2.tm_year = t2->tm_year-1900;
  time2 = mktime(&tmptm2);
#ifdef DEBUG
  fprintf(stderr,"time2 %ld\n", time2);
  fprintf(stderr, "Year=%d(%d)\tMonth=%d(%d)\tDay=%d(%d)\n", 
	  tmptm2.tm_year, t2->tm_year, tmptm2.tm_mon, t2->tm_mon, tmptm2.tm_mday, t2->tm_mday);
  fprintf(stderr, "Hour=%d(%d)\tMinutes=%d(%d)\tSec=%d(%d)\tHSec=0(%d)\n",
	  tmptm2.tm_hour, t2->tm_hour, tmptm2.tm_min, t2->tm_min, tmptm2.tm_sec, t2->tm_sec, 
	  t2->tm_hsec);
#endif

  /* use system's time difference functions for calculation */
  diffreturn = (double) difftime (time2, time1);
  fprintf(stderr, "diffreturn=%f\n", diffreturn);
  diffreturn += (t2->tm_hsec - t1->tm_hsec)/100;

  return diffreturn;
#endif

}