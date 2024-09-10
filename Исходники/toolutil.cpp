U_CAPI int32_t U_EXPORT2 getCurrentYear() {
#if !UCONFIG_NO_FORMATTING
    UErrorCode status=U_ZERO_ERROR;    
    UCalendar *cal = NULL;

    if(currentYear == -1) {
        cal = ucal_open(NULL, -1, NULL, UCAL_TRADITIONAL, &status);
        ucal_setMillis(cal, ucal_getNow(), &status);
        currentYear = ucal_get(cal, UCAL_YEAR, &status);
        ucal_close(cal);
    }
#else
    /* No formatting- no way to set the current year. */
#endif
    return currentYear;
}