	void unresolveIpToName()
	{
		ip.setIp("133.0.0.1");
		CPPUNIT_ASSERT_THROW(ip.getHostname(),
							 NotAddressResolveException);
	}