void CCollectionTest::deserializeStreamClient() {
	string serialisation = "Küche\tkitchenclient\tlocal\t46635\townerSession\tdisabled\n";

	CStreamClientItem *scItem = new CStreamClientItem(m_root, serialisation, 0);

	CPPUNIT_ASSERT( scItem->getServiceName().compare("Küche") == 0);
	CPPUNIT_ASSERT( scItem->getHostName().compare("kitchenclient") == 0);
	CPPUNIT_ASSERT( scItem->getDomainName().compare("local") == 0);
	CPPUNIT_ASSERT( scItem->getPort() == 46635);
	CPPUNIT_ASSERT( scItem->getOwnerSessionName().compare("ownerSession") == 0);
	CPPUNIT_ASSERT( scItem->isEnabled() == false);
}