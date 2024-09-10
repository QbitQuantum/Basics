static void _testDeliveryRetry(CIMClient &client)
{
    try
    {
        cout << "Testing DeliveryRetry functionality..." << endl;
        _setup(client);
        _resetIdentfier(client);
        _testIndicationsWithListenerRunning(client);
#ifdef PEGASUS_ENABLE_DMTF_INDICATION_PROFILE_SUPPORT
        _testIndicationsWithListenerNotRunning(client);
        // Run again the same test, this time SequenceNumber should change
        cout << "Test listener with next sequence ID..." << endl;
        _testIndicationsWithListenerNotRunning(client);
        _testRetryAttemptsExceededIndications(client);
#endif
        _cleanup(client);
#ifdef PEGASUS_ENABLE_DMTF_INDICATION_PROFILE_SUPPORT
        // There should not be any queues after cleanup
        Array<CIMInstance> queues = _getDestinationQueues(client);
        PEGASUS_TEST_ASSERT(queues.size() == 0);
#endif
    }
    catch (Exception& e)
    {
        cerr << "Error: " << e.getMessage() << endl;
        exit(1);
    }
}