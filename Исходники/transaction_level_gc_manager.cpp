void TransactionLevelGCManager::Running(const int &thread_id) {

  uint32_t backoff_shifts = 0;

  while (true) {
    auto &txn_manager = concurrency::TransactionManagerFactory::GetInstance();
    auto max_cid = txn_manager.GetMaxCommittedCid();

    PL_ASSERT(max_cid != MAX_CID);

    int reclaimed_count = Reclaim(thread_id, max_cid);

    int unlinked_count = Unlink(thread_id, max_cid);

    if (is_running_ == false) {
      return;
    }

    if (reclaimed_count == 0 && unlinked_count == 0) {
      // sleep at most 0.8192 s
      if (backoff_shifts < 13) {
        ++backoff_shifts;
      }
      uint64_t sleep_duration = 1UL << backoff_shifts;
      sleep_duration *= 100;
      std::this_thread::sleep_for(std::chrono::microseconds(sleep_duration));
    } else {
      backoff_shifts >>= 1;
    }
  }
}