  Time* Time::from_array(STATE, Object* self, 
                      Fixnum* sec, Fixnum* min, Fixnum* hour,
                      Fixnum* mday, Fixnum* mon, Fixnum* year, Fixnum* usec,
                      Fixnum* isdst, Object* from_gmt) {
    struct tm tm;

    tm.tm_sec = sec->to_native();
    if(tm.tm_sec < 0 || tm.tm_sec > 60) {
      Exception::argument_error(state, "sec must be in 0..60");
    }

    tm.tm_min = min->to_native();
    if(tm.tm_min < 0 || tm.tm_min > 60) {
      Exception::argument_error(state, "min must be in 0..60");
    }

    tm.tm_hour = hour->to_native();
    if(tm.tm_hour < 0 || tm.tm_hour > 24) {
      Exception::argument_error(state, "hour must be in 0..24");
    }

    tm.tm_mday = mday->to_native();
    if(tm.tm_mday < 1 || tm.tm_mday > 31) {
      Exception::argument_error(state, "mday must be in 1..31");
    }

    tm.tm_mon = mon->to_native() - 1;
    if(tm.tm_mon < 0 || tm.tm_mon > 11) {
      Exception::argument_error(state, "mon must be in 0..11");
    }

    tm.tm_wday = -1;
#ifdef HAVE_TM_GMTOFF
    tm.tm_gmtoff = 0;
#endif
#ifdef HAVE_TM_ZONE
    tm.tm_zone = 0;
#endif
    tm.tm_year = year->to_native() - 1900;

    tm.tm_isdst = isdst->to_native();

    time_t seconds = -1;

    if(RTEST(from_gmt)) {
      seconds = ::timegm(&tm);
    } else {
      tzset();
      seconds = ::mktime(&tm);
    }

    int err = 0;

    if(seconds == -1) {
      int utc_p = from_gmt->true_p() ? 1 : 0;
      seconds = mktime_extended(&tm, utc_p, &err);
    }

    if(err) return (Time*)Primitives::failure();

    Time* obj = state->new_object<Time>(as<Class>(self));
    obj->seconds_ = seconds;
    obj->microseconds_ = usec->to_native();
    obj->is_gmt(state, RTEST(from_gmt) ? Qtrue : Qfalse);

    return obj;
  }