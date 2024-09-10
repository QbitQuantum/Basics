bool Nibbler::getDate (const std::string& format, time_t& t)
{
  auto i = _cursor;

  int month  = -1;   // So we can check later.
  int day    = -1;
  int year   = -1;
  int hour   = -1;
  int minute = -1;
  int second = -1;

  // For parsing, unused.
  int wday    = -1;
  int week    = -1;

  for (unsigned int f = 0; f < format.length (); ++f)
  {
    switch (format[f])
    {
    case 'm':
    case 'M':
      if (! parseDigits(i, month, 2, format[f] == 'M'))
        return false;
      break;

    case 'd':
    case 'D':
      if (! parseDigits(i, day, 2, format[f] == 'D'))
        return false;
      break;

    case 'y':
    case 'Y':
      if (! parseDigits(i, year, format[f] == 'y' ? 2 : 4))
        return false;
      if (format[f] == 'y')
          year += 2000;
      break;

    case 'h':
    case 'H':
      if (! parseDigits(i, hour, 2, format[f] == 'H'))
        return false;
      break;

    case 'n':
    case 'N':
      if (! parseDigits(i, minute, 2, format[f] == 'N'))
        return false;
      break;

    case 's':
    case 'S':
      if (! parseDigits(i, second, 2, format[f] == 'S'))
        return false;
      break;

    // Merely parse, not extract.
    case 'v':
    case 'V':
      if (! parseDigits(i, week, 2, format[f] == 'V'))
        return false;
      break;

    // Merely parse, not extract.
    case 'a':
    case 'A':
      if (i + 3 <= _length          &&
          ! Lexer::isDigit ((*_input)[i + 0]) &&
          ! Lexer::isDigit ((*_input)[i + 1]) &&
          ! Lexer::isDigit ((*_input)[i + 2]))
      {
        wday = ISO8601d::dayOfWeek (_input->substr (i, 3).c_str ());
        i += (format[f] == 'a') ? 3 : ISO8601d::dayName (wday).size ();
      }
      else
        return false;
      break;

    case 'b':
    case 'B':
      if (i + 3 <= _length          &&
          ! Lexer::isDigit ((*_input)[i + 0]) &&
          ! Lexer::isDigit ((*_input)[i + 1]) &&
          ! Lexer::isDigit ((*_input)[i + 2]))
      {
        if (month != -1)
          return false;
        month = ISO8601d::monthOfYear (_input->substr (i, 3).c_str());
        i += (format[f] == 'b') ? 3 : ISO8601d::monthName (month).size ();
      }
      else
        return false;
      break;

    default:
      if (i + 1 <= _length &&
          (*_input)[i] == format[f])
        ++i;
      else
        return false;
      break;
    }
  }

  // By default, the most global date variables that are undefined are put to
  // the current date (for instance, the year to the current year for formats
  // that lack Y/y). If even 'second' is undefined, then the date is parsed as
  // now.
  if (year == -1)
  {
    ISO8601d now;
    year = now.year ();
    if (month == -1)
    {
      month = now.month ();
      if (day == -1)
      {
        day = now.day ();
        if (hour == -1)
        {
          hour = now.hour ();
          if (minute == -1)
          {
            minute = now.minute ();
            if (second == -1)
              second = now.second ();
          }
        }
      }
    }
  }

  // Put all remaining undefined date variables to their default values (0 or
  // 1).
  month  = (month  == -1) ? 1 : month;
  day    = (day    == -1) ? 1 : day;
  hour   = (hour   == -1) ? 0 : hour;
  minute = (minute == -1) ? 0 : minute;
  second = (second == -1) ? 0 : second;

  // Check that values are correct
  if (! ISO8601d::valid (month, day, year, hour, minute, second))
    return false;

  // Convert to epoch.
  struct tm tms {};
  tms.tm_isdst = -1;   // Requests that mktime determine summer time effect.
  tms.tm_mon   = month - 1;
  tms.tm_mday  = day;
  tms.tm_year  = year - 1900;
  tms.tm_hour  = hour;
  tms.tm_min   = minute;
  tms.tm_sec   = second;

  t = mktime (&tms);
  _cursor = i;
  return true;
}