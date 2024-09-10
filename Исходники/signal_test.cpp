TEST(core_signal_test, clear_erases_all_slots) {
  Signal signal;

  signal.connect([](int) {});
  signal.connect([](int) {});
  ASSERT_EQ(2u, signal.size());

  signal.clear();
  ASSERT_EQ(0u, signal.size());
}