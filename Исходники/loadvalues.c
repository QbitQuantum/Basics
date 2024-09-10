int 
loadvalue_update_cpuusage(t_loadvalues *loadvalue, t_pdhquery *query,
                          t_pdhcounterset *counter_cpuusage)
{
   static BOOL initialized = FALSE;
   int ret = 0;
   DWORD local_ret;

   DENTER("loadvalue_update_cpuusage");

   /* Do query counter initialisation only once */ 
   if (!initialized) { 
      local_ret = pdhquery_initialize(query);
      if (local_ret == 0) {
         local_ret = pdhcounterset_initialize(counter_cpuusage,
                                              "Processor",
                                              "_Total",
                                              "% Processor Time");
         if (local_ret == 0) {
            local_ret = pdhquery_add_counterset(query, counter_cpuusage);
            if (local_ret != 0) {
               // error handling
               ret = 3;
            }
         } else {
            // error handling
            ret = 2;
         }
      } else {
         // error handling
         ret = 1;
      }
      if (ret != 0) {
         return ret;
      }
      initialized = TRUE;
   }

   /* We are here - no error occured during initialisation */
   local_ret = pdhquery_update(query);
   if (local_ret == 0) {
      PDH_FMT_COUNTERVALUE cpu_usage;
   
      local_ret = PdhGetFormattedCounterValue(
                                          counter_cpuusage->counter_handles[0], 
                                          PDH_FMT_LONG, NULL, &cpu_usage);
      // error handling
      local_ret = WaitForSingleObject(loadvalue_mutex, INFINITE);
      if (local_ret == WAIT_OBJECT_0) {
         loadvalue->cpu = cpu_usage.longValue;
      }
      ReleaseMutex(loadvalue_mutex);
   } else {
      // error handling
      ret = 10;
   }
    
   DEXIT; 
   return ret;
}