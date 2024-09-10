void NxNetRoute_Test::testParseLines()
{
    SCXHandle<NxNetRouteDependencies>deps(new NxNetRouteTestDependenciesWithLines());

    m_netrouteenum = new NxNetRouteEnumeration(deps);

    m_netrouteenum->Update(false);

    SCXHandle<NxNetRouteInstance>instance0(new NxNetRouteInstance());
    instance0 = m_netrouteenum->GetInstance(0);

    CPPUNIT_ASSERT_EQUAL(instance0->GetInterface() , L"eth3");
    CPPUNIT_ASSERT_EQUAL(instance0->GetDestination() , L"18.115.171.49");
    CPPUNIT_ASSERT_EQUAL(instance0->GetGateway() , L"168.234.255.255");
    CPPUNIT_ASSERT_EQUAL(instance0->GetGenMask() , L"5.23.128.0");
    CPPUNIT_ASSERT_EQUAL(instance0->GetFlags() , L"0003");
    CPPUNIT_ASSERT_EQUAL(instance0->GetRefCount() , L"a");
    CPPUNIT_ASSERT_EQUAL(instance0->GetUse() , L"b");
    CPPUNIT_ASSERT_EQUAL(instance0->GetMetric() , L"2");
    CPPUNIT_ASSERT_EQUAL(instance0->GetMtu(), L"x");
    CPPUNIT_ASSERT_EQUAL(instance0->GetWindow() ,L"y");
    CPPUNIT_ASSERT_EQUAL(instance0->GetIrtt() , L"z");

    SCXHandle<NxNetRouteInstance>instance1(new NxNetRouteInstance());
    instance1 = m_netrouteenum->GetInstance(1);

    CPPUNIT_ASSERT_EQUAL(instance1->GetInterface() , L"eth0");
    CPPUNIT_ASSERT_EQUAL(instance1->GetDestination() , L"0.128.59.152");
    CPPUNIT_ASSERT_EQUAL(instance1->GetGenMask() , L"0.252.255.255");
    CPPUNIT_ASSERT_EQUAL(instance1->GetGateway() , L"0.0.0.0");
    CPPUNIT_ASSERT_EQUAL(instance1->GetFlags() , L"0001");
    CPPUNIT_ASSERT_EQUAL(instance1->GetRefCount() , L"0");
    CPPUNIT_ASSERT_EQUAL(instance1->GetUse() , L"0");
    CPPUNIT_ASSERT_EQUAL(instance1->GetMetric() , L"1");
    CPPUNIT_ASSERT_EQUAL(instance1->GetWindow() ,L"0");
    CPPUNIT_ASSERT_EQUAL(instance1->GetIrtt() , L"0");
}