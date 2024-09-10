NS_IMETHODIMP
NamedPipeService::AddDataObserver(void* aHandle,
                                  nsINamedPipeDataObserver* aObserver)
{
  if (!aHandle || aHandle == INVALID_HANDLE_VALUE || !aObserver) {
    return NS_ERROR_ILLEGAL_VALUE;
  }

  nsresult rv;

  HANDLE h = CreateIoCompletionPort(aHandle,
                                    mIocp,
                                    reinterpret_cast<ULONG_PTR>(aObserver),
                                    1);
  if (NS_WARN_IF(!h)) {
    LOG_NPS_ERROR("CreateIoCompletionPort error (%d)", GetLastError());
    return NS_ERROR_FAILURE;
  }
  if (NS_WARN_IF(h != mIocp)) {
    LOG_NPS_ERROR("CreateIoCompletionPort got unexpected value %p (should be %p)",
              h,
              mIocp);
    CloseHandle(h);
    return NS_ERROR_FAILURE;
  }

  {
    MutexAutoLock lock(mLock);
    MOZ_ASSERT(!mObservers.Contains(aObserver));

    mObservers.AppendElement(aObserver);

    // start event loop
    if (mObservers.Length() == 1) {
      rv = mThread->Dispatch(this, NS_DISPATCH_NORMAL);
      if (NS_WARN_IF(NS_FAILED(rv))) {
        LOG_NPS_ERROR("Dispatch to thread failed (%08x)", rv);
        mObservers.Clear();
        return rv;
      }
    }
  }

  return NS_OK;
}