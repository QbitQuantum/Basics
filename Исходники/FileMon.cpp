FileMon::~FileMon() {
#ifdef WIN32
  for(auto i : mWatches) {
    WatchStruct* pWatch=i.second;

    DWORD dwWaitResult = WaitForSingleObject(ghMutex,INFINITE);

    while(true) {
      if(dwWaitResult==WAIT_OBJECT_0) {
        pWatch->mStopNow = TRUE;

        if(!ReleaseMutex(ghMutex)) {
          std::cout << "FileMon : Release mutex err.\n";
        }

        break;
      } else if(dwWaitResult==WAIT_ABANDONED) {
        break;
      }
    }

    CancelIo(pWatch->mDirHandle);

    ReadDirectoryChangesW(
      pWatch->mDirHandle,pWatch->mBuffer,sizeof(pWatch->mBuffer),FALSE,
      pWatch->mNotifyFilter,NULL,&pWatch->mOverlapped,0);

    if(!HasOverlappedIoCompleted(&pWatch->mOverlapped)) {
      SleepEx(5,TRUE);
    }

    CloseHandle(pWatch->mOverlapped.hEvent);
    CloseHandle(pWatch->mDirHandle);
    HeapFree(GetProcessHeap(),0,pWatch);
  }

  CloseHandle(ghMutex);
#endif

#ifdef LINUX
  if(notify) {
    for(auto i : watchMap) {
      inotify_rm_watch(notify,i.first); //unnecessary because of close below?
    }
  }

  if(notify) {
    close(notify);
  }
#endif
}