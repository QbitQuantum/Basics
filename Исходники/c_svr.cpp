BOOL SERVER::CanTalkToServer (ULONG *pStatus)
{
   // Ensure the server exists in the cell at all--
   // this call just updates the server's IP addresses
   // etc (information it gets from the database servers)
   // and doesn't require talking to the server itself.
   //
   if (!RefreshStatus (FALSE, pStatus))
      return FALSE;

   // Find a new refsec array element to use...
   //
   AfsClass_InitRefreshSections();
   EnterCriticalSection (pcsRefSec);

   int idSection;
   for (idSection = 0; idSection < (int)cRefSec; ++idSection)
      {
      if (!aRefSec[ idSection ].fInUse)
         break;
      }
   if (idSection == (int)cRefSec)
      {
      if (!REALLOC (aRefSec, cRefSec, 1+idSection, 4))
         {
         if (pStatus)
            *pStatus = GetLastError();
         LeaveCriticalSection (pcsRefSec);
         return FALSE;
         }
      }
   aRefSec[ idSection ].fInUse = TRUE;
   aRefSec[ idSection ].fCanceled = FALSE;
   aRefSec[ idSection ].lpServer = this;
   aRefSec[ idSection ].hCell = NULL;

   LPCELL lpCell;
   if ((lpCell = OpenCell()) != NULL)
      {
      aRefSec[ idSection ].hCell = lpCell->GetCellObject();
      lpCell->Close();
      }

   LeaveCriticalSection (pcsRefSec);

   // Until we find out differently, assume that we won't be
   // able to query VOS or BOS on this server.
   //
   m_fCanGetAggregates = FALSE;
   m_fCanGetServices = FALSE;
   m_lastStatus = 0;

   // Fork a separate thread, on which to quickly try to talk
   // to the server.
   //
   DWORD dwThreadID;
   HANDLE hThread;
   if ((hThread = CreateThread (NULL, 0, (LPTHREAD_START_ROUTINE)CanTalkToServer_ThreadProc, IntToPtr(idSection), 0, &dwThreadID)) == NULL)
      {
      EnterCriticalSection (pcsRefSec);
      aRefSec[ idSection ].fInUse = FALSE;
      LeaveCriticalSection (pcsRefSec);
      if (pStatus)
         *pStatus = GetLastError();
      return FALSE;
      }
   SetThreadPriority (hThread, THREAD_PRIORITY_BELOW_NORMAL);

   // Wait for that thread to terminate, or for our
   // newly-allocated RefSec entry to be marked Canceled.
   //
   DWORD dw;
   for (dw = STILL_ACTIVE; dw == STILL_ACTIVE; )
      {
      EnterCriticalSection (pcsRefSec);

      GetExitCodeThread (hThread, &dw);
      if (dw == STILL_ACTIVE)
         {
         if ( (aRefSec[ idSection ].fInUse) &&
              (aRefSec[ idSection ].lpServer == this) &&
              (aRefSec[ idSection ].fCanceled) )
            {
            if (m_lastStatus == 0)
               m_lastStatus = ERROR_CANCELLED;
            dw = 0;
            }
         }

      LeaveCriticalSection (pcsRefSec);

      if (dw == STILL_ACTIVE)
         Sleep(100);	// wait another brief instant
      }

   // dw == 0 : user canceled operation (thread is still running!)
   // dw == 1 : thread completed successfully, and set fCanTalkTo* flags.
   //
   // Note that the thread will clear aRefSec[idSection].fInUse when it
   // terminates (so, if dw!=-1, it has already done so).
   //
   if (pStatus)
      *pStatus = m_lastStatus;
   return (dw == 0) ? FALSE : TRUE;
}