int 
xmldatamanager(int argc, char* argv[])
{
  void* lStore = zorba::StoreManager::getStore();
  Zorba* lZorba = Zorba::getInstance(lStore);
  XmlDataManager_t lDataManager = lZorba->getXmlDataManager();
  bool res = false;

  std::cout << "executing example 1" << std::endl;
  res = xmldatamanager_example_1(lZorba, lDataManager);
  if (!res) return 1;
  std::cout << std::endl;

  std::cout << "executing example 2" << std::endl;
  res = xmldatamanager_example_2(lZorba, lDataManager);
  if (!res) return 2;
  std::cout << std::endl;

  std::cout << "executing example 3" << std::endl;
  res = xmldatamanager_example_3(lZorba, lDataManager);
  if (!res) return 3;
  std::cout << std::endl;

  std::cout << "executing example 4" << std::endl;
  res = xmldatamanager_example_4(lZorba, lDataManager);
  if (!res) return 4;
  std::cout << std::endl;

  std::cout << "executing example 5" << std::endl;
  res = xmldatamanager_example_5(lZorba, lDataManager);
  if (!res) return 5;
  std::cout << std::endl;

  lZorba->shutdown();
  zorba::StoreManager::shutdownStore(lStore);
  return 0;
}