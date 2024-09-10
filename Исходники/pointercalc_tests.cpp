TEST_F(PointerCalcTests, rename_field) {
  auto t = createTable(table_7);
  auto res = PointerCalculator::create(t);
  ASSERT_EQ(t->nameOfColumn(0), res->nameOfColumn(0));
  res->rename(0, "NoMobile");
  ASSERT_EQ("NoMobile", res->nameOfColumn(0));
}