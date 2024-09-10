char MaxExeTimeCron()
{
  LocalTime(&total_time_cron);
  if (total_time_cron < lost_time_cron)
    (total_time_cron += 86400);
  total_time_cron -= lost_time_cron;
  return(total_time_cron < MaxExeTime);
}