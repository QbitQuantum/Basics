/*--------------------------------------------------------------------------*/
Tbool CSystemBase::setSystemDateTime(const NTime::CDateTime& a_crDateTime, const Tbool a_cIsUTC/* = true */)
{ CALL
  SYSTEMTIME system_time;

  // Get system time in UTC or local time form.
  if (a_cIsUTC)
    GetSystemTime(&system_time);
  else
    GetLocalTime(&system_time);

  // Update time fields.
  system_time.wYear = a_crDateTime.getDate().getClearYears();
  system_time.wMonth = a_crDateTime.getDate().getClearMonths() + 1;
  system_time.wDay = a_crDateTime.getDate().getClearDays() + 1;
  system_time.wHour = a_crDateTime.getTime().getClearHours();
  system_time.wMinute = a_crDateTime.getTime().getClearMinutes();
  system_time.wSecond = a_crDateTime.getTime().getClearSeconds();
  system_time.wMilliseconds = a_crDateTime.getTime().getClearMilliseconds();

  // Set system time in UTC or local time form.
  //
  // The system uses UTC internally. Therefore, when  you  call  SetLocalTime,
  // the system  uses  the  current  time  zone  information  to  perform  the
  // conversion, including the daylight saving time  setting.  Note  that  the
  // system uses the daylight saving time setting of the current time, not the
  // new time you are setting. Therefore, to ensure the correct  result,  call
  // SetLocalTime a second time, now that  the  first  call  has  updated  the
  // daylight saving time setting.
  //
  BOOL result = (a_cIsUTC) ? SetSystemTime(&system_time) : (SetLocalTime(&system_time) && SetLocalTime(&system_time));
  if (result == FALSE)
  {
    WARNING(STR("Cannot set system time in %x form (%u years, %u months, %u days, %u hours, %u minutes, %u seconds, %u milliseconds).") COMMA ((a_cIsUTC ? STR("UTC") : STR("local time"))) COMMA a_crDateTime.getDate().getClearYears() COMMA a_crDateTime.getDate().getClearMonths() COMMA a_crDateTime.getDate().getClearDays() COMMA a_crDateTime.getTime().getClearHours() COMMA a_crDateTime.getTime().getClearMinutes() COMMA a_crDateTime.getTime().getClearSeconds() COMMA a_crDateTime.getTime().getClearMilliseconds());
    return false;
  }

  // Reset start process time stamp.
  CSystemBase::ms_ProcessTimeStamp = CSystemBase::getSystemTimeStamp();

  return true;
}