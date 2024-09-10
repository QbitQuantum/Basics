void
testMultipleFactoryInitilizations()
{
  Zorba* zorba = NULL;
  void* store = NULL;

  store = zorba::StoreManager::getStore();
  zorba = Zorba::getInstance(store);

  ItemFactory* factory = zorba->getItemFactory();
  factory->createString( "" );

  zorba->shutdown();
  zorba::StoreManager::shutdownStore(store);

  store = zorba::StoreManager::getStore();
  zorba = Zorba::getInstance(store);

  factory = zorba->getItemFactory();
  factory->createString( "" ); // <-- zorba crashes here

  zorba->shutdown();
  zorba::StoreManager::shutdownStore(store);
}