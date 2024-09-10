// Qt wrapper around qt_ucal_getTimeZoneTransitionDate & ucal_get
static QTimeZonePrivate::Data ucalTimeZoneTransition(UCalendar *m_ucal,
                                                     UTimeZoneTransitionType type,
                                                     qint64 atMSecsSinceEpoch)
{
    QTimeZonePrivate::Data tran = QTimeZonePrivate::invalidData();

    // Clone the ucal so we don't change the shared object
    UErrorCode status = U_ZERO_ERROR;
    UCalendar *ucal = ucal_clone(m_ucal, &status);
    if (!U_SUCCESS(status))
        return tran;

    // Set the date to find the transition for
    status = U_ZERO_ERROR;
    ucal_setMillis(ucal, atMSecsSinceEpoch, &status);

    // Find the transition time
    UDate tranMSecs = 0;
    status = U_ZERO_ERROR;
    bool ok = ucal_getTimeZoneTransitionDate(ucal, type, &tranMSecs, &status);

    // Set the transition time to find the offsets for
    if (U_SUCCESS(status) && ok) {
        status = U_ZERO_ERROR;
        ucal_setMillis(ucal, tranMSecs, &status);
    }

    int32_t utc = 0;
    if (U_SUCCESS(status) && ok) {
        status = U_ZERO_ERROR;
        utc = ucal_get(ucal, UCAL_ZONE_OFFSET, &status) / 1000;
    }

    int32_t dst = 0;
    if (U_SUCCESS(status) && ok) {
        status = U_ZERO_ERROR;
        dst = ucal_get(ucal, UCAL_DST_OFFSET, &status) / 1000;
    }

    ucal_close(ucal);
    if (!U_SUCCESS(status) || !ok)
        return tran;
    tran.atMSecsSinceEpoch = tranMSecs;
    tran.offsetFromUtc = utc + dst;
    tran.standardTimeOffset = utc;
    tran.daylightTimeOffset = dst;
    // TODO No ICU API, use short name instead
    if (dst == 0)
        tran.abbreviation = ucalTimeZoneDisplayName(m_ucal, QTimeZone::StandardTime,
                                                    QTimeZone::ShortName, QLocale().name());
    else
        tran.abbreviation = ucalTimeZoneDisplayName(m_ucal, QTimeZone::DaylightTime,
                                                    QTimeZone::ShortName, QLocale().name());
    return tran;
}