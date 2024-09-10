/*****************************************************************************
Name:         Run_RTC_Scheduler  
Parameters:   none                  
Returns:      none  
Description:  Starts Round Robin Scheduler.  Should be call in Main program after
completing initialization.  Only enabled tasks will be scheduled and run. 
*****************************************************************************/
void Run_RTC_Scheduler(void)
{
  int i;
  GBL_run_scheduler = 1;
  /* Loop forever */
  while (1) {
    /* Check each task */
    for (i=0 ; i<MAX_TASKS ; i++) {
      
      /* If this is a scheduled task */
      if (GBL_task_list[i].task != NULL) { /* valid task */
				if (GBL_task_list[i].enabled == 1) { /* enabled */
				  if (GBL_task_list[i].ready == 1) {  /* ready to run */
#if RTC_MONITOR_ACTIVITY
//						RTC_ACTIVE_OUTPUT = 0; // Indicate task is active
#endif // RTC_MONITOR_ACTIVITY	

				    /* Run the task */
				    GBL_task_list[i].task();

#if RTC_MONITOR_ACTIVITY
//						RTC_ACTIVE_OUTPUT = 1; // Indicate task is inactive
#endif // RTC_MONITOR_ACTIVITY	

				    /* Reset the task ready flag */
				    GBL_task_list[i].ready = 0;
				    break;
	  			}
        } 
      } 
    }
		// reached end of loop, so start at top again
#if RTC_HALT_WHEN_IDLE
		RTC_STANDBY_OUTPUT = 0; // Sleeping
		__halt();
		RTC_STANDBY_OUTPUT = 1; // Not sleeping
#endif // RTC_HALT_WHEN_IDLE

#if RTC_STOP_WHEN_IDLE
		RTC_STANDBY_OUTPUT = 0; // Sleeping
		__stop();
		RTC_STANDBY_OUTPUT = 1; // Not sleeping
#endif // RTC_STOP_WHEN_IDLE
	
  }
}