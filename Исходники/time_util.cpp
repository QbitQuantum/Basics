bool_t DayTime::get_localtime(uint32_t* year, uint32_t* mon, uint32_t* day
                              , uint32_t* hour, uint32_t* min, uint32_t* sec
                              , uint32_t srcTime) {

  /* */
  time_t now = srcTime;
  struct tm today;
  LOCALTIME(today, now);
  
  if (year) { *(year) = today.tm_year + 1900; }
  if (mon)  { *(mon)  = today.tm_mon + 1; }
  if (day)  { *(day)  = today.tm_mday; }

  if (hour) { *(hour) = today.tm_hour; }
  if (min)  { *(min)  = today.tm_min; }
  if (sec)  { *(sec)  = today.tm_sec; }

  return TRUE;
}