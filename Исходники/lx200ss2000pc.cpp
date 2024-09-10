bool LX200SS2000PC::updateTime(ln_date * utc, double utc_offset) {
  bool result = true;
  // This method is largely identical to the one in the LX200Generic class.
  // The difference is that it ensures that updates that require planetary
  // data to be recomputed by the SkySensor2000PC are only done when really
  // necessary because this takes quite some time.
  if (!isSimulation()) {
    result = false;
    struct ln_zonedate ltm;
    ln_date_to_zonedate(utc, &ltm, static_cast<long>(utc_offset*3600.0+0.5));
    DEBUGF(INDI::Logger::DBG_DEBUG, "New zonetime is %04d-%02d-%02d %02d:%02d:%06.3f (offset=%ld)", ltm.years, ltm.months, ltm.days, ltm.hours, ltm.minutes, ltm.seconds, ltm.gmtoff);
    JD = ln_get_julian_day(utc);
    DEBUGF(INDI::Logger::DBG_DEBUG, "New JD is %f", JD);
    if (setLocalTime(PortFD, ltm.hours, ltm.minutes, static_cast<int>(ltm.seconds+0.5)) < 0) {
      DEBUG(INDI::Logger::DBG_ERROR, "Error setting local time.");
    }
    else if (!setCalenderDate(ltm.years, ltm.months, ltm.days)) {
      DEBUG(INDI::Logger::DBG_ERROR, "Error setting local date.");
    }
    // Meade defines UTC Offset as the offset ADDED to local time to yield UTC, which
    // is the opposite of the standard definition of UTC offset!
    else if (!setUTCOffset(-static_cast<int>(utc_offset))) {
      DEBUG(INDI::Logger::DBG_ERROR, "Error setting UTC Offset.");
    }
    else {
      DEBUG(INDI::Logger::DBG_SESSION, "Time updated.");
      result = true;
    }
  }
  return result;
}