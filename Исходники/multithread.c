INT8
StartMultiThreadBuild (
  BUILD_ITEM  **BuildList,
  UINT32      ThreadNumber,
  INT8        *BuildDir
  )
/*++

Routine Description:
  
  Start multi-thread build for a specified build list

Arguments:
  
  BuildList     - build list for multi-thread build
  ThreadNumber  - thread number for multi-thread build
  BuildDir      - build dir

Returns:

  0             - Successfully finished the multi-thread build
  other value   - Build failure

--*/
{
  UINT32        Index;
  UINT32        Count;
  BUILD_ITEM    *PreviousBuildItem;
  BUILD_ITEM    *CurrentBuildItem;
  BUILD_ITEM    *NextBuildItem;
  HANDLE        *ThreadHandle;
  INT8          Cmd[MAX_PATH];
  
  mError        = 0;
  mDone         = 0;
  mThreadNumber = ThreadNumber;
  mBuildDir     = BuildDir;
  mPendingList  = *BuildList;
  *BuildList    = NULL;
  mWaitingList  = NULL;
  mBuildingList = NULL;
  mDoneList     = NULL;
  
  //
  // Do nothing when mPendingList is empty
  //
  if (mPendingList == NULL) {
    return 0;
  }
  
  //
  // Get build item count of mPendingList
  //
  Count = 0;
  CurrentBuildItem = mPendingList;
  while (CurrentBuildItem != NULL) {
    Count++;
    CurrentBuildItem = CurrentBuildItem->Next;
  }
  
  //
  // The semaphore is also used to wake up child threads for exit,
  // so need to make sure "maximum count" >= "thread number".
  //
  if (Count < ThreadNumber) {
    Count = ThreadNumber;
  }
  
  //
  // Init mSemaphoreHandle
  //
  mSemaphoreHandle = CreateSemaphore (
                       NULL,       // default security attributes
                       0,          // initial count
                       Count,      // maximum count
                       NULL        // unnamed semaphore
                       );
  if (mSemaphoreHandle == NULL) {
    Error (NULL, 0, 0, NULL, "failed to create semaphore");
    RestoreBuildList (BuildList);
    return 1;
  }  

  //
  // Init mEventHandle
  //
  mEventHandle = CreateEvent( 
                   NULL,     // default security attributes
                   FALSE,    // auto-reset event
                   TRUE,     // initial state is signaled
                   NULL      // object not named
                   ); 
  if (mEventHandle == NULL) { 
    Error (NULL, 0, 0, NULL, "failed to create event");
    CloseHandle (mSemaphoreHandle);
    RestoreBuildList (BuildList);
    return 1;
  }
  
  //
  // Init mCriticalSection
  //
  InitializeCriticalSection (&mCriticalSection);
  
  //
  // Create build item log dir
  //
  sprintf (mLogDir, "%s\\Log", mBuildDir);
  _mkdir (mLogDir);
  
  //
  // Create child threads for muti-thread build
  //
  ThreadHandle = malloc (ThreadNumber * sizeof (HANDLE));
  if (ThreadHandle == NULL) {
    Error (NULL, 0, 0, NULL, "failed to allocate memory");
    CloseHandle (mSemaphoreHandle);
    CloseHandle (mEventHandle);
    RestoreBuildList (BuildList);
    return 1;
  }
  for (Index = 0; Index < ThreadNumber; Index++) {
    ThreadHandle[Index] = CreateThread (
                            NULL,           // default security attributes
                            0,              // use default stack size
                            ThreadProc,     // thread function
                            (LPVOID)Index,  // argument to thread function: use Index as thread id
                            0,              // use default creation flags
                            NULL            // thread identifier not needed
                            );
    if (ThreadHandle[Index] == NULL) {
      Error (NULL, 0, 0, NULL, "failed to create Thread_%d", Index);
      mError       = 1;
      ThreadNumber = Index;
      //
      // Make sure to wake up every child thread for exit
      //
      ReleaseSemaphore (mSemaphoreHandle, ThreadNumber, NULL);
      break;
    }
  }
  
  //
  // Loop until error occurred or no more build items pending for build
  //
  for (;;) {
    WaitForSingleObject (mEventHandle, INFINITE);
    if (mError) {
      break;
    }
    Count = 0;
    
    EnterCriticalSection (&mCriticalSection);
    PreviousBuildItem = NULL;
    CurrentBuildItem  = mPendingList;
    while (CurrentBuildItem != NULL) {
      NextBuildItem = CurrentBuildItem->Next;
      if (CheckDependency (CurrentBuildItem->DependencyList)) {
        //
        // Move the current build item from mPendingList
        //
        if (PreviousBuildItem != NULL) {
          PreviousBuildItem->Next = NextBuildItem;
        } else {
          mPendingList = NextBuildItem;
        }
        //
        // Add the current build item to the head of mWaitingList
        //
        CurrentBuildItem->Next = mWaitingList;
        mWaitingList = CurrentBuildItem;
        Count++;
      } else {
        PreviousBuildItem = CurrentBuildItem;
      }
      CurrentBuildItem  = NextBuildItem;
    }
    LeaveCriticalSection (&mCriticalSection);
    
    ReleaseSemaphore (mSemaphoreHandle, Count, NULL);
    if (mPendingList == NULL) {
      break;
    }
  }

  //
  // Wait until all threads have terminated
  //
  WaitForMultipleObjects (ThreadNumber, ThreadHandle, TRUE, INFINITE);
  
  if (mError && (mBuildingList != NULL)) {
    //
    // Dump build failure log of the first build item which doesn't finish the build
    //
    printf ("\tnmake -nologo -f %s all\n", mBuildingList->Makefile);
    sprintf (Cmd, "type %s\\%s_%s_%d.txt 2>NUL", mLogDir, mBuildingList->BaseName,
             mBuildingList->Processor, mBuildingList->Index);
    _flushall ();
    if (system (Cmd)) {
      Error (NULL, 0, 0, NULL, "failed to run \"%s\"", Cmd);
    }
  }

  DeleteCriticalSection (&mCriticalSection);
  for (Index = 0; Index < ThreadNumber; Index++) {
    CloseHandle (ThreadHandle[Index]);
  }
  free (ThreadHandle);
  CloseHandle (mSemaphoreHandle);
  CloseHandle (mEventHandle);
  RestoreBuildList (BuildList);

  return mError;
}