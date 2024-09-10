void BrowserFactory::ClearCache() {
  LOG(TRACE) << "Entering BrowserFactory::ClearCache";
  if (this->clear_cache_) {
    if (IsWindowsVistaOrGreater()) {
      LOG(DEBUG) << "Clearing cache with low mandatory integrity level as required on Windows Vista or later.";
      this->InvokeClearCacheUtility(true);
    }
    LOG(DEBUG) << "Clearing cache with normal process execution.";
    this->InvokeClearCacheUtility(false);
  }
}