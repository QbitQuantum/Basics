/*!
 * \brief Supervisor task.
 *
 * \return never
 */
static portTASK_FUNCTION( vSupervisorTask, pvParameters )
{
   portTickType xDelayLength = SUPERVISOR_DEFAULT_PERIOD;
   portTickType xLastFocusTime;
#if configHEAP_INIT == 1
#if defined(__GNUC__)
   portLONG     lCheckHeapDelay = 1;
#endif
#endif
#if configCTRLPANEL_TRACE == 1
   portLONG     lPrintTrace = 3;
#endif
   portLONG     lUpdateTimeDelay = 1;
#ifdef MMILCD_ENABLE
   portLONG     lUpdateMMITimeDelay = 1;
   portCHAR DateTime[21];
   struct tm *pxDate;
   bool ms_connected_displayed = pdFALSE;
   bool enum_connected_displayed = pdFALSE;
#endif

   /* The parameters are not used. */
   ( void )pvParameters;

#if configCTRLPANEL_TRACE == 1
   /* Initialize the dump port COM2. */
   itracedump_Init();
#endif

#ifdef MMILCD_ENABLE
   // The MMI module.
   if( pdFALSE == bMMI_start() )
   {
      // vParTestSetLED( ERROR_LED_ID, pdTRUE );
      while( 1 );
   }
#endif

   // Create the SHELL mutex.
   vSemaphoreCreateBinary( xSHELLFSMutex );
   if( NULL == xSHELLFSMutex )
   { // The mutex creation failed.
      // TODO: Add msg on LCD.
      // vParTestSetLED( ERROR_LED_ID, pdTRUE );
      while( 1 );
   }
   // Start the COM1 Shell module.
   vStartCom1Shell( mainCOMSH_TASK_PRIORITY );

   // Create the CFG mutex.
   vSemaphoreCreateBinary( xCFGMutex );
   if( NULL == xCFGMutex )
   { // The mutex creation failed.
      // TODO: Add msg on LCD.
      // vParTestSetLED( ERROR_LED_ID, pdTRUE );
      while( 1 );
   }

   // Start the sensor module.
   if( false == bsensor_start() )
   {
      // TODO: Add msg on LCD.
      // vParTestSetLED( ERROR_LED_ID, pdTRUE );
      while( 1 );
   }

#if NW_INTEGRATED_IN_CONTROL_PANEL
   // Create the Web server mutex.
   vSemaphoreCreateBinary( xWEBMutex );
   if( NULL == xWEBMutex )
   { // The mutex creation failed.
      // TODO: Add msg on LCD.
      // vParTestSetLED( ERROR_LED_ID, pdTRUE );
      while( 1 );
   }
   // Start network tasks.
   vStartEthernetTaskLauncher( tskIDLE_PRIORITY + 1 );
#endif

   // Create the LOG mutex.
   vSemaphoreCreateBinary( xLOGMutex );
   if( NULL == xLOGMutex )
   { // The mutex creation failed.
      // TODO: Add msg on LCD.
      // vParTestSetLED( ERROR_LED_ID, pdTRUE );
      while( 1 );
   }
   // Start the data logger module.
   if( false == bdatalog_start( mainDATALOG_TASK_PRIORITY ) )
   {
      // TODO: Add msg on LCD.
      // vParTestSetLED( ERROR_LED_ID, pdTRUE );
      while( 1 );
   }

#ifdef USB_ENABLE
#if USB_DEVICE_FEATURE == true
   // Create the USB mutex.
   vSemaphoreCreateBinary( xUSBMutex );
   if( NULL == xUSBMutex )
   { // The mutex creation failed.
      // TODO: Add msg on LCD.
      // vParTestSetLED( ERROR_LED_ID, pdTRUE );
      while( 1 );
   }
   // Immediately take the USB mutex. i.e. when we're a Mass Storage device,
   // we'll refuse to give r/w access to the host until a user action. This user
   // action will make the Ctrl Panel device switch to maintenance mode, in which
   // the Mass Storage USB host has r/w access to the Ctrl Panel file system.
   while( pdFALSE == x_supervisor_SemaphoreTake( xUSBMutex, 0 ) );
#endif
   // Start the USB module tasks.
   if( false == b_usbsys_start() )
   {
      // TODO: Add msg on LCD.
      // vParTestSetLED( ERROR_LED_ID, pdTRUE );
      while( 1 );
   }
#endif

#ifdef MMILCD_ENABLE
   // Create the supervisor queue to deal with MMI actions
   xSUPERVISORQueue = xQueueCreate( SUPERVISOR_QUEUE_SIZE, sizeof(bool *) );
   if( 0 == xSUPERVISORQueue )
   {
      // TODO: Add msg on LCD.
      // vParTestSetLED( ERROR_LED_ID, pdTRUE );
      while( 1 );
   }

   /* Get a File System navigator for MMI actions. */
   fsaccess_take_mutex();
   sMmiNavId = fsaccess_alloc_nav_id();
   nav_select( sMmiNavId );   // Select the navigator.
   fsaccess_give_mutex();

   /* Spawn the User Action task. */
   if( pdPASS != xTaskCreate( vSupervisorUserActionTask,
                              ( const signed portCHAR * )"MMIACT",
                              SUPERVISOR_USER_ACTION_STACK_SIZE, NULL, SUPERVISOR_USER_ACTION_TASK_PRIORITY,
                              &xSupervisorUserActionHndl ) )
   {
      vTaskDelete( xSupervisorUserActionHndl );
      // TODO: Add msg on LCD.
      // vParTestSetLED( ERROR_LED_ID, pdTRUE );
      while( 1 );
   }
#endif // #ifdef MMILCD_ENABLE

   /* We need to initialise xLastFlashTime prior to the first call to vTaskDelayUntil(). */
   xLastFocusTime = xTaskGetTickCount();

#if defined(__GNUC__)
   NAKED_TRACE_COM2( "heap start @=%d, heap end @=%d", \
                     (portBASE_TYPE *)&__heap_start__, \
                     (portBASE_TYPE *)&__heap_end__ );
#endif

   /* Enable the watchdog timer. */
   // wdt_enable( SUPERVISOR_WDT_TIMEOUT );

   for(;;)
   {
      /* Delay for the flash period then check. */
      vTaskDelayUntil( &xLastFocusTime, xDelayLength );

      // wdt_clear(); // Kick the watchdog!

      /* MMI USB management. */
#ifdef MMILCD_ENABLE
#ifdef USB_ENABLE
/*** Start of Host behaviour ***/
      // first occurrence of MS connection, Host mode
      if (ms_connected == true && ms_connected_displayed == pdFALSE)
      {
        // display connected logo
        ms_connected_displayed = pdTRUE;
        vMMI_DisplayUSBState(ms_connected_displayed);
        // Display User Menu
        vMMI_SetUserMenuMode(eUserMenuUSBHost, pdTRUE);

      }
      // first occurrence of MS disconnection, end of Host mode
      if (ms_connected == false && ms_connected_displayed == pdTRUE)
      {
        // remove connected logo
        ms_connected_displayed = pdFALSE;
        vMMI_DisplayUSBState(ms_connected_displayed);
        // clear User Menu
        vMMI_SetUserMenuMode(eUserMenuIdle, pdTRUE);
      }
/*** End of Host behaviour ***/
/*** Start of Device behaviour ***/
#if USB_DEVICE_FEATURE == true
      // first occurrence of Device connection, Device mode
      if (Is_device_enumerated() && ( enum_connected_displayed == pdFALSE ) )
      {
        if( true == bIsInMaintenance )
        {
          // display connected logo
          enum_connected_displayed = pdTRUE;
          vMMI_DisplayUSBState(enum_connected_displayed);
          // Display User Menu
          vMMI_SetUserMenuMode(eUserMenuUSBDevice, pdTRUE);
        }
      }
      // first occurrence of Device disconnection, end of Device mode
      else if (!Is_device_enumerated() && enum_connected_displayed == pdTRUE)
      {
        // remove connected logo
        enum_connected_displayed = pdFALSE;
        vMMI_DisplayUSBState(enum_connected_displayed);
        // clear User Menu
        vMMI_SetUserMenuMode(eUserMenuIdle, pdTRUE);
      }
      else
      {
        // remove connected logo => this makes the USB logo blink when the Control
        // Panel is behaving as a USB key.
        enum_connected_displayed = pdFALSE;
        vMMI_DisplayUSBState(enum_connected_displayed);
      }
/*** End of Device behaviour ***/
#endif // #if USB_DEVICE_FEATURE == true
#endif // #ifdef USB_ENABLE
#endif // #ifdef MMILCD_ENABLE

      /* update time every SUPERVISOR_DELAY_TIMEUPDATE seconds. */
      if( 0 == --lUpdateTimeDelay )
      {
         /* Update the local time. */
         lUpdateTimeDelay = SUPERVISOR_DELAY_TIMEUPDATE;
         xcptime_LocalTime++;
         // v_cptime_UpdateLocalTime();
      }

#ifdef MMILCD_ENABLE
      /* Update time displayed on the LCD. */
      if( 0 == --lUpdateMMITimeDelay)
      {
         // Get the broken-down representation of the current date.
         pxDate = gmtime( &xcptime_LocalTime );

         // WARNING: pxDate->tm_year == number of years since 1900.
         // For years >= 2000, we'll display the last 2 digits only.
         if( pxDate->tm_year >= 100 )  pxDate->tm_year -= 100;
#if DISPLAY_MMI_SECOND == 1
         sprintf( DateTime, "%02d/%02d/20%02d  %02d:%02d:%02d", pxDate->tm_mon +1, pxDate->tm_mday,
                            pxDate->tm_year, pxDate->tm_hour, pxDate->tm_min, pxDate->tm_sec );
#else
         sprintf( DateTime, "%02d/%02d/20%02d     %02d:%02d", pxDate->tm_mon +1, pxDate->tm_mday,
                            pxDate->tm_year, pxDate->tm_hour, pxDate->tm_min );
#endif
         vMMI_DisplayDateAndTime(DateTime);
         lUpdateMMITimeDelay = SUPERVISOR_DELAY_MMI_TIMEUPDATE;
      }

      // Manage MMI
      vMMI_Manage();

      // Manage MMI user action
      prv_v_manage_user_action();
#endif // #ifdef MMILCD_ENABLE

#ifdef USB_ENABLE
      if( true == bOutOfMaintenance )
      {
         prv_v_leave_maintenance_mode();
      }
#endif

      /* Execute a scheduled command if expiration date is up. */
      v_cptime_ExecuteScheduledCmd();

#if configHEAP_INIT == 1
#if defined(__GNUC__)
      /* Record the malloc() heap highest consumption every SUPERVISOR_DELAY_HEAPCHECK seconds. */
      if( 0 == --lCheckHeapDelay )
      {
         lCheckHeapDelay = SUPERVISOR_DELAY_HEAPCHECK;
         prvCheckMallocHeap();
      }
#endif
#endif

#if configCTRLPANEL_TRACE == 1
      // Display traces on USART1 every SUPERVISOR_DELAY_PRINTTASKLIST seconds.
      if( 0 == --lPrintTrace )
      {
         lPrintTrace = SUPERVISOR_DELAY_PRINTTASKLIST; // Restart the delay.
         v_syscmds_display_traces();
      }
#endif

   } // for(;;)
} /*lint !e715 !e818 !e830 Function definition must be standard for task creation. */