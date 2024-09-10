void test_initDriverDataDispatcherList_add_too_much_dispatchers(void) {
    init_driverDataDispatcherList();
    TEST_ASSERT_FALSE(isThereAnyError());
    TEST_ASSERT_EQUAL(0, getDriverDataDispatcherCount());

    // Add a first dispatcher
    DriverDataDispatcher* dispacher = addLocalDriverDataDispatcher();
    TEST_ASSERT_FALSE(isThereAnyError());
    TEST_ASSERT_EQUAL(1, getDriverDataDispatcherCount());
    // TEST_ASSERT_EQUAL(dispacher, getDriverDataDispatcherByIndex(0));
    
    // Add a second dispatcher
    dispacher = addLocalDriverDataDispatcher();
    TEST_ASSERT_FALSE(isThereAnyError());
    TEST_ASSERT_EQUAL(2, getDriverDataDispatcherCount());
    TEST_ASSERT_EQUAL(dispacher, getDriverDataDispatcherByIndex(1));

    dispacher = addLocalDriverDataDispatcher();
    TEST_ASSERT_EQUAL(TOO_MUCH_DRIVER_DATA_DISPATCHER, getLastError());
}