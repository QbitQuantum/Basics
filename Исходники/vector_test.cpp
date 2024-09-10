void VectorTest::test_calculate_sum(void) {
  message += "test_calculate_sum\n";

  Vector<int> v;

  assert_true(v.calculate_sum() == 0, LOG);

  v.set(2);
  v.initialize(1);

  assert_true(v.calculate_sum() == 2, LOG);
}