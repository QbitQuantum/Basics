    ~SystemServicesDiscoveryTest()
    {
        discoveryProxy.reset();
        discoveryProxyBuilder.reset();
        runtime->deleteChannel();
        runtime->stopExternalCommunication();

        runtime->shutdown();
        test::util::resetAndWaitUntilDestroyed(runtime);
        test::util::resetAndWaitUntilDestroyed(mockMessageReceiverHttp);
        test::util::resetAndWaitUntilDestroyed(mockMessageReceiverMqtt);
        test::util::resetAndWaitUntilDestroyed(mockMessageSenderMqtt);

        // Delete persisted files
        std::remove(settingsFilename.c_str());
        std::remove(ClusterControllerSettings::
                            DEFAULT_LOCAL_CAPABILITIES_DIRECTORY_PERSISTENCE_FILENAME().c_str());
        std::remove(LibjoynrSettings::DEFAULT_MESSAGE_ROUTER_PERSISTENCE_FILENAME().c_str());
        std::remove(LibjoynrSettings::DEFAULT_SUBSCRIPTIONREQUEST_PERSISTENCE_FILENAME().c_str());
        std::remove(LibjoynrSettings::DEFAULT_PARTICIPANT_IDS_PERSISTENCE_FILENAME().c_str());
    }