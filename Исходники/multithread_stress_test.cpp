int
multithread_stress_test(int argc, char* argv[])
{
  simplestore::SimpleStore* lStore = StoreManager::getStore();
  Zorba*                    lZorba = Zorba::getInstance(StoreManager::getStore());
  bool                      res = false;

  std::cout << std::endl  << "executing multithread test 1 : ";
  res = multithread_stress_example_1(lZorba);
  if (!res) {
    std::cout << "Failed" << std::endl;
    lZorba->shutdown();
    StoreManager::shutdownStore(lStore);
    return 1;
  }
  else std::cout << "Passed" << std::endl;

  lZorba->shutdown();
  StoreManager::shutdownStore(lStore);
  return 0;
}