BENCHMARK_F(ProjectionScanBase, project_new_order_tpcc_district_mat) {
  //SELECT d_next_o_id, d_tax FROM district
  //materialized
  auto result = ps->execute()->getResultTable();

  MaterializingScan *ms = new MaterializingScan(false);
  ms->setEvent("NO_PAPI");
  ms->addInput(result);

  auto result_mat = ms->execute()->getResultTable();
}