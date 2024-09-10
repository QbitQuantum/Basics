void KSim::Sysinfo::clockUptimeUpdate()
{
  TQString time;
  static bool updateDate = true;

  if (m_timeLabel) {
    TQTime now = TQTime::currentTime();
    time = TDEGlobal::locale()->formatTime(now, true);
    if ( now == TQTime(0, 0) )
      updateDate = true;

    m_timeLabel->setText(time);
  }

  // only update the date when necessary
  if (m_dateLabel) {
    if (updateDate) {
      m_dateLabel->setText(TDEGlobal::locale()->formatDate(TQDate::currentDate()));
      updateDate = false;
    }
  }
  else {
    updateDate = true;
  }

  if (m_uptimeLabel) {
    TQString uptime = m_config->uptimeFormat();
    ++m_totalUptime;
    long uptimeDays, uptimeHours, uptimeMins, uptimeSecs;

    uptimeHours = m_totalUptime / 3600;
    uptimeDays = uptimeHours / 24;
    uptimeMins = (m_totalUptime - uptimeHours * 3600) / 60;
    uptimeSecs = m_totalUptime % 60;

    TQString days;
    TQString hours;
    TQString minutes;
    TQString seconds;

    // found days so we have to modify hours
    if (uptime.find(TQRegExp("%d" ), 0) >= 0)
      uptimeHours -= (uptimeDays * 24);

    days.sprintf("%02li", uptimeDays);
    hours.sprintf("%02li", uptimeHours);
    minutes.sprintf("%02li", uptimeMins);
    seconds.sprintf("%02li", uptimeSecs);

    uptime.replace(TQRegExp("%d"), days);
    uptime.replace(TQRegExp("%h"), hours);
    uptime.replace(TQRegExp("%m"), minutes);
    uptime.replace(TQRegExp("%s"), seconds);
    m_uptimeLabel->setText(uptime);
  }
}