KLF_EXPORT KLFSysInfo::BatteryInfo _klf_win_battery_info()
{
  KLFSysInfo::BatteryInfo info;

  SYSTEM_POWER_STATUS batterystatus;

  if (GetSystemPowerStatus(&batterystatus) == 0) {
    klfWarning("Could not get battery status.") ;
    info.islaptop = false;
    info.onbatterypower = false;
    return info;
  }

  info.islaptop = (batterystatus.ACLineStatus != 255);
  info.onbatterypower = false;
  if (batterystatus.ACLineStatus == 0)
    info.onbatterypower = true;

  return info;
}