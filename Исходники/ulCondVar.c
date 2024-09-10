static INLINE Bool
MXUserCreateInternal(MXUserCondVar *condVar)  // IN/OUT:
{
   Bool success;

   if (MXUserNativeCVSupported()) {
      ASSERT(pInitializeConditionVariable);
      (*pInitializeConditionVariable)(&condVar->x.condObject);
      success = TRUE;
   } else {
      if (InitializeCriticalSectionAndSpinCount(&condVar->x.compat.condVarLock,
                                                0x80000400) == 0) {
         success = FALSE;
      } else {
         condVar->x.compat.numWaiters = 0;
         condVar->x.compat.numForRelease = 0;

         condVar->x.compat.signalEvent = CreateEvent(NULL,  // no security
                                                     TRUE,  // manual-reset
                                                     FALSE, // non-signaled
                                                     NULL); // unnamed

         success = (condVar->x.compat.signalEvent != NULL);

         if (!success) {
            DeleteCriticalSection(&condVar->x.compat.condVarLock);
         }
      }
   }

   return success;
}