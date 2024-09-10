TEST(iterator, sync_rownum) {

  Connection cnx;
  cnx.connect();

  int32_t actual = 0;

  auto &result = cnx.execute("SELECT generate_series(1, 3)");
  for (auto &row: result) {
    actual += row.num();
  }

  // rownum should reset for the next query
  auto &result2 = cnx.execute("SELECT generate_series(1, 3)");
  for (auto &row: result2) {
    actual += row.num();
  }

  EXPECT_EQ(actual, 12);

}