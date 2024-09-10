HANDLE CNktDvProcessMemory::GetWriteAccessHandle()
{
  if (hProc[1] == NULL)
  {
    CNktAutoFastMutex cLock(&GetLockObject());
    TNktComPtr<CNktDvProcessHandlesMgr> cPhMgr;

    if (hProc[1] == NULL && bWriteAccessChecked == FALSE)
    {
      bWriteAccessChecked = TRUE;
      if (SUCCEEDED(CNktDvProcessHandlesMgr::Get(&cPhMgr)))
        hProc[1] = cPhMgr->GetHandle(dwPid, NKT_ACCESS_WRITE);
    }
  }
  return hProc[1];
}