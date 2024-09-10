word
pl_convert_time(term_t time, term_t year, term_t month,
		term_t day, term_t hour, term_t minute,
		term_t second, term_t usec)
{ double tf;

  if ( PL_get_float(time, &tf) && tf <= PLMAXINT && tf >= PLMININT )
  { long t    = (long) tf;
    long us   = (long)((tf - (double) t) * 1000.0);
    struct tm *tm = LocalTime(&t);

    if ( PL_unify_integer(year,   tm->tm_year + 1900) &&
	 PL_unify_integer(month,  tm->tm_mon + 1) &&
	 PL_unify_integer(day,    tm->tm_mday) &&
	 PL_unify_integer(hour,   tm->tm_hour) &&
	 PL_unify_integer(minute, tm->tm_min) &&
	 PL_unify_integer(second, tm->tm_sec) &&
	 PL_unify_integer(usec,   us) )
      succeed;
    else
      fail;
  }

  return PL_error("convert_time", 8, NULL, ERR_TYPE, ATOM_time_stamp, time);
}