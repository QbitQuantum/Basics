void
CalendarLimitTest::doLimitsTest(Calendar& cal,
                                const int32_t* fieldsToTest,
                                UDate startDate,
                                int32_t testDuration) {
    static const int32_t FIELDS[] = {
        UCAL_ERA,
        UCAL_YEAR,
        UCAL_MONTH,
        UCAL_WEEK_OF_YEAR,
        UCAL_WEEK_OF_MONTH,
        UCAL_DAY_OF_MONTH,
        UCAL_DAY_OF_YEAR,
        UCAL_DAY_OF_WEEK_IN_MONTH,
        UCAL_YEAR_WOY,
        UCAL_EXTENDED_YEAR,
        -1,
    };

    static const char* FIELD_NAME[] = {
        "ERA", "YEAR", "MONTH", "WEEK_OF_YEAR", "WEEK_OF_MONTH",
        "DAY_OF_MONTH", "DAY_OF_YEAR", "DAY_OF_WEEK",
        "DAY_OF_WEEK_IN_MONTH", "AM_PM", "HOUR", "HOUR_OF_DAY",
        "MINUTE", "SECOND", "MILLISECOND", "ZONE_OFFSET",
        "DST_OFFSET", "YEAR_WOY", "DOW_LOCAL", "EXTENDED_YEAR",
        "JULIAN_DAY", "MILLISECONDS_IN_DAY",
        "IS_LEAP_MONTH"
    };

    UErrorCode status = U_ZERO_ERROR;
    int32_t i, j;
    UnicodeString ymd;

    GregorianCalendar greg(status);
    if (failure(status, "new GregorianCalendar")) {
        return;
    }
    greg.setTime(startDate, status);
    if (failure(status, "GregorianCalendar::setTime")) {
        return;
    }
    logln((UnicodeString)"Start: " + startDate);

    if (fieldsToTest == NULL) {
        fieldsToTest = FIELDS;
    }


    // Keep a record of minima and maxima that we actually see.
    // These are kept in an array of arrays of hashes.
    int32_t limits[UCAL_FIELD_COUNT][4];
    for (j = 0; j < UCAL_FIELD_COUNT; j++) {
        limits[j][0] = INT32_MAX;
        limits[j][1] = INT32_MIN;
        limits[j][2] = INT32_MAX;
        limits[j][3] = INT32_MIN;
    }

    // This test can run for a long time; show progress.
    UDate millis = ucal_getNow();
    UDate mark = millis + 5000; // 5 sec
    millis -= testDuration * 1000; // stop time if testDuration<0

    for (i = 0;
         testDuration > 0 ? i < testDuration
                        : ucal_getNow() < millis;
         ++i) {
        if (ucal_getNow() >= mark) {
            logln((UnicodeString)"(" + i + " days)");
            mark += 5000; // 5 sec
        }
        UDate testMillis = greg.getTime(status);
        cal.setTime(testMillis, status);
        cal.setMinimalDaysInFirstWeek(1);
        if (failure(status, "Calendar set/getTime")) {
            return;
        }
        for (j = 0; fieldsToTest[j] >= 0; ++j) {
            UCalendarDateFields f = (UCalendarDateFields)fieldsToTest[j];
            int32_t v = cal.get(f, status);
            int32_t minActual = cal.getActualMinimum(f, status);
            int32_t maxActual = cal.getActualMaximum(f, status);
            int32_t minLow = cal.getMinimum(f);
            int32_t minHigh = cal.getGreatestMinimum(f);
            int32_t maxLow = cal.getLeastMaximum(f);
            int32_t maxHigh = cal.getMaximum(f);

            if (limits[j][0] > minActual) {
                // the minimum
                limits[j][0] = minActual;
            }
            if (limits[j][1] < minActual) {
                // the greatest minimum
                limits[j][1] = minActual;
            }
            if (limits[j][2] > maxActual) {
                // the least maximum
                limits[j][2] = maxActual;
            }
            if (limits[j][3] < maxActual) {
                // the maximum
                limits[j][3] = maxActual;
            }

            if (minActual < minLow || minActual > minHigh) {
                errln((UnicodeString)"Fail: [" + cal.getType() + "] " +
                      ymdToString(cal, ymd) +
                      " Range for min of " + FIELD_NAME[f] + "(" + f +
                      ")=" + minLow + ".." + minHigh +
                      ", actual_min=" + minActual);
            }
            if (maxActual < maxLow || maxActual > maxHigh) {
                if ( uprv_strcmp(cal.getType(), "chinese") == 0 &&
                        testMillis >= 2842992000000.0  && testMillis <= 2906668800000.0 &&
                     logKnownIssue("12620", "chinese calendar failures for some actualMax tests")) {
                    logln((UnicodeString)"KnownFail: [" + cal.getType() + "] " +
                          ymdToString(cal, ymd) +
                          " Range for max of " + FIELD_NAME[f] + "(" + f +
                          ")=" + maxLow + ".." + maxHigh +
                          ", actual_max=" + maxActual);
                } else {
                    errln((UnicodeString)"Fail: [" + cal.getType() + "] " +
                          ymdToString(cal, ymd) +
                          " Range for max of " + FIELD_NAME[f] + "(" + f +
                          ")=" + maxLow + ".." + maxHigh +
                          ", actual_max=" + maxActual);
                }
            }
            if (v < minActual || v > maxActual) {
                // timebomb per #9967, fix with #9972
                if ( uprv_strcmp(cal.getType(), "dangi") == 0 &&
                        testMillis >= 1865635198000.0  &&
                     logKnownIssue("9972", "as per #9967")) { // Feb 2029 gregorian, end of dangi 4361
                    logln((UnicodeString)"KnownFail: [" + cal.getType() + "] " +
                          ymdToString(cal, ymd) +
                          " " + FIELD_NAME[f] + "(" + f + ")=" + v +
                          ", actual=" + minActual + ".." + maxActual +
                          ", allowed=(" + minLow + ".." + minHigh + ")..(" +
                          maxLow + ".." + maxHigh + ")");
                } else if ( uprv_strcmp(cal.getType(), "chinese") == 0 &&
                        testMillis >= 2842992000000.0  && testMillis <= 2906668800000.0 &&
                     logKnownIssue("12620", "chinese calendar failures for some actualMax tests")) {
                    logln((UnicodeString)"KnownFail: [" + cal.getType() + "] " +
                          ymdToString(cal, ymd) +
                          " " + FIELD_NAME[f] + "(" + f + ")=" + v +
                          ", actual=" + minActual + ".." + maxActual +
                          ", allowed=(" + minLow + ".." + minHigh + ")..(" +
                          maxLow + ".." + maxHigh + ")");
                } else {
                    errln((UnicodeString)"Fail: [" + cal.getType() + "] " +
                          ymdToString(cal, ymd) +
                          " " + FIELD_NAME[f] + "(" + f + ")=" + v +
                          ", actual=" + minActual + ".." + maxActual +
                          ", allowed=(" + minLow + ".." + minHigh + ")..(" +
                          maxLow + ".." + maxHigh + ")");
                }
            }
        }
        greg.add(UCAL_DAY_OF_YEAR, 1, status);
        if (failure(status, "Calendar::add")) {
            return;
        }
    }

    // Check actual maxima and minima seen against ranges returned
    // by API.
    UnicodeString buf;
    for (j = 0; fieldsToTest[j] >= 0; ++j) {
        int32_t rangeLow, rangeHigh;
        UBool fullRangeSeen = TRUE;
        UCalendarDateFields f = (UCalendarDateFields)fieldsToTest[j];

        buf.remove();
        buf.append((UnicodeString)"[" + cal.getType() + "] " + FIELD_NAME[f]);

        // Minumum
        rangeLow = cal.getMinimum(f);
        rangeHigh = cal.getGreatestMinimum(f);
        if (limits[j][0] != rangeLow || limits[j][1] != rangeHigh) {
            fullRangeSeen = FALSE;
        }
        buf.append((UnicodeString)" minima range=" + rangeLow + ".." + rangeHigh);
        buf.append((UnicodeString)" minima actual=" + limits[j][0] + ".." + limits[j][1]);

        // Maximum
        rangeLow = cal.getLeastMaximum(f);
        rangeHigh = cal.getMaximum(f);
        if (limits[j][2] != rangeLow || limits[j][3] != rangeHigh) {
            fullRangeSeen = FALSE;
        }
        buf.append((UnicodeString)" maxima range=" + rangeLow + ".." + rangeHigh);
        buf.append((UnicodeString)" maxima actual=" + limits[j][2] + ".." + limits[j][3]);

        if (fullRangeSeen) {
            logln((UnicodeString)"OK: " + buf);
        } else {
            // This may or may not be an error -- if the range of dates
            // we scan over doesn't happen to contain a minimum or
            // maximum, it doesn't mean some other range won't.
            logln((UnicodeString)"Warning: " + buf);
        }
    }

    logln((UnicodeString)"End: " + greg.getTime(status));
}