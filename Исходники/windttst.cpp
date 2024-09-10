void Win32DateTimeTest::testLocales(TestLog *log)
{
    SYSTEMTIME winNow;
    UDate icuNow = 0;
    SYSTEMTIME st;
    FILETIME ft;
    UnicodeString zoneID;
    const TimeZone *tz = TimeZone::createDefault();
    TIME_ZONE_INFORMATION tzi;

    tz->getID(zoneID);
    if (! uprv_getWindowsTimeZoneInfo(&tzi, zoneID.getBuffer(), zoneID.length())) {
        UBool found = FALSE;
        int32_t ec = TimeZone::countEquivalentIDs(zoneID);

        for (int z = 0; z < ec; z += 1) {
            UnicodeString equiv = TimeZone::getEquivalentID(zoneID, z);

            if (found = uprv_getWindowsTimeZoneInfo(&tzi, equiv.getBuffer(), equiv.length())) {
                break;
            }
        }

        if (! found) {
            GetTimeZoneInformation(&tzi);
        }
    }

    GetSystemTime(&st);
    SystemTimeToFileTime(&st, &ft);
    SystemTimeToTzSpecificLocalTime(&tzi, &st, &winNow);

    int64_t wftNow = ((int64_t) ft.dwHighDateTime << 32) + ft.dwLowDateTime;
    UErrorCode status = U_ZERO_ERROR;

    int64_t udtsNow = utmscale_fromInt64(wftNow, UDTS_WINDOWS_FILE_TIME, &status);

    icuNow = (UDate) utmscale_toInt64(udtsNow, UDTS_ICU4C_TIME, &status);

    int32_t lcidCount = 0;
    Win32Utilities::LCIDRecord *lcidRecords = Win32Utilities::getLocales(lcidCount);

    for(int i = 0; i < lcidCount; i += 1) {
        UErrorCode status = U_ZERO_ERROR;
        WCHAR longDateFormat[81], longTimeFormat[81], wdBuffer[256], wtBuffer[256];
        int32_t calType = 0;

        // NULL localeID means ICU didn't recognize this locale
        if (lcidRecords[i].localeID == NULL) {
            continue;
        }

        GetLocaleInfoW(lcidRecords[i].lcid, LOCALE_SLONGDATE,   longDateFormat, 81);
        GetLocaleInfoW(lcidRecords[i].lcid, LOCALE_STIMEFORMAT, longTimeFormat, 81);
        GetLocaleInfoW(lcidRecords[i].lcid, LOCALE_RETURN_NUMBER|LOCALE_ICALENDARTYPE, (LPWSTR) calType, sizeof(int32_t));

        char localeID[64];

        uprv_strcpy(localeID, lcidRecords[i].localeID);
        uprv_strcat(localeID, getCalendarType(calType));

        UnicodeString ubBuffer, udBuffer, utBuffer;
        Locale ulocale(localeID);
        int32_t wdLength, wtLength;

        wdLength = GetDateFormatW(lcidRecords[i].lcid, DATE_LONGDATE, &winNow, NULL, wdBuffer, UPRV_LENGTHOF(wdBuffer));
        wtLength = GetTimeFormatW(lcidRecords[i].lcid, 0, &winNow, NULL, wtBuffer, UPRV_LENGTHOF(wtBuffer));

        if (uprv_strchr(localeID, '@') > 0) {
            uprv_strcat(localeID, ";");
        } else {
            uprv_strcat(localeID, "@");
        }

        uprv_strcat(localeID, "compat=host");

        Locale wlocale(localeID);
        DateFormat *wbf = DateFormat::createDateTimeInstance(DateFormat::kFull, DateFormat::kFull, wlocale);
        DateFormat *wdf = DateFormat::createDateInstance(DateFormat::kFull, wlocale);
        DateFormat *wtf = DateFormat::createTimeInstance(DateFormat::kFull, wlocale);

        wbf->format(icuNow, ubBuffer);
        wdf->format(icuNow, udBuffer);
        wtf->format(icuNow, utBuffer);

        if (ubBuffer.indexOf(wdBuffer, wdLength - 1, 0) < 0) {
            UnicodeString baseName(wlocale.getBaseName());
            UnicodeString expected(wdBuffer);

            log->errln("DateTime format error for locale " + baseName + ": expected date \"" + expected +
                       "\" got \"" + ubBuffer + "\"");
        }

        if (ubBuffer.indexOf(wtBuffer, wtLength - 1, 0) < 0) {
            UnicodeString baseName(wlocale.getBaseName());
            UnicodeString expected(wtBuffer);

            log->errln("DateTime format error for locale " + baseName + ": expected time \"" + expected +
                       "\" got \"" + ubBuffer + "\"");
        }

        if (udBuffer.compare(wdBuffer) != 0) {
            UnicodeString baseName(wlocale.getBaseName());
            UnicodeString expected(wdBuffer);

            log->errln("Date format error for locale " + baseName + ": expected \"" + expected +
                       "\" got \"" + udBuffer + "\"");
        }

        if (utBuffer.compare(wtBuffer) != 0) {
            UnicodeString baseName(wlocale.getBaseName());
            UnicodeString expected(wtBuffer);

            log->errln("Time format error for locale " + baseName + ": expected \"" + expected +
                       "\" got \"" + utBuffer + "\"");
        }
        delete wbf;
        delete wdf;
        delete wtf;
    }

    Win32Utilities::freeLocales(lcidRecords);
    delete tz;
}