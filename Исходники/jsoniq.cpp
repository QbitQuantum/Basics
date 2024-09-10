int 
jsoniq(int argc, char* argv[])
{
  void* lStore = StoreManager::getStore();
  Zorba *lZorba = Zorba::getInstance(lStore);

  bool res = false;

  try {
    std::cout << "executing jsoniq example 1" << std::endl;
    res = jsoniq_test::example_1(lZorba);
    if (!res) return 1;
    std::cout << std::endl;

    std::cout << "executing jsoniq example 2" << std::endl;
    res = jsoniq_test::example_2(lZorba);
    if (!res) return 1;
    std::cout << std::endl;

    std::cout << "executing jsoniq example 3" << std::endl;
    res = jsoniq_test::example_3(lZorba);
    if (!res) return 1;
    std::cout << std::endl;

    std::cout << "executing jsoniq example 4" << std::endl;
    res = jsoniq_test::example_4(lZorba);
    if (!res) return 1;
    std::cout << std::endl;

    std::cout << "executing jsoniq example 5" << std::endl;
    res = jsoniq_test::example_5(lZorba);
    if (!res) return 1;
    std::cout << std::endl;

    std::cout << "executing jsoniq example 6" << std::endl;
    res = jsoniq_test::example_6(lZorba);
    if (!res) return 1;
    std::cout << std::endl;

    std::cout << "executing jsoniq example 9" << std::endl;
    res = jsoniq_test::example_7(lZorba);
    if (!res) return 1;
    std::cout << std::endl;
  }
  catch (ZorbaException& e) {
    std::cout << "ZorbaException raised: " << e.what() << std::endl;
    return 2;
  }

  lZorba->shutdown();
  StoreManager::shutdownStore(lStore);
  return 0;
}