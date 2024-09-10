nsresult
ShutdownXPCOM(nsIServiceManager* aServMgr)
{
  // Make sure the hang monitor is enabled for shutdown.
  HangMonitor::NotifyActivity();

  if (!NS_IsMainThread()) {
    NS_RUNTIMEABORT("Shutdown on wrong thread");
  }

  nsresult rv;
  nsCOMPtr<nsISimpleEnumerator> moduleLoaders;

  // Notify observers of xpcom shutting down
  {
    // Block it so that the COMPtr will get deleted before we hit
    // servicemanager shutdown

    nsCOMPtr<nsIThread> thread = do_GetCurrentThread();
    if (NS_WARN_IF(!thread)) {
      return NS_ERROR_UNEXPECTED;
    }

    RefPtr<nsObserverService> observerService;
    CallGetService("@mozilla.org/observer-service;1",
                   (nsObserverService**)getter_AddRefs(observerService));

    if (observerService) {
      mozilla::KillClearOnShutdown(ShutdownPhase::WillShutdown);
      observerService->NotifyObservers(nullptr,
                                       NS_XPCOM_WILL_SHUTDOWN_OBSERVER_ID,
                                       nullptr);

      nsCOMPtr<nsIServiceManager> mgr;
      rv = NS_GetServiceManager(getter_AddRefs(mgr));
      if (NS_SUCCEEDED(rv)) {
        mozilla::KillClearOnShutdown(ShutdownPhase::Shutdown);
        observerService->NotifyObservers(mgr, NS_XPCOM_SHUTDOWN_OBSERVER_ID,
                                         nullptr);
      }
    }

    // This must happen after the shutdown of media and widgets, which
    // are triggered by the NS_XPCOM_SHUTDOWN_OBSERVER_ID notification.
    NS_ProcessPendingEvents(thread);
    gfxPlatform::ShutdownLayersIPC();

    mozilla::scache::StartupCache::DeleteSingleton();
    if (observerService)
    {
      mozilla::KillClearOnShutdown(ShutdownPhase::ShutdownThreads);
      observerService->NotifyObservers(nullptr,
                                       NS_XPCOM_SHUTDOWN_THREADS_OBSERVER_ID,
                                       nullptr);
    }

    gXPCOMThreadsShutDown = true;
    NS_ProcessPendingEvents(thread);

    // Shutdown the timer thread and all timers that might still be alive before
    // shutting down the component manager
    nsTimerImpl::Shutdown();

    NS_ProcessPendingEvents(thread);

    // Shutdown all remaining threads.  This method does not return until
    // all threads created using the thread manager (with the exception of
    // the main thread) have exited.
    nsThreadManager::get()->Shutdown();

    NS_ProcessPendingEvents(thread);

    HangMonitor::NotifyActivity();

    // Late-write checks needs to find the profile directory, so it has to
    // be initialized before mozilla::services::Shutdown or (because of
    // xpcshell tests replacing the service) modules being unloaded.
    mozilla::InitLateWriteChecks();

    // We save the "xpcom-shutdown-loaders" observers to notify after
    // the observerservice is gone.
    if (observerService) {
      mozilla::KillClearOnShutdown(ShutdownPhase::ShutdownLoaders);
      observerService->EnumerateObservers(NS_XPCOM_SHUTDOWN_LOADERS_OBSERVER_ID,
                                          getter_AddRefs(moduleLoaders));

      observerService->Shutdown();
    }
  }

  // Free ClearOnShutdown()'ed smart pointers.  This needs to happen *after*
  // we've finished notifying observers of XPCOM shutdown, because shutdown
  // observers themselves might call ClearOnShutdown().
  mozilla::KillClearOnShutdown(ShutdownPhase::ShutdownFinal);

  // XPCOM is officially in shutdown mode NOW
  // Set this only after the observers have been notified as this
  // will cause servicemanager to become inaccessible.
  mozilla::services::Shutdown();

  // We may have AddRef'd for the caller of NS_InitXPCOM, so release it
  // here again:
  NS_IF_RELEASE(aServMgr);

  // Shutdown global servicemanager
  if (nsComponentManagerImpl::gComponentManager) {
    nsComponentManagerImpl::gComponentManager->FreeServices();
  }

  // Release the directory service
  nsDirectoryService::gService = nullptr;

  free(gGREBinPath);
  gGREBinPath = nullptr;

  if (moduleLoaders) {
    bool more;
    nsCOMPtr<nsISupports> el;
    while (NS_SUCCEEDED(moduleLoaders->HasMoreElements(&more)) && more) {
      moduleLoaders->GetNext(getter_AddRefs(el));

      // Don't worry about weak-reference observers here: there is
      // no reason for weak-ref observers to register for
      // xpcom-shutdown-loaders

      // FIXME: This can cause harmless writes from sqlite committing
      // log files. We have to ignore them before we can move
      // the mozilla::PoisonWrite call before this point. See bug
      // 834945 for the details.
      nsCOMPtr<nsIObserver> obs(do_QueryInterface(el));
      if (obs) {
        obs->Observe(nullptr, NS_XPCOM_SHUTDOWN_LOADERS_OBSERVER_ID, nullptr);
      }
    }

    moduleLoaders = nullptr;
  }

  bool shutdownCollect;
#ifdef NS_FREE_PERMANENT_DATA
  shutdownCollect = true;
#else
  shutdownCollect = !!PR_GetEnv("MOZ_CC_RUN_DURING_SHUTDOWN");
#endif
  nsCycleCollector_shutdown(shutdownCollect);

  PROFILER_MARKER("Shutdown xpcom");
  // If we are doing any shutdown checks, poison writes.
  if (gShutdownChecks != SCM_NOTHING) {
#ifdef XP_MACOSX
    mozilla::OnlyReportDirtyWrites();
#endif /* XP_MACOSX */
    mozilla::BeginLateWriteChecks();
  }

  // Shutdown nsLocalFile string conversion
  NS_ShutdownLocalFile();
#ifdef XP_UNIX
  NS_ShutdownNativeCharsetUtils();
#endif

  // Shutdown xpcom. This will release all loaders and cause others holding
  // a refcount to the component manager to release it.
  if (nsComponentManagerImpl::gComponentManager) {
    rv = (nsComponentManagerImpl::gComponentManager)->Shutdown();
    NS_ASSERTION(NS_SUCCEEDED(rv), "Component Manager shutdown failed.");
  } else {
    NS_WARNING("Component Manager was never created ...");
  }

#ifdef MOZ_ENABLE_PROFILER_SPS
  // In optimized builds we don't do shutdown collections by default, so
  // uncollected (garbage) objects may keep the nsXPConnect singleton alive,
  // and its XPCJSRuntime along with it. However, we still destroy various
  // bits of state in JS_ShutDown(), so we need to make sure the profiler
  // can't access them when it shuts down. This call nulls out the
  // JS pseudo-stack's internal reference to the main thread JSRuntime,
  // duplicating the call in XPCJSRuntime::~XPCJSRuntime() in case that
  // never fired.
  if (PseudoStack* stack = mozilla_get_pseudo_stack()) {
    stack->sampleRuntime(nullptr);
  }
#endif

  // Shut down the JS engine.
  JS_ShutDown();

  // Release our own singletons
  // Do this _after_ shutting down the component manager, because the
  // JS component loader will use XPConnect to call nsIModule::canUnload,
  // and that will spin up the InterfaceInfoManager again -- bad mojo
  XPTInterfaceInfoManager::FreeInterfaceInfoManager();

  // Finally, release the component manager last because it unloads the
  // libraries:
  if (nsComponentManagerImpl::gComponentManager) {
    nsrefcnt cnt;
    NS_RELEASE2(nsComponentManagerImpl::gComponentManager, cnt);
    NS_ASSERTION(cnt == 0, "Component Manager being held past XPCOM shutdown.");
  }
  nsComponentManagerImpl::gComponentManager = nullptr;
  nsCategoryManager::Destroy();

  NS_ShutdownAtomTable();

  NS_IF_RELEASE(gDebug);

  delete sIOThread;
  sIOThread = nullptr;

  delete sMessageLoop;
  sMessageLoop = nullptr;

  if (sCommandLineWasInitialized) {
    CommandLine::Terminate();
    sCommandLineWasInitialized = false;
  }

  delete sExitManager;
  sExitManager = nullptr;

  Omnijar::CleanUp();

  HangMonitor::Shutdown();

  delete sMainHangMonitor;
  sMainHangMonitor = nullptr;

  BackgroundHangMonitor::Shutdown();

  profiler_shutdown();

  NS_LogTerm();

#if defined(MOZ_WIDGET_GONK)
  // This _exit(0) call is intended to be temporary, to get shutdown leak
  // checking working on non-B2G platforms.
  // On debug B2G, the child process crashes very late.  Instead, just
  // give up so at least we exit cleanly. See bug 1071866.
  if (XRE_IsContentProcess()) {
      NS_WARNING("Exiting child process early!");
      _exit(0);
  }
#endif

  return NS_OK;
}