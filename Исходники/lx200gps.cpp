bool LX200GPS::updateTime(ln_date *utc, double utc_offset)
{
    ln_zonedate ltm;

    if (isSimulation())
        return true;

    JD = ln_get_julian_day(utc);

    DEBUGF(INDI::Logger::DBG_DEBUG, "New JD is %f", (float)JD);

    ln_date_to_zonedate(utc, &ltm, utc_offset * 3600);

    DEBUGF(INDI::Logger::DBG_DEBUG, "Local time is %02d:%02d:%02g", ltm.hours, ltm.minutes, ltm.seconds);

    // Set Local Time
    if (setLocalTime(PortFD, ltm.hours, ltm.minutes, ltm.seconds) < 0)
    {
        DEBUG(INDI::Logger::DBG_ERROR, "Error setting local time time.");
        return false;
    }

    if (setCalenderDate(PortFD, utc->days, utc->months, utc->years) < 0)
    {
        DEBUG(INDI::Logger::DBG_ERROR, "Error setting UTC date.");
        return false;
    }

    // Meade defines UTC Offset as the offset ADDED to local time to yield UTC, which
    // is the opposite of the standard definition of UTC offset!
    if (setUTCOffset(PortFD, (utc_offset * -1.0)) < 0)
    {
        DEBUG(INDI::Logger::DBG_ERROR, "Error setting UTC Offset.");
        return false;
    }

    DEBUG(INDI::Logger::DBG_SESSION, "Time updated, updating planetary data...");
    return true;
}