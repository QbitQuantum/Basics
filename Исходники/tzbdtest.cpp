void
TimeZoneBoundaryTest::TestBoundaries()
{
    UErrorCode status = U_ZERO_ERROR;
    TimeZone* pst = TimeZone::createTimeZone("PST");
    Calendar* tempcal = Calendar::createInstance(pst, status);
    if(U_SUCCESS(status)) {
        verifyMapping(*tempcal, 1997, Calendar::APRIL, 3,  0, 238904.0);
        verifyMapping(*tempcal, 1997, Calendar::APRIL, 4,  0, 238928.0);
        verifyMapping(*tempcal, 1997, Calendar::APRIL, 5,  0, 238952.0);
        verifyMapping(*tempcal, 1997, Calendar::APRIL, 5, 23, 238975.0);
        verifyMapping(*tempcal, 1997, Calendar::APRIL, 6,  0, 238976.0);
        verifyMapping(*tempcal, 1997, Calendar::APRIL, 6,  1, 238977.0);
        verifyMapping(*tempcal, 1997, Calendar::APRIL, 6,  3, 238978.0);
    } else {
        dataerrln("Could not create calendar. Error: %s", u_errorName(status));
    }
    TimeZone* utc = TimeZone::createTimeZone("UTC");
    Calendar* utccal =  Calendar::createInstance(utc, status);
    if(U_SUCCESS(status)) {
        verifyMapping(*utccal, 1997, Calendar::APRIL, 6, 0, 238968.0);
    } else {
        dataerrln("Could not create calendar. Error: %s", u_errorName(status));
    }
    TimeZone* save = TimeZone::createDefault();
    TimeZone::setDefault(*pst);

    if (tempcal != NULL) {
        // DST changeover for PST is 4/6/1997 at 2 hours past midnight
        // at 238978.0 epoch hours.
        tempcal->clear();
        tempcal->set(1997, Calendar::APRIL, 6);
        UDate d = tempcal->getTime(status);

        // i is minutes past midnight standard time
        for (int i=-120; i<=180; i+=60)
        {
            UBool inDST = (i >= 120);
            tempcal->setTime(d + i*60*1000, status);
            verifyDST(tempcal->getTime(status),pst, TRUE, inDST, -8*ONE_HOUR,inDST ? -7*ONE_HOUR : -8*ONE_HOUR);
        }
    }
    TimeZone::setDefault(*save);
    delete save;
    delete utccal;
    delete tempcal;

#if 1
    {
        logln("--- Test a ---");
        UDate d = date(97, UCAL_APRIL, 6);
        TimeZone *z = TimeZone::createTimeZone("PST");
        for (int32_t i = 60; i <= 180; i += 15) {
            UBool inDST = (i >= 120);
            UDate e = d + i * 60 * 1000;
            verifyDST(e, z, TRUE, inDST, - 8 * ONE_HOUR, inDST ? - 7 * ONE_HOUR: - 8 * ONE_HOUR);
        }
        delete z;
    }
#endif
#if 1
    {
        logln("--- Test b ---");
        TimeZone *tz;
        TimeZone::setDefault(*(tz = TimeZone::createTimeZone("PST")));
        delete tz;
        logln("========================================");
        findDaylightBoundaryUsingDate(date(97, 0, 1), "PST", PST_1997_BEG);
        logln("========================================");
        findDaylightBoundaryUsingDate(date(97, 6, 1), "PDT", PST_1997_END);
    }
#endif
#if 1
    {
        logln("--- Test c ---");
        logln("========================================");
        TimeZone* z = TimeZone::createTimeZone("Australia/Adelaide");
        findDaylightBoundaryUsingTimeZone(date(97, 0, 1), TRUE, 859653000000.0, z);
        logln("========================================");
        findDaylightBoundaryUsingTimeZone(date(97, 6, 1), FALSE, 877797000000.0, z);
        delete z;
    }
#endif
#if 1
    {
        logln("--- Test d ---");
        logln("========================================");
        findDaylightBoundaryUsingTimeZone(date(97, 0, 1), FALSE, PST_1997_BEG);
        logln("========================================");
        findDaylightBoundaryUsingTimeZone(date(97, 6, 1), TRUE, PST_1997_END);
    }
#endif
#if 0
    {
        logln("--- Test e ---");
        TimeZone *z = TimeZone::createDefault();
        logln(UnicodeString("") + z->getOffset(1, 97, 3, 4, 6, 0) + " " + date(97, 3, 4));
        logln(UnicodeString("") + z->getOffset(1, 97, 3, 5, 7, 0) + " " + date(97, 3, 5));
        logln(UnicodeString("") + z->getOffset(1, 97, 3, 6, 1, 0) + " " + date(97, 3, 6));
        logln(UnicodeString("") + z->getOffset(1, 97, 3, 7, 2, 0) + " " + date(97, 3, 7));
        delete z;
    }
#endif
}