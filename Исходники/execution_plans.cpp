int
execution_plans(int argc, char* argv[])
{
  void* lStore = zorba::StoreManager::getStore();
  Zorba *lZorba = Zorba::getInstance(lStore);

  bool res = false;

  std::cout << "executing example 1" << std::endl;
  res = execution_plan_example_1(lZorba);
  if (!res) return 1; 
  std::cout << std::endl;

  std::cout << "executing example 2" << std::endl;
  res = execution_plan_example_2(lZorba);
  if (!res) return 2; 
  std::cout << std::endl;

  std::cout << "executing example 3" << std::endl;
  res = execution_plan_example_3(lZorba);
  if (!res) return 3; 
  std::cout << std::endl;

  lZorba->shutdown();
  zorba::StoreManager::shutdownStore(lStore);
  return 0;
}