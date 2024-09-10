int KXAsio::ASIOThread(void)
{
    // Vista optimization
    HANDLE hMmTask = NULL;
    DWORD dwMmTaskIndex = 0;

    HMODULE avrt = LoadLibrary("Avrt.dll");
    if(avrt)
    {

    enum AVRT_PRIORITY
    {
    AVRT_PRIORITY_CRITICAL=2,
    AVRT_PRIORITY_HIGH=1,
    AVRT_PRIORITY_LOW=-1,
    AVRT_PRIORITY_NORMAL=0
    };

            typedef HANDLE (WINAPI *AvSetMmThreadCharacteristics_t)(LPCTSTR TaskName,LPDWORD TaskIndex);
            typedef BOOL (WINAPI *AvSetMmThreadPriority_t)(HANDLE AvrtHandle,AVRT_PRIORITY Priority);

            AvSetMmThreadCharacteristics_t avSetMmThreadCharacteristics=(AvSetMmThreadCharacteristics_t)
               GetProcAddress(avrt,"AvSetMmThreadCharacteristicsA");

            AvSetMmThreadPriority_t avSetMmThreadPriority=(AvSetMmThreadPriority_t)
               GetProcAddress(avrt,"AvSetMmThreadPriority");

            if(avSetMmThreadCharacteristics && avSetMmThreadPriority)
            {
                 // Register this thread with MMCSS
                 hMmTask = avSetMmThreadCharacteristics("Pro Audio",&dwMmTaskIndex); // used to be "Audio"

                 // Set thread priority to HIGH via MMCSS
                 if( NULL != hMmTask )
                 {
                     if(avSetMmThreadPriority(hMmTask, AVRT_PRIORITY_CRITICAL))
                      debug("kxasio: Vista-specific thread priority set to critical\n");
                     else
                      debug("kxasio: could not set Vista-specific thread priority! [%d]\n",GetLastError());

                 } else debug("kxasio: Could not set thread characteristics [NULL]\n");
            } else debug("kxasio: Could not find appropriate entry points in avrt.dll\n");

            FreeLibrary(avrt);
    }

 MMRESULT rr=timeBeginPeriod(1);
 
 if(rr==TIMERR_NOERROR)
  debug("kxasio: time period set to 1,0 msec\n");
 else
 {
  if(rr==TIMERR_NOCANDO)
   debug("kxasio: value not supported (nocando - 1 msec) !\n");

  debug("kxasio: failed to set time period to 1msec; %x !\n",GetLastError());
 }

 // 3552 change:
 int tmp_new_timer=0;
 ikx->asio_timer(1,5000,tmp_new_timer); // input is in 10000-units, set to 0.5ms

 HANDLE timer=NULL;
 timer=CreateWaitableTimer(NULL,FALSE,NULL); // synchro timer
 if(timer==NULL)
 {
  strcpy(errorMessage,"Error creating system timer");
  debug("kxasio: error creating timer\n");
  return false;
 }
 debug("kxasio: timer created\n");

 double tm_delay=(1000.0 * (double)blockFrames / sampleRate / 8.0); // 8.0 is a constant; 8 times per buffer
 if(tm_delay<1.0) tm_delay=1.0;

 LARGE_INTEGER when;
 when.QuadPart=(__int64)(tm_delay*1000000.0);

 if(SetWaitableTimer(timer,&when,(DWORD)tm_delay,NULL,NULL,FALSE)==0)
 {
      DWORD err=GetLastError();
      char tmp[128];
      debug("kxasio: Error setting waitable timer: %x (%d)\n",err,err);
      return false;
 }

 int asio_method=ikx->get_asio_method();
 HANDLE asio_event=ikx->get_asio_event();

 do
 {
   if(ikx)
   {
     // ret=1 - switch buffers
     if(ikx->asio_wait(toggle,&done))
     {
      bufferSwitch();
     }
     else
     {
         // time has not come yet
         // asio_wait() will process KXASIO_METHOD_WAIT_IN_KERNEL itself

         if(asio_method&KXASIO_METHOD_SLEEP)
          Sleep(1);
         else
          if(asio_method&KXASIO_METHOD_THREAD)
            SwitchToThread(); // sleep
          else
           if(asio_method&KXASIO_METHOD_TIMER)
            WaitForSingleObject(timer,(DWORD)tm_delay);
          else
           if(asio_method&KXASIO_METHOD_SEND_EVENT && asio_event)
             WaitForSingleObject(asio_event,100);
           else
            Sleep(0); // KXASIO_METHOD_NOWAIT
     }
   }
   else
    break;
 }while(!done);

 if(timer)
 {
  CloseHandle(timer);
  timer=NULL;
 }

 ikx->asio_timer(0,0,tmp_new_timer); // setget=0 -> reset value

 timeEndPeriod(1);

 return 0;
}