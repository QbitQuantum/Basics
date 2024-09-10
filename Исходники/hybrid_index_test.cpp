TEST_F(HybridIndexTests, HybridScanTest) {
  std::unique_ptr<storage::DataTable> hyadapt_table;
  CreateTable(hyadapt_table, false);
  LoadTable(hyadapt_table);

  std::vector<oid_t> key_attrs;

  auto tuple_schema = hyadapt_table->GetSchema();
  catalog::Schema *key_schema;
  index::IndexMetadata *index_metadata;
  bool unique;

  key_attrs = {0};
  key_schema = catalog::Schema::CopySchema(tuple_schema, key_attrs);
  key_schema->SetIndexedColumns(key_attrs);

  unique = true;

  index_metadata = new index::IndexMetadata(
      "primary_index", 123, INVALID_OID, INVALID_OID, IndexType::BWTREE,
      IndexConstraintType::PRIMARY_KEY, tuple_schema, key_schema, key_attrs,
      unique);

  std::shared_ptr<index::Index> pkey_index(
      index::IndexFactory::GetIndex(index_metadata));

  hyadapt_table->AddIndex(pkey_index);

  std::thread index_builder =
      std::thread(BuildIndex, pkey_index, hyadapt_table.get());

  for (size_t query_itr = 0; query_itr < query_count; query_itr++) {
    LaunchHybridScan(hyadapt_table);
  }

  index_builder.join();
}