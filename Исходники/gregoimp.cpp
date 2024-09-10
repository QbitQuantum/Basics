void CalendarData::initData(const char *locale, const char *type, UErrorCode& status) {
  fOtherFillin = ures_open(U_CALENDAR_DATA, locale, &status);
  fFillin = ures_getByKey(fOtherFillin, U_CALENDAR_KEY, fFillin, &status);

  if((type != NULL) && 
     (*type != '\0') && 
     (uprv_strcmp(type, U_GREGORIAN_KEY)))
  {
    fBundle = ures_getByKeyWithFallback(fFillin, type, NULL, &status);
    fFallback = ures_getByKeyWithFallback(fFillin, U_GREGORIAN_KEY, NULL, &status);

#if defined (U_DEBUG_CALDATA)
    fprintf(stderr, "%p: CalendarData(%s, %s, %s) -> main(%p, %s)=%s, fallback(%p, %s)=%s\n", 
            this, locale, type, u_errorName(status), fBundle, type, fBundle?ures_getLocale(fBundle, &status):"", 
            fFallback, U_GREGORIAN_KEY, fFallback?ures_getLocale(fFallback, &status):"");
#endif

  } else {
    fBundle = ures_getByKeyWithFallback(fFillin, U_GREGORIAN_KEY, NULL, &status);
#if defined (U_DEBUG_CALDATA)
    fprintf(stderr, "%p: CalendarData(%s, %s, %s) -> main(%p, %s)=%s, fallback = NULL\n",
            this, locale, type, u_errorName(status), fBundle, U_GREGORIAN_KEY, fBundle?ures_getLocale(fBundle, &status):"" );
#endif
  }
}