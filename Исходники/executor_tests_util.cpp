/**
 * @brief  Populates the tiles in the given tile-group in a specific manner.
 * @param tile_group Tile-group to populate with values.
 * @param num_rows Number of tuples to insert.
 */
void ExecutorTestsUtil::PopulateTiles(
    std::shared_ptr<storage::TileGroup> tile_group, int num_rows) {
  // Create tuple schema from tile schemas.
  std::vector<catalog::Schema> &tile_schemas = tile_group->GetTileSchemas();
  std::unique_ptr<catalog::Schema> schema(
      catalog::Schema::AppendSchemaList(tile_schemas));

  // Ensure that the tile group is as expected.
  assert(schema->GetColumnCount() == 4);

  // Insert tuples into tile_group.
  auto &txn_manager = concurrency::TransactionManager::GetInstance();
  const bool allocate = true;
  auto txn = txn_manager.BeginTransaction();
  const txn_id_t txn_id = txn->GetTransactionId();
  const cid_t commit_id = txn->GetCommitId();
  auto testing_pool = TestingHarness::GetInstance().GetTestingPool();

  for (int col_itr = 0; col_itr < num_rows; col_itr++) {
    storage::Tuple tuple(schema.get(), allocate);
    tuple.SetValue(0, ValueFactory::GetIntegerValue(PopulatedValue(col_itr, 0)),
                   testing_pool);
    tuple.SetValue(1, ValueFactory::GetIntegerValue(PopulatedValue(col_itr, 1)),
                   testing_pool);
    tuple.SetValue(2, ValueFactory::GetDoubleValue(PopulatedValue(col_itr, 2)),
                   testing_pool);
    Value string_value = ValueFactory::GetStringValue(
        std::to_string(PopulatedValue(col_itr, 3)));
    tuple.SetValue(3, string_value, testing_pool);

    oid_t tuple_slot_id = tile_group->InsertTuple(txn_id, &tuple);
    tile_group->CommitInsertedTuple(tuple_slot_id, txn_id, commit_id);
  }

  txn_manager.CommitTransaction();
}