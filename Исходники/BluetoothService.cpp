nsresult
BluetoothService::HandleShutdown()
{
  MOZ_ASSERT(NS_IsMainThread());

  // This is a two phase shutdown. First we notify all child processes that
  // bluetooth is going away, and then we wait for them to acknowledge. Then we
  // close down all the bluetooth machinery.

  gInShutdown = true;

  Cleanup();

  AutoInfallibleTArray<BluetoothParent*, 10> childActors;
  GetAllBluetoothActors(childActors);

  if (!childActors.IsEmpty()) {
    // Notify child processes that they should stop using bluetooth now.
    for (uint32_t index = 0; index < childActors.Length(); index++) {
      childActors[index]->BeginShutdown();
    }

    // Create a timer to ensure that we don't wait forever for a child process
    // or the bluetooth threads to finish. If we don't get a timer or can't use
    // it for some reason then we skip all the waiting entirely since we really
    // can't afford to hang on shutdown.
    nsCOMPtr<nsITimer> timer = do_CreateInstance(NS_TIMER_CONTRACTID);
    MOZ_ASSERT(timer);

    if (timer) {
      bool timeExceeded = false;

      if (NS_SUCCEEDED(timer->InitWithFuncCallback(ShutdownTimeExceeded,
                                                   &timeExceeded,
                                                   DEFAULT_SHUTDOWN_TIMER_MS,
                                                   nsITimer::TYPE_ONE_SHOT))) {
        nsIThread* currentThread = NS_GetCurrentThread();
        MOZ_ASSERT(currentThread);

        // Wait for those child processes to acknowledge.
        while (!timeExceeded && !childActors.IsEmpty()) {
          if (!NS_ProcessNextEvent(currentThread)) {
            MOZ_ASSERT(false, "Something horribly wrong here!");
            break;
          }
          GetAllBluetoothActors(childActors);
        }

        if (NS_FAILED(timer->Cancel())) {
          MOZ_NOT_REACHED("Failed to cancel shutdown timer, this will crash!");
        }
      }
      else {
        MOZ_ASSERT(false, "Failed to initialize shutdown timer!");
      }
    }
  }

  if (IsEnabled() && NS_FAILED(StartStopBluetooth(false))) {
    MOZ_ASSERT(false, "Failed to deliver stop message!");
  }

  return NS_OK;
}