void baseTimer::timerThread()
{
   GJV_thread::setThreadName( "hires timer" );

   currTick = 0;

   basetick = GetTickCount();


   TIMECAPS tc;

   if ( timeGetDevCaps( &tc, sizeof( TIMECAPS ) ) != TIMERR_NOERROR )
   {
      // Error; application can't continue.
      MessageBox( 0, "Timer", "GetDevCaps", MB_ICONERROR | MB_OK );
   }

   UINT wTimerRes = std::min( std::max( tc.wPeriodMin, TARGET_RESOLUTION ), tc.wPeriodMax );
   timeBeginPeriod( wTimerRes );
   MMRESULT timeEventId = timeSetEvent( TIMER_INTERVAL, 0, intrTick, 0, TIME_PERIODIC );

   hTimerThreadCloseEvent = CreateEvent(
                               NULL,     // no security attributes
                               TRUE,     // manual reset event
                               FALSE,      // not-signalled
                               NULL );  // no name

   while ( 1 )
   {
      // Wait for request to close or for a read thread to terminate.
      DWORD dwWait = WaitForSingleObject( hTimerThreadCloseEvent, 1000 );

      if ( dwWait == WAIT_TIMEOUT )
         continue;

      CloseHandle( hTimerThreadCloseEvent );
      if ( timeEventId )
      {
         timeKillEvent( timeEventId );
         timeEventId = 0;
      }

      if ( wTimerRes )
      {
         timeEndPeriod( wTimerRes );
         wTimerRes = 0;
      }
      return ;
   }

}