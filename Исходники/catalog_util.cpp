void DeleteTuple(storage::DataTable *table, oid_t id){
	  auto txn = peloton::concurrency::current_txn;
	  std::unique_ptr<executor::ExecutorContext> context(
	      new executor::ExecutorContext(txn));


	  LOG_INFO("Removing tuple with id %d from table %s", (int)id, table->GetName().c_str());
	  LOG_INFO("Transaction ID: %d", (int)txn->GetTransactionId());
	  // Delete
	  planner::DeletePlan delete_node(table, false);
	  executor::DeleteExecutor delete_executor(&delete_node, context.get());

	  // Predicate
	  // WHERE id_in_table = id
	  expression::TupleValueExpression *tup_val_exp =
	      new expression::TupleValueExpression(VALUE_TYPE_INTEGER, 0, 0);
	  expression::ConstantValueExpression *const_val_exp =
	      new expression::ConstantValueExpression(
	          ValueFactory::GetIntegerValue(id));
	  auto predicate = new expression::ComparisonExpression<expression::CmpEq>(
			  EXPRESSION_TYPE_COMPARE_EQUAL, tup_val_exp, const_val_exp);

	  // Seq scan
	  std::vector<oid_t> column_ids = {0, 1};
	  std::unique_ptr<planner::SeqScanPlan> seq_scan_node(
	      new planner::SeqScanPlan(table, predicate, column_ids));
	  executor::SeqScanExecutor seq_scan_executor(seq_scan_node.get(),
	                                              context.get());

	  // Parent-Child relationship
	  delete_node.AddChild(std::move(seq_scan_node));
	  delete_executor.AddChild(&seq_scan_executor);
	  delete_executor.Init();
	  delete_executor.Execute();

}