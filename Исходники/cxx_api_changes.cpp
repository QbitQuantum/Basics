int
cxx_api_changes (int argc, char* argv[])
{
  void* lStore = zorba::StoreManager::getStore();
  Zorba* lZorba = Zorba::getInstance(lStore);

  std::cout << "executing cxx_api_changes_test1" << std::endl;
  if (!cxx_api_changes_test1(lZorba))
  {
    return 1;
  }

  std::cout << "executing cxx_api_changes_test2" << std::endl;
  if (!cxx_api_changes_test2(lZorba))
  {
    return 2;
  }

  std::cout << "executing cxx_api_changes_test3" << std::endl;
  if (!cxx_api_changes_test3(lZorba))
  {
    return 3;
  }

  std::cout << "executing cxx_api_changes_test4" << std::endl;
  if (!cxx_api_changes_test4(lZorba))
  {
    return 4;
  }

  std::cout << "executing cxx_api_changes_test5" << std::endl;
  if (!cxx_api_changes_test5(lZorba))
  {
    return 5;
  }

  std::cout << "executing cxx_api_changes_test6" << std::endl;
  if (!cxx_api_changes_test6(lZorba))
  {
    return 6;
  }

  lZorba->shutdown();
  zorba::StoreManager::shutdownStore(lStore);
  return 0;
}