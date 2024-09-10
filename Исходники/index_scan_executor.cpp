bool IndexScanExecutor::ExecPrimaryIndexLookup() {
  PL_ASSERT(!done_);

  std::vector<ItemPointer *> tuple_location_ptrs;

  PL_ASSERT(index_->GetIndexType() == INDEX_CONSTRAINT_TYPE_PRIMARY_KEY);

  if (0 == key_column_ids_.size()) {
    index_->ScanAllKeys(tuple_location_ptrs);
  } else {
    index_->Scan(values_, key_column_ids_, expr_types_,
                 SCAN_DIRECTION_TYPE_FORWARD, tuple_location_ptrs);
  }


  if (tuple_location_ptrs.size() == 0) return false;

  auto &transaction_manager =
      concurrency::TransactionManagerFactory::GetInstance();

  std::map<oid_t, std::vector<oid_t>> visible_tuples;
  std::vector<ItemPointer> garbage_tuples;
  // for every tuple that is found in the index.
  for (auto tuple_location_ptr : tuple_location_ptrs) {
    
    ItemPointer tuple_location = *tuple_location_ptr;
    
    auto &manager = catalog::Manager::GetInstance();
    auto tile_group = manager.GetTileGroup(tuple_location.block);
    auto tile_group_header = tile_group.get()->GetHeader();

    size_t chain_length = 0;
    while (true) {

      ++chain_length;

      // if the tuple is visible.
      if (transaction_manager.IsVisible(tile_group_header,
                                        tuple_location.offset)) {

        LOG_TRACE("traverse chain length : %lu", chain_length);
        LOG_TRACE("perform read: %u, %u", tuple_location.block,
                 tuple_location.offset);

        // perform predicate evaluation.
        if (predicate_ == nullptr) {
          visible_tuples[tuple_location.block].push_back(tuple_location.offset);

          auto res = transaction_manager.PerformRead(tuple_location);
          if (!res) {
            transaction_manager.SetTransactionResult(RESULT_FAILURE);
            return res;
          }
        } else {
          expression::ContainerTuple<storage::TileGroup> tuple(
              tile_group.get(), tuple_location.offset);
          auto eval =
              predicate_->Evaluate(&tuple, nullptr, executor_context_).IsTrue();
          if (eval == true) {
            visible_tuples[tuple_location.block]
                .push_back(tuple_location.offset);

            auto res = transaction_manager.PerformRead(tuple_location);
            if (!res) {
              transaction_manager.SetTransactionResult(RESULT_FAILURE);
              return res;
            }
          }
        }
        break;
      }
      // if the tuple is not visible.
      else {
        ItemPointer old_item = tuple_location;
        cid_t old_end_cid = tile_group_header->GetEndCommitId(old_item.offset);

        tuple_location = tile_group_header->GetNextItemPointer(old_item.offset);
        // there must exist a visible version.

        // FIXME: currently, only speculative read transaction manager **may** see a null version
        // it's a potential bug
        if(tuple_location.IsNull()) {
          transaction_manager.SetTransactionResult(RESULT_FAILURE);
          // FIXME: this cause unnecessary abort when we have delete operations
          return false;
        }

        // FIXME: Is this always true? what if we have a deleted tuple? --jiexi
        PL_ASSERT(tuple_location.IsNull() == false);

        cid_t max_committed_cid = transaction_manager.GetMaxCommittedCid();

        // check whether older version is garbage.

        if (old_end_cid <= max_committed_cid) {
          PL_ASSERT(tile_group_header->GetTransactionId(old_item.offset) == INITIAL_TXN_ID ||
                      tile_group_header->GetTransactionId(old_item.offset) == INVALID_TXN_ID);

          if (tile_group_header->SetAtomicTransactionId(old_item.offset, INVALID_TXN_ID) == true) {

            // atomically swap item pointer held in the index bucket.
            AtomicUpdateItemPointer(tuple_location_ptr, tuple_location);

            // currently, let's assume only primary index exists.
            // gc::GCManagerFactory::GetInstance().RecycleTupleSlot(
            //     table_->GetOid(), old_item.block, old_item.offset,
            //     transaction_manager.GetNextCommitId());
            garbage_tuples.push_back(old_item);

            tile_group = manager.GetTileGroup(tuple_location.block);
            tile_group_header = tile_group.get()->GetHeader();
            tile_group_header->SetPrevItemPointer(tuple_location.offset, INVALID_ITEMPOINTER);

          } else {

            tile_group = manager.GetTileGroup(tuple_location.block);
            tile_group_header = tile_group.get()->GetHeader();
          }

        } else {
        tile_group = manager.GetTileGroup(tuple_location.block);
        tile_group_header = tile_group.get()->GetHeader();

        }


      }
    }
  }

  // Add all garbage tuples to GC manager
  if(garbage_tuples.size() != 0) {
    cid_t garbage_timestamp = transaction_manager.GetNextCommitId();
    for (auto garbage : garbage_tuples) {
      gc::GCManagerFactory::GetInstance().RecycleTupleSlot(
        table_->GetOid(), garbage.block, garbage.offset, garbage_timestamp);
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

  done_ = true;

  LOG_TRACE("Result tiles : %lu", result_.size());

  return true;
}