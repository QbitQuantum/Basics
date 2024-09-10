int sax2( int argc, char * argv[] )
{
  // create a SAX content handler that prints all events to standard out
  XMLSerializer lContentHandler( std::cout );

  void* lStore = zorba::StoreManager::getStore();

  // initialize the Zorba engine and get a pointer to it
  Zorba* lZorba = Zorba::getInstance(lStore);

  try 
  {
    // compile a query
    XQuery_t lQuery = lZorba->compileQuery("<a xmlns:f=\"foo\" xmlns=\"http://zorba.io/defaultns\"> text a text a <b xmlns:ns1=\"http://zorba.io/usecase1\" attr1=\"value1\" attr2=\"value2\"> text b </b><f:bar>foo</f:bar><foo /><bar /><b><![CDATA[ foo ]]></b></a>");

    // register the content handler created above
    lQuery->registerSAXHandler( &lContentHandler );

    // execute the query and call according SAX callbacks 
    // i.e. equivalent to serializing to xml and parsing using SAX).
    lQuery->executeSAX();
  }
  catch ( ZorbaException &e ) 
  {
    std::cerr << e << std::endl;
  }

  lZorba->shutdown();
  zorba::StoreManager::shutdownStore(lStore);
  return 0;
}