int main(int argc, char *argv[])
{
  CURL    *curl;
  conf_t  conf[1];
  int     OptionIndex;
  struct  tm *lt;
  struct  tm *gmt;
  time_t  tt;
  time_t  tt_local;
  time_t  tt_gmt;
  double  tzonediffFloat;
  int     tzonediffWord;
  char    timeBuf[61];
  char    tzoneBuf[16];
  int     RetValue;

  OptionIndex     = 0;
  ShowAllHeader   = 0;    /* Do not show HTTP Header */
  AutoSyncTime    = 0;    /* Do not synchronise computer clock */
  RetValue        = 0;    /* Successful Exit */
  conf_init(conf);

  if (argc > 1) {
    while (OptionIndex < argc) {
      if (strncmp(argv[OptionIndex], "--server=", 9) == 0)
        snprintf(conf->timeserver, MAX_STRING, "%s", &argv[OptionIndex][9]);

      if (strcmp(argv[OptionIndex], "--showall") == 0)
        ShowAllHeader = 1;

      if (strcmp(argv[OptionIndex], "--synctime") == 0)
        AutoSyncTime = 1;

      if (strncmp(argv[OptionIndex], "--proxy-user="******"%s", &argv[OptionIndex][13]);

      if (strncmp(argv[OptionIndex], "--proxy=", 8) == 0)
        snprintf(conf->http_proxy, MAX_STRING, "%s", &argv[OptionIndex][8]);

      if ((strcmp(argv[OptionIndex], "--help") == 0) ||
          (strcmp(argv[OptionIndex], "/?") == 0)) {
        showUsage();
        return 0;
      }
      OptionIndex++;
    }
  }

  if (*conf->timeserver == 0)     /* Use default server for time information */
    snprintf(conf->timeserver, MAX_STRING, "%s", DefaultTimeServer[0]);

  /* Init CURL before usage */
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  if (curl) {
    SyncTime_CURL_Init(curl, conf->http_proxy, conf->proxy_user);

    /* Calculating time diff between GMT and localtime */
    tt       = time(0);
    lt       = localtime(&tt);
    tt_local = mktime(lt);
    gmt      = gmtime(&tt);
    tt_gmt   = mktime(gmt);
    tzonediffFloat = difftime(tt_local, tt_gmt);
    tzonediffWord  = (int)(tzonediffFloat/3600.0);

    if ((double)(tzonediffWord * 3600) == tzonediffFloat)
      snprintf(tzoneBuf, 15, "%+03d'00'", tzonediffWord);
    else
      snprintf(tzoneBuf, 15, "%+03d'30'", tzonediffWord);

    /* Get current system time and local time */
    GetSystemTime(&SYSTime);
    GetLocalTime(&LOCALTime);
    snprintf(timeBuf, 60, "%s, %02d %s %04d %02d:%02d:%02d.%03d, ",
             DayStr[LOCALTime.wDayOfWeek], LOCALTime.wDay,
             MthStr[LOCALTime.wMonth-1], LOCALTime.wYear,
             LOCALTime.wHour, LOCALTime.wMinute, LOCALTime.wSecond,
             LOCALTime.wMilliseconds);

    fprintf(stderr, "Fetch: %s\n\n", conf->timeserver);
    fprintf(stderr, "Before HTTP. Date: %s%s\n\n", timeBuf, tzoneBuf);

    /* HTTP HEAD command to the Webserver */
    SyncTime_CURL_Fetch(curl, conf->timeserver, "index.htm",
                        HTTP_COMMAND_HEAD);

    GetLocalTime(&LOCALTime);
    snprintf(timeBuf, 60, "%s, %02d %s %04d %02d:%02d:%02d.%03d, ",
             DayStr[LOCALTime.wDayOfWeek], LOCALTime.wDay,
             MthStr[LOCALTime.wMonth-1], LOCALTime.wYear,
             LOCALTime.wHour, LOCALTime.wMinute, LOCALTime.wSecond,
             LOCALTime.wMilliseconds);
    fprintf(stderr, "\nAfter  HTTP. Date: %s%s\n", timeBuf, tzoneBuf);

    if (AutoSyncTime == 3) {
      /* Synchronising computer clock */
      if (!SetSystemTime(&SYSTime)) {  /* Set system time */
        fprintf(stderr, "ERROR: Unable to set system time.\n");
        RetValue = 1;
      }
      else {
        /* Successfully re-adjusted computer clock */
        GetLocalTime(&LOCALTime);
        snprintf(timeBuf, 60, "%s, %02d %s %04d %02d:%02d:%02d.%03d, ",
                 DayStr[LOCALTime.wDayOfWeek], LOCALTime.wDay,
                 MthStr[LOCALTime.wMonth-1], LOCALTime.wYear,
                 LOCALTime.wHour, LOCALTime.wMinute, LOCALTime.wSecond,
                 LOCALTime.wMilliseconds);
        fprintf(stderr, "\nNew System's Date: %s%s\n", timeBuf, tzoneBuf);
      }
    }

    /* Cleanup before exit */
    conf_init(conf);
    curl_easy_cleanup(curl);
  }
  return RetValue;
}