int
external_function(int argc, char* argv[]) 
{
  void* lStore = zorba::StoreManager::getStore();
  Zorba* lZorba = Zorba::getInstance(lStore);

  std::cout << "executing external_function_test_1" << std::endl;
  if (!external_function_test_1(lZorba))
  {
    return 1;
  }

  std::cout << "executing external_function_test_2" << std::endl;
  if (!external_function_test_2(lZorba))
  {
    return 2;
  }

  std::cout << "executing external_function_test_3" << std::endl;
  if (!external_function_test_3(lZorba))
  {
    return 3;
  }

  std::cout << "executing external_function_test_4" << std::endl;
  if (!external_function_test_4(lZorba))
  {
    return 4;
  }

  std::cout << "executing external_function_test_5" << std::endl;
  if (!external_function_test_5(lZorba))
  {
    return 4;
  }


  lZorba->shutdown();
  zorba::StoreManager::shutdownStore(lStore);
  return 0;
}