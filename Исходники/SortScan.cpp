BENCHMARK_F(SortScanBase, simple_sort_scan_string_mat_memcpy) {
  sc->setSortField(4);
  auto result = sc->execute()->getResultTable();

  MaterializingScan *ms = new MaterializingScan(true);
  ms->setEvent("NO_PAPI");
  ms->addInput(result);

  auto result_mat = ms->execute()->getResultTable();

}