/**
 * @brief Build a executor tree and execute it.
 * Use std::vector<common::Value> as params to make it more elegant for
 * networking
 * Before ExecutePlan, a node first receives value list, so we should pass
 * value list directly rather than passing Postgres's ParamListInfo
 * @return status of execution.
 */
peloton_status PlanExecutor::ExecutePlan(
    const planner::AbstractPlan *plan,
    const std::vector<common::Value> &params, std::vector<ResultType> &result,
    const std::vector<int> &result_format) {
  peloton_status p_status;

  if (plan == nullptr) return p_status;

  LOG_TRACE("PlanExecutor Start ");

  bool status;
  bool init_failure = false;
  bool single_statement_txn = false;

  auto &txn_manager = concurrency::TransactionManagerFactory::GetInstance();
  // auto txn = peloton::concurrency::current_txn;
  // This happens for single statement queries in PG
  // if (txn == nullptr) {
  single_statement_txn = true;
  auto txn = txn_manager.BeginTransaction();
  // }
  PL_ASSERT(txn);

  LOG_TRACE("Txn ID = %lu ", txn->GetTransactionId());
  LOG_TRACE("Building the executor tree");

  // Use const std::vector<common::Value> &params to make it more elegant for
  // network
  std::unique_ptr<executor::ExecutorContext> executor_context(
      BuildExecutorContext(params, txn));

  // Build the executor tree
  std::unique_ptr<executor::AbstractExecutor> executor_tree(
      BuildExecutorTree(nullptr, plan, executor_context.get()));

  LOG_TRACE("Initializing the executor tree");

  // Initialize the executor tree
  status = executor_tree->Init();

  // Abort and cleanup
  if (status == false) {
    init_failure = true;
    txn->SetResult(Result::RESULT_FAILURE);
    goto cleanup;
  }

  LOG_TRACE("Running the executor tree");
  result.clear();

  // Execute the tree until we get result tiles from root node
  while (status == true) {
    status = executor_tree->Execute();

    std::unique_ptr<executor::LogicalTile> logical_tile(
        executor_tree->GetOutput());
    // Some executors don't return logical tiles (e.g., Update).
    if (logical_tile.get() != nullptr) {
      LOG_TRACE("Final Answer: %s",
                logical_tile->GetInfo().c_str());  // Printing the answers
      std::unique_ptr<catalog::Schema> output_schema(
          logical_tile->GetPhysicalSchema());  // Physical schema of the tile
      std::vector<std::vector<std::string>> answer_tuples;
      answer_tuples =
          std::move(logical_tile->GetAllValuesAsStrings(result_format));

      // Construct the returned results
      for (auto &tuple : answer_tuples) {
        unsigned int col_index = 0;
        auto &schema_columns = output_schema->GetColumns();
        for (auto &column : schema_columns) {
          auto column_name = column.GetName();
          auto res = ResultType();
          PlanExecutor::copyFromTo(column_name, res.first);
          LOG_TRACE("column name: %s", column_name.c_str());
          PlanExecutor::copyFromTo(tuple[col_index++], res.second);
          if (tuple[col_index - 1].c_str() != nullptr) {
            LOG_TRACE("column content: %s", tuple[col_index - 1].c_str());
          }
          result.push_back(res);
        }
      }
    }
  }

  // Set the result
  p_status.m_processed = executor_context->num_processed;
  p_status.m_result_slots = nullptr;

// final cleanup
cleanup:

  LOG_TRACE("About to commit: single stmt: %d, init_failure: %d, status: %d",
            single_statement_txn, init_failure, txn->GetResult());

  // should we commit or abort ?
  if (single_statement_txn == true || init_failure == true) {
    auto status = txn->GetResult();
    switch (status) {
      case Result::RESULT_SUCCESS:
        // Commit
        LOG_TRACE("Commit Transaction");
        p_status.m_result = txn_manager.CommitTransaction(txn);
        break;

      case Result::RESULT_FAILURE:
      default:
        // Abort
        LOG_TRACE("Abort Transaction");
        p_status.m_result = txn_manager.AbortTransaction(txn);
    }
  }

  // clean up executor tree
  CleanExecutorTree(executor_tree.get());

  return p_status;
}