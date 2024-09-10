void TimestampOrderingTransactionManager::PerformUpdate(
    TransactionContext *const current_txn, const ItemPointer &location,
    const ItemPointer &new_location) {
  PL_ASSERT(current_txn->GetIsolationLevel() != IsolationLevelType::READ_ONLY);

  ItemPointer old_location = location;

  LOG_TRACE("Performing Update old tuple %u %u", old_location.block,
            old_location.offset);
  LOG_TRACE("Performing Update new tuple %u %u", new_location.block,
            new_location.offset);

  auto &manager = catalog::Manager::GetInstance();

  auto tile_group_header =
      manager.GetTileGroup(old_location.block)->GetHeader();
  auto new_tile_group_header =
      manager.GetTileGroup(new_location.block)->GetHeader();

  auto transaction_id = current_txn->GetTransactionId();
  // if we can perform update, then we must have already locked the older
  // version.
  PL_ASSERT(tile_group_header->GetTransactionId(old_location.offset) ==
            transaction_id);
  PL_ASSERT(tile_group_header->GetPrevItemPointer(old_location.offset)
                .IsNull() == true);

  // check whether the new version is empty.
  PL_ASSERT(new_tile_group_header->GetTransactionId(new_location.offset) ==
            INVALID_TXN_ID);
  PL_ASSERT(new_tile_group_header->GetBeginCommitId(new_location.offset) ==
            MAX_CID);
  PL_ASSERT(new_tile_group_header->GetEndCommitId(new_location.offset) ==
            MAX_CID);

  // if the executor doesn't call PerformUpdate after AcquireOwnership,
  // no one will possibly release the write lock acquired by this txn.

  // Set double linked list
  tile_group_header->SetPrevItemPointer(old_location.offset, new_location);

  new_tile_group_header->SetNextItemPointer(new_location.offset, old_location);

  new_tile_group_header->SetTransactionId(new_location.offset, transaction_id);

  // we should guarantee that the newer version is all set before linking the
  // newer version to older version.
  COMPILER_MEMORY_FENCE;

  InitTupleReserved(new_tile_group_header, new_location.offset);

  // we must be updating the latest version.
  // Set the header information for the new version
  ItemPointer *index_entry_ptr =
      tile_group_header->GetIndirection(old_location.offset);

  // if there's no primary index on a table, then index_entry_ptr == nullptr.
  if (index_entry_ptr != nullptr) {
    new_tile_group_header->SetIndirection(new_location.offset, index_entry_ptr);

    // Set the index header in an atomic way.
    // We do it atomically because we don't want any one to see a half-done
    // pointer.
    // In case of contention, no one can update this pointer when we are
    // updating it
    // because we are holding the write lock. This update should success in
    // its first trial.
    UNUSED_ATTRIBUTE auto res =
        AtomicUpdateItemPointer(index_entry_ptr, new_location);
    PL_ASSERT(res == true);
  }

  // Add the old tuple into the update set
  current_txn->RecordUpdate(old_location);

  // Increment table update op stats
  if (static_cast<StatsType>(settings::SettingsManager::GetInt(settings::SettingId::stats_mode)) !=
      StatsType::INVALID) {
    stats::BackendStatsContext::GetInstance()->IncrementTableUpdates(
        new_location.block);
  }
}