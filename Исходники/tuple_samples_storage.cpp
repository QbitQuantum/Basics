/**
 * AddSamplesTable - Add a samples table into the 'samples_db'.
 * The table name is generated by concatenating db_id and table_id with '_'.
 */
void TupleSamplesStorage::AddSamplesTable(
    storage::DataTable *data_table,
    std::vector<std::unique_ptr<storage::Tuple>> &sampled_tuples) {
  auto schema = data_table->GetSchema();
  auto schema_copy = catalog::Schema::CopySchema(schema);
  std::unique_ptr<catalog::Schema> schema_ptr(schema_copy);
  auto catalog = catalog::Catalog::GetInstance();
  bool is_catalog = false;
  std::string samples_table_name = GenerateSamplesTableName(
      data_table->GetDatabaseOid(), data_table->GetOid());

  auto &txn_manager = concurrency::TransactionManagerFactory::GetInstance();
  auto txn = txn_manager.BeginTransaction();
  catalog->CreateTable(std::string(SAMPLES_DB_NAME),
                       std::string(DEFAULT_SCHEMA_NAME), samples_table_name,
                       std::move(schema_ptr), txn, is_catalog);

  auto samples_table = catalog->GetTableWithName(
      std::string(SAMPLES_DB_NAME), std::string(DEFAULT_SCHEMA_NAME),
      samples_table_name, txn);

  for (auto &tuple : sampled_tuples) {
    InsertSampleTuple(samples_table, std::move(tuple), txn);
  }
  txn_manager.CommitTransaction(txn);
}