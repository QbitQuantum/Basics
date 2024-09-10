void DataDrivenCalendarTest::testConvert(TestData *testData,
        const DataMap *settings, UBool forward) {
    UErrorCode status = U_ZERO_ERROR;
    Calendar *toCalendar= NULL;
    const DataMap *currentCase= NULL;
    char toCalLoc[256] = "";
    char fromCalLoc[256] = "";
    // build to calendar
    UnicodeString testSetting = settings->getString("ToCalendar", status);
    if (U_SUCCESS(status)) {
        testSetting.extract(0, testSetting.length(), toCalLoc, (const char*)0);
        toCalendar = Calendar::createInstance(toCalLoc, status);
        if (U_FAILURE(status)) {
            dataerrln(UnicodeString("Unable to instantiate ToCalendar for ")+testSetting);
            return;
        }
    }

    CalendarFieldsSet fromSet, toSet, diffSet;
    SimpleDateFormat fmt(UnicodeString("EEE MMM dd yyyy / YYYY'-W'ww-ee"),
            status);
    if (U_FAILURE(status)) {
        errcheckln(status, "FAIL: Couldn't create SimpleDateFormat: %s",
                u_errorName(status));
        return;
    }
    // Start the processing
    int n = 0;
    while (testData->nextCase(currentCase, status)) {
        ++n;
        Calendar *fromCalendar= NULL;
        UnicodeString locale = currentCase->getString("locale", status);
        if (U_SUCCESS(status)) {
            locale.extract(0, locale.length(), fromCalLoc, (const char*)0); // default codepage.  Invariant codepage doesn't have '@'!
            fromCalendar = Calendar::createInstance(fromCalLoc, status);
            if (U_FAILURE(status)) {
                errln("Unable to instantiate fromCalendar for "+locale);
                return;
            }
        } else {
            errln("No 'locale' line.");
            continue;
        }

        fromSet.clear();
        toSet.clear();

        UnicodeString from = currentCase->getString("from", status);
        if (U_FAILURE(status)) {
            errln("No 'from' line.");
            continue;
        }
        fromSet.parseFrom(from, status);
        if (U_FAILURE(status)) {
            errln("Failed to parse 'from' parameter: "+from);
            continue;
        }
        UnicodeString to = currentCase->getString("to", status);
        if (U_FAILURE(status)) {
            errln("No 'to' line.");
            continue;
        }
        toSet.parseFrom(to, &fromSet, status);
        if (U_FAILURE(status)) {
            errln("Failed to parse 'to' parameter: "+to);
            continue;
        }

        // now, do it.
        if (forward) {
            logln((UnicodeString)"#"+n+" "+locale+"/"+from+" >>> "+toCalLoc+"/"
                    +to);
            testConvert(n, fromSet, fromCalendar, toSet, toCalendar, forward);
        } else {
            logln((UnicodeString)"#"+n+" "+locale+"/"+from+" <<< "+toCalLoc+"/"
                    +to);
            testConvert(n, toSet, toCalendar, fromSet, fromCalendar, forward);
        }

        delete fromCalendar;
    }
    delete toCalendar;
}