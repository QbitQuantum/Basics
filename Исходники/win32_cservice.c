//
//  FUNCTION: CmdRemoveService()
//
//  PURPOSE: Stops and removes the service
//
//  PARAMETERS:
//    none
//
//  RETURN VALUE:
//    0 if success
//
//  COMMENTS:
//
int CmdRemoveService()
{
   SC_HANDLE   schService;
   SC_HANDLE   schSCManager;

   int ret = 0;

   schSCManager = OpenSCManager(
                               NULL,                   // machine (NULL == local)
                               NULL,                   // database (NULL == default)
                               SC_MANAGER_CONNECT   // access required
                               );
   if ( schSCManager )
   {
      schService = OpenService(schSCManager, TEXT(SZSERVICENAME), DELETE | SERVICE_STOP | SERVICE_QUERY_STATUS);

      if (schService)
      {
         // try to stop the service
         if ( ControlService( schService, SERVICE_CONTROL_STOP, &ssStatus ) )
         {
            _tprintf(TEXT("Stopping %s."), TEXT(SZSERVICEDISPLAYNAME));
            Sleep( 1000 );

            while ( QueryServiceStatus( schService, &ssStatus ) )
            {
               if ( ssStatus.dwCurrentState == SERVICE_STOP_PENDING )
               {
                  _tprintf(TEXT("."));
                  Sleep( 1000 );
               }
               else
                  break;
            }

            if ( ssStatus.dwCurrentState == SERVICE_STOPPED )
               _tprintf(TEXT("\n%s stopped.\n"), TEXT(SZSERVICEDISPLAYNAME) );
            else
         {
               _tprintf(TEXT("\n%s failed to stop.\n"), TEXT(SZSERVICEDISPLAYNAME) );
      ret = 1;
         }

         }

         // now remove the service
         if ( DeleteService(schService) )
            _tprintf(TEXT("%s removed.\n"), TEXT(SZSERVICEDISPLAYNAME) );
         else
      {
            _tprintf(TEXT("DeleteService failed - %s\n"), GetLastErrorText(szErr,256));
        ret = 1;
      }


         CloseServiceHandle(schService);
      }
      else
   {
         _tprintf(TEXT("OpenService failed - %s\n"), GetLastErrorText(szErr,256));
     ret = 1;
   }

      CloseServiceHandle(schSCManager);
   }
   else
     {
      _tprintf(TEXT("OpenSCManager failed - %s\n"), GetLastErrorText(szErr,256));
       ret = 1;
     }
   return ret;
}