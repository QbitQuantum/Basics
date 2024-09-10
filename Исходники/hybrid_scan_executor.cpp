bool HybridScanExecutor::ExecPrimaryIndexLookup() {
  PL_ASSERT(index_done_ == false);

  const planner::HybridScanPlan &node = GetPlanNode<planner::HybridScanPlan>();
  bool acquire_owner = GetPlanNode<planner::AbstractScan>().IsForUpdate();

  auto key_column_ids_ = node.GetKeyColumnIds();
  auto expr_type_ = node.GetExprTypes();

  std::vector<ItemPointer *> tuple_location_ptrs;

  PL_ASSERT(index_->GetIndexType() == INDEX_CONSTRAINT_TYPE_PRIMARY_KEY);

  if (0 == key_column_ids_.size()) {
    LOG_TRACE("Scan all keys");
    index_->ScanAllKeys(tuple_location_ptrs);
  } else {
    LOG_TRACE("Scan");
    index_->Scan(values_,
                 key_column_ids_,
                 expr_type_,
                 SCAN_DIRECTION_TYPE_FORWARD,
                 tuple_location_ptrs,
                 &node.GetIndexPredicate().GetConjunctionList()[0]);
  }

  LOG_TRACE("Result tuple count: %lu", tuple_location_ptrs.size());

  auto &transaction_manager =
      concurrency::TransactionManagerFactory::GetInstance();

  auto current_txn = executor_context_->GetTransaction();

  if (tuple_location_ptrs.size() == 0) {
    index_done_ = true;
    return false;
  }

  std::map<oid_t, std::vector<oid_t>> visible_tuples;

  // for every tuple that is found in the index.
  for (auto tuple_location_ptr : tuple_location_ptrs) {
    ItemPointer tuple_location = *tuple_location_ptr;

    if (type_ == HYBRID_SCAN_TYPE_HYBRID &&
        tuple_location.block >= (block_threshold)) {
      item_pointers_.insert(tuple_location);
    }

    auto &manager = catalog::Manager::GetInstance();
    auto tile_group = manager.GetTileGroup(tuple_location.block);
    auto tile_group_header = tile_group.get()->GetHeader();

    // perform transaction read
    size_t chain_length = 0;
    while (true) {
      ++chain_length;

      auto visibility = transaction_manager.IsVisible(current_txn, tile_group_header, tuple_location.offset);

      if (visibility == VISIBILITY_OK) {

        visible_tuples[tuple_location.block].push_back(tuple_location.offset);
        auto res = transaction_manager.PerformRead(current_txn, tuple_location, acquire_owner);
        if (!res) {
          transaction_manager.SetTransactionResult(current_txn, RESULT_FAILURE);
          return res;
        }
        break;
      } else {
        ItemPointer old_item = tuple_location;
        cid_t old_end_cid = tile_group_header->GetEndCommitId(old_item.offset);

        tuple_location = tile_group_header->GetNextItemPointer(old_item.offset);
        // there must exist a visible version.
        assert(tuple_location.IsNull() == false);

        cid_t max_committed_cid = transaction_manager.GetMaxCommittedCid();

        // check whether older version is garbage.
        if (old_end_cid < max_committed_cid) {
          assert(tile_group_header->GetTransactionId(old_item.offset) ==
              INITIAL_TXN_ID ||
              tile_group_header->GetTransactionId(old_item.offset) ==
                  INVALID_TXN_ID);

          if (tile_group_header->SetAtomicTransactionId(
              old_item.offset, INVALID_TXN_ID) == true) {
            // atomically swap item pointer held in the index bucket.
            AtomicUpdateItemPointer(tuple_location_ptr, tuple_location);
          }
        }

        tile_group = manager.GetTileGroup(tuple_location.block);
        tile_group_header = tile_group.get()->GetHeader();
      }
    }
  }

  // Construct a logical tile for each block
  for (auto tuples : visible_tuples) {
    auto &manager = catalog::Manager::GetInstance();
    auto tile_group = manager.GetTileGroup(tuples.first);

    std::unique_ptr<LogicalTile> logical_tile(LogicalTileFactory::GetTile());

    // Add relevant columns to logical tile
    logical_tile->AddColumns(tile_group, full_column_ids_);
    logical_tile->AddPositionList(std::move(tuples.second));

    if (column_ids_.size() != 0) {
      logical_tile->ProjectColumns(full_column_ids_, column_ids_);
    }

    result_.push_back(logical_tile.release());
  }

  index_done_ = true;

  LOG_TRACE("Result tiles : %lu", result_.size());

  return true;
}