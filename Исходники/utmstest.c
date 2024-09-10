/*
 * ICU's Universal Time Scale is designed to be tick-for-tick compatible with
 * .Net System.DateTime. Verify that this is so for the
 * .Net-supported date range (years 1-9999 AD).
 * This requires a proleptic Gregorian calendar because that's what .Net uses.
 * Proleptic: No Julian/Gregorian switchover, or a switchover before
 * any date that we test, that is, before 0001 AD.
 */
static void
TestDotNet() {
    static const UChar utc[] = { 0x45, 0x74, 0x63, 0x2f, 0x47, 0x4d, 0x54, 0 }; /* "Etc/GMT" */
    const int32_t dayMillis = 86400 * INT64_C(1000);    /* 1 day = 86400 seconds */
    const int64_t dayTicks = 86400 * INT64_C(10000000);
    const DotNetDateTimeTicks *dt;
    UCalendar *cal;
    UErrorCode errorCode;
    UDate icuDate;
    int64_t ticks, millis;
    int32_t i;

    /* Open a proleptic Gregorian calendar. */
    errorCode = U_ZERO_ERROR;
    cal = ucal_open(utc, -1, "", UCAL_GREGORIAN, &errorCode);
    ucal_setGregorianChange(cal, -1000000 * (dayMillis * (UDate)1), &errorCode);
    if(U_FAILURE(errorCode)) {
        log_err("ucal_open(UTC/proleptic Gregorian) failed: %s\n", u_errorName(errorCode));
        ucal_close(cal);
        return;
    }
    for(i = 0; i < LENGTHOF(dotNetDateTimeTicks); ++i) {
        /* Test conversion from .Net/Universal time to ICU time. */
        dt = dotNetDateTimeTicks + i;
        millis = utmscale_toInt64(dt->ticks, UDTS_ICU4C_TIME, &errorCode);
        ucal_clear(cal);
        ucal_setDate(cal, dt->year, dt->month - 1, dt->day, &errorCode); /* Java & ICU use January = month 0. */
        icuDate = ucal_getMillis(cal, &errorCode);
        if(millis != icuDate) {
            /* Print days not millis to stay within printf() range. */
            log_err("utmscale_toInt64(ticks[%d], ICU4C)=%dd != %dd=ucal_getMillis(%04d-%02d-%02d)\n",
                    (int)i, (int)(millis/dayMillis), (int)(icuDate/dayMillis), (int)dt->year, (int)dt->month, (int)dt->day);
        }

        /* Test conversion from ICU time to .Net/Universal time. */
        ticks = utmscale_fromInt64((int64_t)icuDate, UDTS_ICU4C_TIME, &errorCode);
        if(ticks != dt->ticks) {
            /* Print days not ticks to stay within printf() range. */
            log_err("utmscale_fromInt64(date[%d], ICU4C)=%dd != %dd=.Net System.DateTime(%04d-%02d-%02d).Ticks\n",
                    (int)i, (int)(ticks/dayTicks), (int)(dt->ticks/dayTicks), (int)dt->year, (int)dt->month, (int)dt->day);
        }
    }

    ucal_close(cal);
}