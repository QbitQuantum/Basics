void printTime()
{
  ros::Duration d = current_time - start_time;

  if (paused)
    printf("\r [PAUSED]   Log Time: %13.6f   Duration: %.6f            \r", current_time.toSec(), d.toSec());
  else
    printf("\r [RUNNING]  Log Time: %13.6f   Duration: %.6f            \r", current_time.toSec(), d.toSec());
  fflush(stdout);
}