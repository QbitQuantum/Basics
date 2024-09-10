void ExecuteJoinTest(PlanNodeType join_algorithm, PelotonJoinType join_type, oid_t join_test_type) {
  //===--------------------------------------------------------------------===//
  // Mock table scan executors
  //===--------------------------------------------------------------------===//

  MockExecutor left_table_scan_executor, right_table_scan_executor;

  // Create a table and wrap it in logical tile
  size_t tile_group_size = TESTS_TUPLES_PER_TILEGROUP;
  size_t left_table_tile_group_count = 3;
  size_t right_table_tile_group_count = 2;

  auto &txn_manager = concurrency::TransactionManager::GetInstance();
  auto txn = txn_manager.BeginTransaction();
  auto txn_id = txn->GetTransactionId();

  // Left table has 3 tile groups
  std::unique_ptr<storage::DataTable> left_table(
      ExecutorTestsUtil::CreateTable(tile_group_size));
  ExecutorTestsUtil::PopulateTable(
      txn, left_table.get(),
      tile_group_size * left_table_tile_group_count, false,
      false, false);

  // Right table has 2 tile groups
  std::unique_ptr<storage::DataTable> right_table(
      ExecutorTestsUtil::CreateTable(tile_group_size));
  ExecutorTestsUtil::PopulateTable(
      txn, right_table.get(),
      tile_group_size * right_table_tile_group_count, false,
      false, false);

  txn_manager.CommitTransaction();

  //std::cout << (*left_table);

  //std::cout << (*right_table);

  // Wrap the input tables with logical tiles
  std::unique_ptr<executor::LogicalTile> left_table_logical_tile1(
      executor::LogicalTileFactory::WrapTileGroup(left_table->GetTileGroup(0),
                                                  txn_id));
  std::unique_ptr<executor::LogicalTile> left_table_logical_tile2(
      executor::LogicalTileFactory::WrapTileGroup(left_table->GetTileGroup(1),
                                                  txn_id));
  std::unique_ptr<executor::LogicalTile> left_table_logical_tile3(
      executor::LogicalTileFactory::WrapTileGroup(left_table->GetTileGroup(2),
                                                  txn_id));

  std::unique_ptr<executor::LogicalTile> right_table_logical_tile1(
      executor::LogicalTileFactory::WrapTileGroup(
          right_table->GetTileGroup(0),
          txn_id));

  std::unique_ptr<executor::LogicalTile> right_table_logical_tile2(
      executor::LogicalTileFactory::WrapTileGroup(
          right_table->GetTileGroup(1),
          txn_id));

  // Left scan executor returns logical tiles from the left table

  EXPECT_CALL(left_table_scan_executor, DInit()).WillOnce(Return(true));

  //===--------------------------------------------------------------------===//
  // Setup left table
  //===--------------------------------------------------------------------===//

  if(join_test_type == BASIC_TEST) {

    EXPECT_CALL(left_table_scan_executor, DExecute())
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(true))
        .WillOnce(Return(false));

    EXPECT_CALL(left_table_scan_executor, GetOutput())
        .WillOnce(Return(left_table_logical_tile1.release()))
        .WillOnce(Return(left_table_logical_tile2.release()))
        .WillOnce(Return(left_table_logical_tile3.release()));

  }

  // Right scan executor returns logical tiles from the right table

  EXPECT_CALL(right_table_scan_executor, DInit()).WillOnce(Return(true));

  //===--------------------------------------------------------------------===//
  // Setup right table
  //===--------------------------------------------------------------------===//

  if(join_test_type == BASIC_TEST) {

    EXPECT_CALL(right_table_scan_executor, DExecute())
         .WillOnce(Return(true))
         .WillOnce(Return(true))
         .WillOnce(Return(false));

     EXPECT_CALL(right_table_scan_executor, GetOutput())
         .WillOnce(Return(right_table_logical_tile1.release()))
         .WillOnce(Return(right_table_logical_tile2.release()));

  }

  //===--------------------------------------------------------------------===//
  // Setup join plan nodes and executors and run them
  //===--------------------------------------------------------------------===//

  oid_t result_tuple_count = 0;
  oid_t tuples_with_null = 0;
  auto projection = JoinTestsUtil::CreateProjection();

  // Construct predicate
  expression::AbstractExpression *predicate =
      JoinTestsUtil::CreateJoinPredicate();

  // Differ based on join algorithm
  switch (join_algorithm) {
    case PLAN_NODE_TYPE_NESTLOOP: {
      // Create nested loop join plan node.
      planner::NestedLoopJoinPlan nested_loop_join_node(join_type, predicate,
                                                        projection);

      // Run the nested loop join executor
      executor::NestedLoopJoinExecutor nested_loop_join_executor(
          &nested_loop_join_node, nullptr);

      // Construct the executor tree
      nested_loop_join_executor.AddChild(&left_table_scan_executor);
      nested_loop_join_executor.AddChild(&right_table_scan_executor);

      // Run the nested loop join executor
      EXPECT_TRUE(nested_loop_join_executor.Init());
      while (nested_loop_join_executor.Execute() == true) {
        std::unique_ptr<executor::LogicalTile> result_logical_tile(
            nested_loop_join_executor.GetOutput());

        if (result_logical_tile != nullptr) {
          result_tuple_count += result_logical_tile->GetTupleCount();
          tuples_with_null +=
              CountTuplesWithNullFields(result_logical_tile.get());
          //std::cout << (*result_logical_tile);
        }
      }

    } break;

    case PLAN_NODE_TYPE_MERGEJOIN: {
      // Create join clauses
      std::vector<planner::MergeJoinPlan::JoinClause> join_clauses;
      join_clauses = CreateJoinClauses();

      // Create merge join plan node
      planner::MergeJoinPlan merge_join_node(join_type, predicate, projection,
                                             join_clauses);

      // Construct the merge join executor
      executor::MergeJoinExecutor merge_join_executor(&merge_join_node,
                                                      nullptr);

      // Construct the executor tree
      merge_join_executor.AddChild(&left_table_scan_executor);
      merge_join_executor.AddChild(&right_table_scan_executor);

      // Run the merge join executor
      EXPECT_TRUE(merge_join_executor.Init());
      while (merge_join_executor.Execute() == true) {
        std::unique_ptr<executor::LogicalTile> result_logical_tile(
            merge_join_executor.GetOutput());

        if (result_logical_tile != nullptr) {
          result_tuple_count += result_logical_tile->GetTupleCount();
          tuples_with_null +=
              CountTuplesWithNullFields(result_logical_tile.get());
          //std::cout << (*result_logical_tile);
        }
      }

    } break;

    case PLAN_NODE_TYPE_HASHJOIN: {
      // Create hash plan node
      expression::AbstractExpression *right_table_attr_1 =
          new expression::TupleValueExpression(1, 1);

      std::vector<std::unique_ptr<const expression::AbstractExpression> >
          hash_keys;
      hash_keys.emplace_back(right_table_attr_1);

      // Create hash plan node
      planner::HashPlan hash_plan_node(hash_keys);

      // Construct the hash executor
      executor::HashExecutor hash_executor(&hash_plan_node, nullptr);

      // Create hash join plan node.
      planner::HashJoinPlan hash_join_plan_node(join_type, predicate,
                                                projection);

      // Construct the hash join executor
      executor::HashJoinExecutor hash_join_executor(&hash_join_plan_node,
                                                    nullptr);

      // Construct the executor tree
      hash_join_executor.AddChild(&left_table_scan_executor);
      hash_join_executor.AddChild(&hash_executor);

      hash_executor.AddChild(&right_table_scan_executor);

      // Run the hash_join_executor
      EXPECT_TRUE(hash_join_executor.Init());
      while (hash_join_executor.Execute() == true) {
        std::unique_ptr<executor::LogicalTile> result_logical_tile(
            hash_join_executor.GetOutput());

        if (result_logical_tile != nullptr) {
          result_tuple_count += result_logical_tile->GetTupleCount();
          tuples_with_null +=
              CountTuplesWithNullFields(result_logical_tile.get());
          // std::cout << (*result_logical_tile);
        }
      }

    } break;

    default:
      throw Exception("Unsupported join algorithm : " +
                      std::to_string(join_algorithm));
      break;
  }

  //===--------------------------------------------------------------------===//
  // Execute test
  //===--------------------------------------------------------------------===//

  if(join_test_type == BASIC_TEST) {

    // Check output
    switch (join_type) {
      case JOIN_TYPE_INNER:
        EXPECT_EQ(result_tuple_count, 10);
        EXPECT_EQ(tuples_with_null, 0);
        break;

      case JOIN_TYPE_LEFT:
        EXPECT_EQ(result_tuple_count, 15);
        EXPECT_EQ(tuples_with_null, 5);
        break;

      case JOIN_TYPE_RIGHT:
        EXPECT_EQ(result_tuple_count, 10);
        EXPECT_EQ(tuples_with_null, 0);
        break;

      case JOIN_TYPE_OUTER:
        EXPECT_EQ(result_tuple_count, 15);
        EXPECT_EQ(tuples_with_null, 5);
        break;

      default:
        throw Exception("Unsupported join type : " + std::to_string(join_type));
        break;
    }

  }

}