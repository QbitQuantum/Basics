int hb_fsProcessValue( HB_FHANDLE hProcess, HB_BOOL fWait )
{
   int iRetStatus = -1;

   HB_TRACE( HB_TR_DEBUG, ( "hb_fsProcessValue(%p, %d)", ( void * ) ( HB_PTRDIFF ) hProcess, fWait ) );

#if defined( HB_OS_WIN )
{
   HB_BOOL fError = HB_TRUE;
   DWORD dwResult;
   HANDLE hProc = ( HANDLE ) hb_fsGetOsHandle( hProcess );

   if( hProc )
   {
      hb_vmUnlock();
      dwResult = WaitForSingleObject( hProc, fWait ? INFINITE : 0 );
      if( dwResult == WAIT_OBJECT_0 )
      {
         fError = ! GetExitCodeProcess( hProc, &dwResult );
         iRetStatus = ! fError ? ( int ) dwResult : -2;
      }
      hb_fsSetIOError( ! fError, 0 );
      if( ! fError )
         CloseHandle( hProc );
      hb_vmLock();
   }
   else
      hb_fsSetError( ( HB_ERRCODE ) FS_ERROR );
}
#elif defined( HB_OS_UNIX ) || ( defined( HB_OS_OS2 ) && defined( __GNUC__ ) )
{
   int iStatus;
   pid_t pid = ( pid_t ) hProcess;

   if( pid > 0 )
   {
      hb_vmUnlock();
      iRetStatus = waitpid( pid, &iStatus, fWait ? 0 : WNOHANG );
      hb_fsSetIOError( iRetStatus >= 0, 0 );
#ifdef ERESTARTSYS
      if( iRetStatus < 0 && hb_fsOsError() != ( HB_ERRCODE ) ERESTARTSYS )
#else
      if( iRetStatus < 0 )
#endif
         iRetStatus = -2;
      else if( iRetStatus == 0 )
         iRetStatus = -1;
      else
         iRetStatus = WIFEXITED( iStatus ) ? WEXITSTATUS( iStatus ) : 0;
      hb_vmLock();
   }
   else
      hb_fsSetError( ( HB_ERRCODE ) FS_ERROR );
}
#elif defined( HB_OS_OS2 )
{
   PID pid = ( PID ) hProcess;

   if( pid > 0 )
   {
      RESULTCODES resultCodes = { 0, 0 };
      APIRET ret;

      ret = DosWaitChild( DCWA_PROCESS, fWait ? DCWW_WAIT : DCWW_NOWAIT,
                          &resultCodes, &pid, pid );
      hb_fsSetIOError( ret == NO_ERROR, 0 );
      if( ret == NO_ERROR )
         iRetStatus = resultCodes.codeResult;
      else
         iRetStatus = -2;
   }
   else
      hb_fsSetError( ( HB_ERRCODE ) FS_ERROR );
}
#elif defined( HB_OS_OS2 ) || defined( HB_OS_WIN )
{
   int iPid = ( int ) hProcess;

   HB_SYMBOL_UNUSED( fWait );

   if( iPid > 0 )
   {
      hb_vmUnlock();
#if defined( __BORLANDC__ )
      iPid = cwait( &iRetStatus, iPid, 0 );
#else
      iPid = _cwait( &iRetStatus, iPid, 0 );
#endif
      hb_fsSetIOError( iPid > 0, 0 );
      if( iPid != ( int ) hProcess )
         iRetStatus = -1;
      hb_vmLock();
   }
   else
      hb_fsSetError( ( HB_ERRCODE ) FS_ERROR );
}
#else
{
   int iTODO; /* TODO: for given platform */

   HB_SYMBOL_UNUSED( hProcess );
   HB_SYMBOL_UNUSED( fWait );
   hb_fsSetError( ( HB_ERRCODE ) FS_ERROR );
}
#endif
   return iRetStatus;
}