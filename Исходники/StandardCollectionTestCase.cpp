void StandardCollectionTestCase::testScanWithMonitor()
{    
    string sConf = getFilePath("standard_collection", "standard_with_monitor.xml");
    CollectionPtr pCol = Collection::buildCollection(sConf);
    CPPUNIT_ASSERT(pCol.isNotNull());

    pCol->scan(false);
    Thread::sleep(1000);
    pCol->waitStop();

    checkIndex();
}