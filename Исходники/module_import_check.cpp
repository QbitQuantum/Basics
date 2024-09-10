int module_import_check(int argc, char* argv[])
{
  void* lStore = zorba::StoreManager::getStore();
  Zorba *lZorba = Zorba::getInstance(lStore);

  bool res = false;

  res = example1(lZorba);
  if (!res)
    return 1;

  lZorba->shutdown();
  zorba::StoreManager::shutdownStore(lStore);
  return 0;
}