int
apm_read(struct olsr_apm_info *ApmInfo)
{
#if !defined WINCE
  SYSTEM_POWER_STATUS PowerStat;

  memset(ApmInfo, 0, sizeof(struct olsr_apm_info));

  if (!GetSystemPowerStatus(&PowerStat))
    return 0;

  ApmInfo->ac_line_status = (PowerStat.ACLineStatus == 1) ? OLSR_AC_POWERED : OLSR_BATTERY_POWERED;

  ApmInfo->battery_percentage = (PowerStat.BatteryLifePercent <= 100) ? PowerStat.BatteryLifePercent : 0;

  return 1;
#else /* !defined WINCE */
  return 0;
#endif /* !defined WINCE */
}