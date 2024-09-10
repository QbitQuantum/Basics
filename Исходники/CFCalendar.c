static void __CFCalendarSetToFirstInstant(CFCalendarRef calendar, CFCalendarUnit unit, CFAbsoluteTime at) {
    // Set UCalendar to first instant of unit prior to 'at'
    UErrorCode status = U_ZERO_ERROR;
    UDate udate = floor((at + kCFAbsoluteTimeIntervalSince1970) * 1000.0);
    ucal_setMillis(calendar->_cal, udate, &status);
    int target_era = INT_MIN;
    switch (unit) { // largest to smallest, we set the fields to their minimum value
    case kCFCalendarUnitWeek:
	{
	// reduce to first day of week, then reduce the rest of the day
        int32_t goal = ucal_getAttribute(calendar->_cal, UCAL_FIRST_DAY_OF_WEEK);
	int32_t dow = ucal_get(calendar->_cal, UCAL_DAY_OF_WEEK, &status);
	while (dow != goal) {
	    ucal_add(calendar->_cal, UCAL_DAY_OF_MONTH, -1, &status);
	    dow = ucal_get(calendar->_cal, UCAL_DAY_OF_WEEK, &status);
	}
	goto day;
	}
    case kCFCalendarUnitEra:
	{
	target_era = ucal_get(calendar->_cal, UCAL_ERA, &status);
	ucal_set(calendar->_cal, UCAL_YEAR, ucal_getLimit(calendar->_cal, UCAL_YEAR, UCAL_ACTUAL_MINIMUM, &status));
	}
    case kCFCalendarUnitYear:
	ucal_set(calendar->_cal, UCAL_MONTH, ucal_getLimit(calendar->_cal, UCAL_MONTH, UCAL_ACTUAL_MINIMUM, &status));
    case kCFCalendarUnitMonth:
	ucal_set(calendar->_cal, UCAL_DAY_OF_MONTH, ucal_getLimit(calendar->_cal, UCAL_DAY_OF_MONTH, UCAL_ACTUAL_MINIMUM, &status));
    case kCFCalendarUnitWeekday:
    case kCFCalendarUnitDay:
    day:;
	ucal_set(calendar->_cal, UCAL_HOUR_OF_DAY, ucal_getLimit(calendar->_cal, UCAL_HOUR_OF_DAY, UCAL_ACTUAL_MINIMUM, &status));
    case kCFCalendarUnitHour:
	ucal_set(calendar->_cal, UCAL_MINUTE, ucal_getLimit(calendar->_cal, UCAL_MINUTE, UCAL_ACTUAL_MINIMUM, &status));
    case kCFCalendarUnitMinute:
	ucal_set(calendar->_cal, UCAL_SECOND, ucal_getLimit(calendar->_cal, UCAL_SECOND, UCAL_ACTUAL_MINIMUM, &status));
    case kCFCalendarUnitSecond:
	ucal_set(calendar->_cal, UCAL_MILLISECOND, 0);
    }
    if (INT_MIN != target_era && ucal_get(calendar->_cal, UCAL_ERA, &status) < target_era) {
	// In the Japanese calendar, and possibly others, eras don't necessarily
	// start on the first day of a year, so the previous code may have backed
	// up into the previous era, and we have to correct forward.
	UDate bad_udate = ucal_getMillis(calendar->_cal, &status);
	ucal_add(calendar->_cal, UCAL_MONTH, 1, &status);
	while (ucal_get(calendar->_cal, UCAL_ERA, &status) < target_era) {
	    bad_udate = ucal_getMillis(calendar->_cal, &status);
	    ucal_add(calendar->_cal, UCAL_MONTH, 1, &status);
	}
	udate = ucal_getMillis(calendar->_cal, &status);
	// target date is between bad_udate and udate
	for (;;) {
	    UDate test_udate = (udate + bad_udate) / 2;
	    ucal_setMillis(calendar->_cal, test_udate, &status);
	    if (ucal_get(calendar->_cal, UCAL_ERA, &status) < target_era) {
		bad_udate = test_udate;
	    } else {
		udate = test_udate;
	    }
	    if (fabs(udate - bad_udate) < 1000) break;
	}
	do {
	    bad_udate = floor((bad_udate + 1000) / 1000) * 1000;
	    ucal_setMillis(calendar->_cal, bad_udate, &status);
	} while (ucal_get(calendar->_cal, UCAL_ERA, &status) < target_era);
    }
}