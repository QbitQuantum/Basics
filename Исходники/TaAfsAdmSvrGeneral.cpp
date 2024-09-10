DWORD WINAPI AfsAdmSvr_AutoShutdownThread (LPVOID lp)
{
   for (;;)
      {
      AfsAdmSvr_Enter();

      BOOL fShutdown = l.fAutoShutdown;

      // If there are any clients connected, forcably disconnect any
      // that haven't pinged us for too long
      //
      for (size_t iClient = 0; iClient < l.cClientsAllocated; ++iClient)
         {
         if (!l.aClients[ iClient ])
            continue;
         if (l.aClients[ iClient ]->timeLastPing + cminREQ_CLIENT_PING <= AfsAdmSvr_GetCurrentTime())
            {
            Print (dlCONNECTION, "Client 0x%08lX idle for too long; detaching", l.aClients[ iClient ]);
            AfsAdmSvr_DetachClient ((UINT_PTR)l.aClients[ iClient ]);
            }
         }

      // If any operations are in progress, we can't shutdown.
      //
      if (l.cOperations)
         fShutdown = FALSE;

      // If any clients are still connected, we can't shutdown.
      //
      if (l.cClients)
         fShutdown = FALSE;

      // If we haven't been idle long enough, we can't shutdown
      //
      if (!l.timeLastIdleStart)
         fShutdown = FALSE;
      else if (l.timeLastIdleStart + cminAUTO_SHUTDOWN > AfsAdmSvr_GetCurrentTime())
         fShutdown = FALSE;

      // That's it; can we stop now?
      //
      if (fShutdown)
         {
         Print ("Idle for too long; shutting down.");
         RpcMgmtStopServerListening (NULL);
         AfsAdmSvr_StopCallbackManagers();
         }

      AfsAdmSvr_Leave();

      if (fShutdown)
         break;

      Sleep (cminAUTO_SHUTDOWN_SLEEP * 60L * 1000L);
      }

   return 0;
}