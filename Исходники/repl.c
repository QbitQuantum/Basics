VOID
ReplicationManager (
    IN PVOID ThreadParameter
    )

/*++

Routine Description:


Arguments: 

    ThreadParameter - Not used.


Return Value:

    This thread never exits.

--*/

{
   BOOL DoReplication = FALSE;
   NTSTATUS Status;
   LLS_REPL_HANDLE ReplHandle = NULL;
   LLS_HANDLE LlsHandle = NULL;
   PLLS_CONNECT_INFO_0 pConnectInfo;
   PREPL_REQUEST pReplInfo;
   TCHAR ReplicateTo[MAX_COMPUTERNAME_LENGTH + 3];
   DWORD LastReplicated;
   LPTSTR pReplicateTo = ReplicateTo;
   TCHAR LastFailedConnectionDownlevelReplicateTo[MAX_COMPUTERNAME_LENGTH + 3] = TEXT("");

#if DBG
   if (TraceFlags & (TRACE_FUNCTION_TRACE | TRACE_REPLICATION))
      dprintf(TEXT("LLS TRACE: ReplicationManager\n"));
#endif

   //
   // Loop forever waiting to be given the opportunity to serve the
   // greater good.
   //
   for ( ; ; ) {
      //
      // Wait to be notified that there is work to be done
      //
      Status = NtWaitForSingleObject( ReplicationEvent, TRUE, NULL );

      //
      // So they said, go replicate my son...  Yeah, but first we must ask
      // the master for permission.
      //

      //
      // Construct our repl record
      //
      pReplInfo = MIDL_user_allocate(sizeof(REPL_REQUEST));
      ASSERT(pReplInfo != NULL);
      if (pReplInfo != NULL) {
         RtlEnterCriticalSection(&ConfigInfoLock);
         lstrcpy(ReplicateTo, ConfigInfo.ReplicateTo);

         pReplInfo->EnterpriseServerDate = 0;
         lstrcpy(pReplInfo->EnterpriseServer, ConfigInfo.EnterpriseServer);
         pReplInfo->EnterpriseServerDate = ConfigInfo.EnterpriseServerDate;

         pReplInfo->LastReplicated = ConfigInfo.LastReplicatedSeconds;
         pReplInfo->CurrentTime = LastUsedTime;
         pReplInfo->NumberServices = 0;
         pReplInfo->NumberUsers = 0;

         pReplInfo->ReplSize = MAX_REPL_SIZE;

         pReplInfo->Backoff = 0;
         RtlLeaveCriticalSection(&ConfigInfoLock);

#if DBG
         if (TraceFlags & TRACE_REPLICATION)
            dprintf(TEXT("LLS Starting Replication to: %s @ %s\n"), ReplicateTo, TimeToString(pReplInfo->CurrentTime));
#endif

         Status = (*pLlsReplConnect) ( ReplicateTo, &ReplHandle, 0, (LPBYTE *) &pConnectInfo );

         if ( STATUS_SUCCESS != Status )
         {
#if DBG
            dprintf(TEXT("LLS Error: LlsReplConnect failed: 0x%lX\n"), Status);
#endif
            ReplHandle = NULL;
         }
         else
         {
            Status = (*pLlsConnectW)( ReplicateTo, &LlsHandle );

            if ( STATUS_SUCCESS != Status )
            {
#if DBG
               dprintf(TEXT("LLS Error: LlsConnectW failed: 0x%lX\n"), Status);
#endif
               LlsHandle = NULL;
            }
         }

         if (Status != STATUS_SUCCESS)
         {
            DWORD          dwWinError;
            DWORD          dwBuildNumber;

            dwWinError = WinNtBuildNumberGet( ReplicateTo, &dwBuildNumber );

            if ( ( ERROR_SUCCESS == dwWinError ) && ( dwBuildNumber < 1057L ) )
            {
               // the ReplicateTo machine does not support the license service
               if ( lstrcmpi( ReplicateTo, LastFailedConnectionDownlevelReplicateTo ) )
               {
                  lstrcpy( LastFailedConnectionDownlevelReplicateTo, ReplicateTo );

                  LogEvent( LLS_EVENT_REPL_DOWNLEVEL_TARGET, 1, &pReplicateTo, Status );
               }
            }
            else
            {
               // the ReplicateTo machine should be running the license service
               *LastFailedConnectionDownlevelReplicateTo = TEXT( '\0' );

               LogEvent( LLS_EVENT_REPL_NO_CONNECTION, 1, &pReplicateTo, Status );
            }
         }
         else
         {
            *LastFailedConnectionDownlevelReplicateTo = TEXT( '\0' );

            Status = (*pLlsReplicationRequestW) ( ReplHandle, REPL_VERSION, pReplInfo );

            if (Status != STATUS_SUCCESS)
            {
               LogEvent( LLS_EVENT_REPL_REQUEST_FAILED, 1, &pReplicateTo, Status );
            }
            else
            {
               RtlEnterCriticalSection(&ConfigInfoLock);
               lstrcpy(ConfigInfo.EnterpriseServer, pReplInfo->EnterpriseServer);
               ConfigInfo.EnterpriseServerDate = pReplInfo->EnterpriseServerDate;
               ConfigInfo.IsReplicating = TRUE;
               LastReplicated = pReplInfo->LastReplicated;
               RtlLeaveCriticalSection(&ConfigInfoLock);

               //
               //  And lo, thou may proceed...
               //
               if (pReplInfo->Backoff == 0)
               {
                  if ( ConfigInfo.LogLevel )
                  {
                     LogEvent( LLS_EVENT_REPL_START, 1, &pReplicateTo, ERROR_SUCCESS );
                  }

                  Status = ReplicationDo( LlsHandle, ReplHandle, LastReplicated );

                  if ( STATUS_SUCCESS != Status )
                  {
                     LogEvent( LLS_EVENT_REPL_FAILED, 1, &pReplicateTo, Status );
                  }
                  else if ( ConfigInfo.LogLevel )
                  {
                     LogEvent( LLS_EVENT_REPL_END, 1, &pReplicateTo, ERROR_SUCCESS );
                  }

                  RtlEnterCriticalSection(&ConfigInfoLock);

                  //
                  // Need to update when next we should replicate
                  //
                  ConfigInfo.LastReplicatedSeconds = DateSystemGet();
                  GetLocalTime(&ConfigInfo.LastReplicated);
                  ReplicationTimeSet();
               }
               else
               {
                  LogEvent( LLS_EVENT_REPL_BACKOFF, 1, &pReplicateTo, ERROR_SUCCESS );
                  RtlEnterCriticalSection(&ConfigInfoLock);
               }

               ConfigInfo.IsReplicating = FALSE;
               RtlLeaveCriticalSection(&ConfigInfoLock);
            }
         }

         //
         // Disconnect from Master Server
         //
         if ( NULL != LlsHandle )
         {
            (*pLlsClose)( LlsHandle );
            LlsHandle = NULL;
         }

         if ( NULL != ReplHandle )
         {
            Status = (*pLlsReplClose) ( &ReplHandle );
            try
            {
               RpcSmDestroyClientContext( &ReplHandle );
            }
            except (TRUE)
            {
               Status = I_RpcMapWin32Status(RpcExceptionCode());
#if DBG
               dprintf(TEXT("ERROR LLSSRV.EXE (Repl): RPC Exception: 0x%lX\n"), Status);
#endif
            }

            ReplHandle = NULL;
         }

         MIDL_user_free( pReplInfo );
      }