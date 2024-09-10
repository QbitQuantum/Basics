already_AddRefed<SharedThreadPool>
SharedThreadPool::Get(const nsCString& aName, uint32_t aThreadLimit)
{
  MOZ_ASSERT(sMonitor && sPools);
  ReentrantMonitorAutoEnter mon(*sMonitor);
  SharedThreadPool* pool = nullptr;
  nsresult rv;

  if (auto entry = sPools->LookupForAdd(aName)) {
    pool = entry.Data();
    if (NS_FAILED(pool->EnsureThreadLimitIsAtLeast(aThreadLimit))) {
      NS_WARNING("Failed to set limits on thread pool");
    }
  } else {
    nsCOMPtr<nsIThreadPool> threadPool(CreateThreadPool(aName));
    if (NS_WARN_IF(!threadPool)) {
      sPools->Remove(aName); // XXX entry.Remove()
      return nullptr;
    }
    pool = new SharedThreadPool(aName, threadPool);

    // Set the thread and idle limits. Note that we don't rely on the
    // EnsureThreadLimitIsAtLeast() call below, as the default thread limit
    // is 4, and if aThreadLimit is less than 4 we'll end up with a pool
    // with 4 threads rather than what we expected; so we'll have unexpected
    // behaviour.
    rv = pool->SetThreadLimit(aThreadLimit);
    if (NS_WARN_IF(NS_FAILED(rv))) {
      sPools->Remove(aName); // XXX entry.Remove()
      return nullptr;
    }

    rv = pool->SetIdleThreadLimit(aThreadLimit);
    if (NS_WARN_IF(NS_FAILED(rv))) {
      sPools->Remove(aName); // XXX entry.Remove()
      return nullptr;
    }

    entry.OrInsert([pool] () { return pool; });
  }

  MOZ_ASSERT(pool);
  RefPtr<SharedThreadPool> instance(pool);
  return instance.forget();
}