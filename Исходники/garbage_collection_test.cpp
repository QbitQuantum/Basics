// count number of expired versions.
int GarbageNum(storage::DataTable *table) {
  auto table_tile_group_count_ = table->GetTileGroupCount();
  auto current_tile_group_offset_ = START_OID;

  int old_num = 0;

  while (current_tile_group_offset_ < table_tile_group_count_) {
    auto tile_group = table->GetTileGroup(current_tile_group_offset_++);
    auto tile_group_header = tile_group->GetHeader();
    oid_t active_tuple_count = tile_group->GetNextTupleSlot();

    for (oid_t tuple_id = 0; tuple_id < active_tuple_count; tuple_id++) {
      auto tuple_txn_id = tile_group_header->GetTransactionId(tuple_id);
      auto tuple_end_cid = tile_group_header->GetEndCommitId(tuple_id);
      if (tuple_txn_id == INITIAL_TXN_ID && tuple_end_cid != MAX_CID) {
        old_num++;
      }
    }
  }

  LOG_INFO("old version num = %d", old_num);
  return old_num;
}