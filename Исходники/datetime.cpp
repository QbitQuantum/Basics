   void DateTime::_setTime(const uint64 tt)
   {
      _millis = (time_t)tt;

      struct tm tm_;
#if defined(_WINDOWS) || defined(_WIN32)
      localtime_s(&tm_, &_millis);
#else
      tm_ = localtime_r(&tt);
#endif
      _year = tm_.tm_year + 1900;
      _mon  = tm_.tm_mon + 1;
      _day  = tm_.tm_mday;
      _hour = tm_.tm_hour;
      _min  = tm_.tm_min;
      _sec  = tm_.tm_sec;
      _wday = tm_.tm_wday;
   }