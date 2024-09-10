already_AddRefed<Service>
Service::getSingleton()
{
  if (gService) {
    return do_AddRef(gService);
  }

  // Ensure that we are using the same version of SQLite that we compiled with
  // or newer.  Our configure check ensures we are using a new enough version
  // at compile time.
  if (SQLITE_VERSION_NUMBER > ::sqlite3_libversion_number()) {
    nsCOMPtr<nsIPromptService> ps(do_GetService(NS_PROMPTSERVICE_CONTRACTID));
    if (ps) {
      nsAutoString title, message;
      title.AppendLiteral("SQLite Version Error");
      message.AppendLiteral("The application has been updated, but the SQLite "
                            "library wasn't updated properly and the application "
                            "cannot run. Please try to launch the application again. "
                            "If that should still fail, please try reinstalling "
                            "it, or visit https://support.mozilla.org/.");
      (void)ps->Alert(nullptr, title.get(), message.get());
    }
    MOZ_CRASH("SQLite Version Error");
  }

  // The first reference to the storage service must be obtained on the
  // main thread.
  NS_ENSURE_TRUE(NS_IsMainThread(), nullptr);
  RefPtr<Service> service = new Service();
  if (NS_SUCCEEDED(service->initialize())) {
    // Note: This is cleared in the Service destructor.
    gService = service.get();
    return service.forget();
  }

  return nullptr;
}