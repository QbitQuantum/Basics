// TODO: Device shouldn't be responsible for doing this
// TODO: Connect setting provider's signal to a battery provider slot that will load settings
void Wallaby::Device::settingsChanged()
{
  const int type = m_settingsProvider->value("battery_type", 0).toInt();
  const float thresh = m_settingsProvider->value("battery_warning_thresh", 0.1f).toFloat();
  const bool enabled = m_settingsProvider->value("battery_warning_enabled", true).toBool();
  
  Wallaby::BatteryLevelProvider *wblProvider = (Wallaby::BatteryLevelProvider *)m_batteryLevelProvider;
  wblProvider->setBatteryType(type);
  wblProvider->setWarningThresh(thresh);
  
  if(m_timerId > 0 && !enabled)
  {
    killTimer(m_timerId);
    m_timerId = 0;
  }
  else if(m_timerId <= 0 && enabled)
    m_timerId = startTimer(1000);
}