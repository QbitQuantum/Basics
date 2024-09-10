TEST(AggregateTests, HashDistinctTest) {
  /*
   * SELECT d, a, b, c FROM table GROUP BY a, b, c, d;
   */

  const int tuple_count = TESTS_TUPLES_PER_TILEGROUP;

  // Create a table and wrap it in logical tiles
  auto &txn_manager = concurrency::TransactionManager::GetInstance();
  auto txn = txn_manager.BeginTransaction();
  auto txn_id = txn->GetTransactionId();
  std::unique_ptr<storage::DataTable> data_table(
      ExecutorTestsUtil::CreateTable(tuple_count, false));
  ExecutorTestsUtil::PopulateTable(txn, data_table.get(),
                                   2 * tuple_count, false,
                                   true,
                                   true);  // let it be random
  txn_manager.CommitTransaction();

  std::unique_ptr<executor::LogicalTile> source_logical_tile1(
      executor::LogicalTileFactory::WrapTileGroup(data_table->GetTileGroup(0),
                                                  txn_id));

  std::unique_ptr<executor::LogicalTile> source_logical_tile2(
      executor::LogicalTileFactory::WrapTileGroup(data_table->GetTileGroup(1),
                                                  txn_id));

  // (1-5) Setup plan node

  // 1) Set up group-by columns
  std::vector<oid_t> group_by_columns = {0, 1, 2, 3};

  // 2) Set up project info
  planner::ProjectInfo::DirectMapList direct_map_list = {
      {0, {0, 3}}, {1, {0, 0}}, {2, {0, 1}}, {3, {0, 2}}};
  auto proj_info = new planner::ProjectInfo(planner::ProjectInfo::TargetList(),
                                            std::move(direct_map_list));

  // 3) Set up unique aggregates (empty)
  std::vector<planner::AggregatePlan::AggTerm> agg_terms;

  // 4) Set up predicate (empty)
  expression::AbstractExpression* predicate = nullptr;

  // 5) Create output table schema
  auto data_table_schema = data_table.get()->GetSchema();
  std::vector<oid_t> set = {3, 0, 1, 2};
  std::vector<catalog::Column> columns;
  for (auto column_index : set) {
    columns.push_back(data_table_schema->GetColumn(column_index));
  }

  auto output_table_schema = new catalog::Schema(columns);

  // OK) Create the plan node
  planner::AggregatePlan node(proj_info, predicate, std::move(agg_terms),
                              std::move(group_by_columns), output_table_schema,
                              AGGREGATE_TYPE_HASH);

  // Create and set up executor
  auto txn2 = txn_manager.BeginTransaction();
  std::unique_ptr<executor::ExecutorContext> context(
      new executor::ExecutorContext(txn2));

  executor::AggregateExecutor executor(&node, context.get());
  MockExecutor child_executor;
  executor.AddChild(&child_executor);

  EXPECT_CALL(child_executor, DInit()).WillOnce(Return(true));

  EXPECT_CALL(child_executor, DExecute())
      .WillOnce(Return(true))
      .WillOnce(Return(true))
      .WillOnce(Return(false));

  EXPECT_CALL(child_executor, GetOutput())
      .WillOnce(Return(source_logical_tile1.release()))
      .WillOnce(Return(source_logical_tile2.release()));

  EXPECT_TRUE(executor.Init());

  EXPECT_TRUE(executor.Execute());
  txn_manager.CommitTransaction();

  /* Verify result */
  std::unique_ptr<executor::LogicalTile> result_tile(executor.GetOutput());
  EXPECT_TRUE(result_tile.get() != nullptr);

  for (auto tuple_id : *result_tile) {
    int colA = ValuePeeker::PeekAsInteger(result_tile->GetValue(tuple_id, 1));
    (void)colA;
  }
}