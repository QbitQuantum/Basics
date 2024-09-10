// Do insert and create insert tuple log records
std::vector<ItemPointer> InsertTuples(
    storage::DataTable* table, const std::vector<storage::Tuple*>& tuples,
    bool committed) {
  std::vector<ItemPointer> locations;

  auto& txn_manager = concurrency::TransactionManagerFactory::GetInstance();

  for (auto tuple : tuples) {
    auto txn = txn_manager.BeginTransaction();
    ItemPointer location = table->InsertTuple(tuple);
    if (location.block == INVALID_OID) {
      txn->SetResult(Result::RESULT_FAILURE);
      LOG_ERROR("Insert failed");
      exit(EXIT_FAILURE);
    }

    txn->RecordInsert(location);

    locations.push_back(location);

    // Logging
    {
      auto& log_manager = logging::LogManager::GetInstance();

      if (log_manager.IsInLoggingMode()) {
        auto logger = log_manager.GetBackendLogger();
        auto record = logger->GetTupleRecord(
            LOGRECORD_TYPE_TUPLE_INSERT, txn->GetTransactionId(),
            table->GetOid(), location, INVALID_ITEMPOINTER, tuple,
            LOGGING_TESTS_DATABASE_OID);
        logger->Log(record);
      }
    }

    // commit or abort as required
    if (committed) {
      txn_manager.CommitTransaction();
    } else {
      txn_manager.AbortTransaction();
    }
  }

  return locations;
}