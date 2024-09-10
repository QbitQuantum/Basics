static void setdate(cell year,cell month,cell day)
{
  int maxday;

  #if defined __WIN32__ || defined _WIN32 || defined WIN32
    SYSTEMTIME systim;

    GetLocalTime(&systim);
    if (year!=CELLMIN)
      systim.wYear=(WORD)wrap((int)year,1970,2099);
    if (month!=CELLMIN)
      systim.wMonth=(WORD)wrap((int)month,1,12);
    maxday=monthdays[systim.wMonth - 1];
    if (systim.wMonth==2 && ((systim.wYear % 4)==0 && ((systim.wYear % 100)!=0 || (systim.wYear % 400)==0)))
      maxday++;
    if (day!=CELLMIN)
      systim.wDay=(WORD)wrap((int)day,1,maxday);
    SetLocalTime(&systim);
  #else
    /* Linux/Unix (and some DOS compilers) have stime(); on Linux/Unix, you
     * must have "root" permission to call stime()
     */
    time_t sec1970;
    struct tm gtm;

    time(&sec1970);
    gtm=*localtime(&sec1970);
    if (year!=CELLMIN)
      gtm.tm_year=year-1900;
    if (month!=CELLMIN)
      gtm.tm_mon=month-1;
    if (day!=CELLMIN)
      gtm.tm_mday=day;
    sec1970=mktime(&gtm);
    stime(&sec1970);
  #endif
}