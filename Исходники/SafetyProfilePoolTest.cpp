// Malloc should return pointer
void test_malloc() {
  SafetyProfilePool pool;
  pool.configure_pool(1024, sizeof(void*));
  TEST_CHECK(pool.malloc(24));
}