static VOID Initialize()
{
  if (nInitialized == 0)
  {
    NktHookLib::Internals::CNktSimpleLockNonReentrant cLock(&nMutex);

    if (nInitialized == 0)
    {
      LONG nResult = -1;

      //are we running in a X64 processor?
      if (NktHookLibHelpers::GetProcessorArchitecture() == PROCESSOR_ARCHITECTURE_AMD64)
      {
        if (NktHookLib_InitializeWow64() != 0)
          nResult = 1;
      }
      _InterlockedExchange(&nInitialized, nResult);
    }
  }
  return;
}