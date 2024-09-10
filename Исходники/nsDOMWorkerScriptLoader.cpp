nsresult
nsDOMWorkerScriptLoader::LoadScripts(JSContext* aCx,
                                     const nsTArray<nsString>& aURLs,
                                     PRBool aForWorker)
{
  NS_ASSERTION(!NS_IsMainThread(), "Wrong thread!");
  NS_ASSERTION(aCx, "Null context!");

  mTarget = NS_GetCurrentThread();
  NS_ASSERTION(mTarget, "This should never be null!");

  if (mCanceled) {
    return NS_ERROR_ABORT;
  }

  mForWorker = aForWorker;

  mScriptCount = aURLs.Length();
  if (!mScriptCount) {
    return NS_ERROR_INVALID_ARG;
  }

  // Do all the memory work for these arrays now rather than checking for
  // failures all along the way.
  PRBool success = mLoadInfos.SetCapacity(mScriptCount);
  NS_ENSURE_TRUE(success, NS_ERROR_OUT_OF_MEMORY);

  // Need one runnable per script and then an extra for the finished
  // notification.
  success = mPendingRunnables.SetCapacity(mScriptCount + 1);
  NS_ENSURE_TRUE(success, NS_ERROR_OUT_OF_MEMORY);

  for (PRUint32 index = 0; index < mScriptCount; index++) {
    ScriptLoadInfo* newInfo = mLoadInfos.AppendElement();
    NS_ASSERTION(newInfo, "Shouldn't fail if SetCapacity succeeded above!");

    newInfo->url.Assign(aURLs[index]);
    if (newInfo->url.IsEmpty()) {
      return NS_ERROR_INVALID_ARG;
    }

    success = newInfo->scriptObj.Hold(aCx);
    NS_ENSURE_TRUE(success, NS_ERROR_FAILURE);
  }

  // Don't want timeouts, etc., from queuing up while we're waiting on the
  // network or compiling.
  AutoSuspendWorkerEvents aswe(this);

  nsresult rv = DoRunLoop(aCx);
  if (NS_FAILED(rv)) {
    return rv;
  }

  // Verify that all scripts downloaded and compiled.
  rv = VerifyScripts(aCx);
  if (NS_FAILED(rv)) {
    return rv;
  }

  rv = ExecuteScripts(aCx);
  if (NS_FAILED(rv)) {
    return rv;
  }

  return NS_OK;
}