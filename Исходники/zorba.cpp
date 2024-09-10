int
runQuery(const char* query)
{
  void* lStore = StoreManager::getStore();
  Zorba *lZorba = Zorba::getInstance(lStore);

  XQuery_t lQuery = lZorba->compileQuery(query);

  std::cout << lQuery << std::endl;

  lZorba->shutdown();
  StoreManager::shutdownStore(lStore);

  return 0;
}