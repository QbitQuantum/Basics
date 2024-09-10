nsresult
sbWindowWatcher::CallWithWindow_Proxy(const nsAString&           aWindowType,
                                  sbICallWithWindowCallback* aCallback,
                                  bool                     aWait)
{
  // Validate arguments.
  NS_ENSURE_ARG_POINTER(aCallback);

  // Function variables.
  nsresult rv;

  // If not on main thread, call back through a proxy.
  if (!SB_IsMainThread(mThreadManager)) {
    nsRefPtr<sbRunnable_<nsresult>> job =
      new sbRunnableMethod3_<nsresult,sbWindowWatcher,
      const nsAString&,sbICallWithWindowCallback*,bool>(
          *this,&sbWindowWatcher::CallWithWindow_Proxy,
          aWindowType,aCallback,aWait);
    // Call back through the proxy.  Wait for window if specified to do so.
    rv = NS_OK;
    while (1) {
      // Call the proxied window watcher.  Exit loop on success or if not
      // waiting.
      NS_DispatchToMainThread(job);
      rv = job->Wait();
      if (NS_SUCCEEDED(rv) || !aWait)
        break;
      if (rv != NS_ERROR_NOT_AVAILABLE)
        NS_ENSURE_SUCCESS(rv, NS_ERROR_FAILURE);

      // Wait for a window if none available.
      rv = WaitForWindow(aWindowType);
      NS_ENSURE_SUCCESS(rv, NS_ERROR_FAILURE);
    }
    NS_ENSURE_SUCCESS(rv, NS_ERROR_FAILURE);

    return NS_OK;
  }

  // Operate within the monitor.
  mozilla::ReentrantMonitorAutoEnter autoMonitor(mMonitor);

  // Check if window is already available.
  nsCOMPtr<nsIDOMWindow> window;
  rv = GetWindow(aWindowType, getter_AddRefs(window));
  NS_ENSURE_SUCCESS(rv, NS_ERROR_FAILURE);

  // If a window is available or this instance is shutting down, call the
  // callback.  Otherwise, place the call with window information on the call
  // with window list.
  if (window || mIsShuttingDown) {
    aCallback->HandleWindowCallback(window);
  } else {
    // If specified to wait and the window is not available, return a not
    // available error indication instead of enqueuing onto the call with window
    // list.
    if (aWait)
      return NS_ERROR_NOT_AVAILABLE;

    // Place the call with window information on the call with window list.
    CallWithWindowInfo callWithWindowInfo;
    callWithWindowInfo.windowType = aWindowType;
    callWithWindowInfo.callback = aCallback;
    mCallWithWindowList.AppendElement(callWithWindowInfo);
  }

  return NS_OK;
}