nsresult
Logger::Shutdown()
{
  MOZ_ASSERT(NS_IsMainThread());
  nsresult rv = mThread->Dispatch(NewNonOwningRunnableMethod(this,
                                                             &Logger::CloseFile),
                                  NS_DISPATCH_NORMAL);
  NS_WARNING_ASSERTION(NS_SUCCEEDED(rv), "Dispatch failed");

  rv = mThread->Shutdown();
  NS_WARNING_ASSERTION(NS_SUCCEEDED(rv), "Shutdown failed");
  return NS_OK;
}