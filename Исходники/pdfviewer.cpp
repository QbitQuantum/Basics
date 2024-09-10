static void printInfoDate(Dict *infoDict, char *key, char *text) {
  Object obj;
  char *s;
  int year, mon, day, hour, min, sec, tz_hour, tz_minute;
  char tz;
  struct tm tmStruct;
  char buf[256];

  if (infoDict->lookup(key, &obj)->isString()) {
    fputs(text, stdout);
    s = obj.getString()->getCString();
    // TODO do something with the timezone info
    if ( parseDateString( s, &year, &mon, &day, &hour, &min, &sec, &tz, &tz_hour, &tz_minute ) ) {
      tmStruct.tm_year = year - 1900;
      tmStruct.tm_mon = mon - 1;
      tmStruct.tm_mday = day;
      tmStruct.tm_hour = hour;
      tmStruct.tm_min = min;
      tmStruct.tm_sec = sec;
      tmStruct.tm_wday = -1;
      tmStruct.tm_yday = -1;
      tmStruct.tm_isdst = -1;
      // compute the tm_wday and tm_yday fields
      if (mktime(&tmStruct) != (time_t)-1 &&
          strftime(buf, sizeof(buf), "%c", &tmStruct)) {
        fputs(buf, stdout);
      } else {
        fputs(s, stdout);
      }
    } else {
      fputs(s, stdout);
    }
    fputc('\n', stdout);
  }
  obj.free();
}