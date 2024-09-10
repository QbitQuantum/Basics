 ~JoynrClusterControllerRuntimeTest()
 {
     if (runtime) {
         runtime->deleteChannel();
         runtime->stopExternalCommunication();
         runtime->shutdown();
         test::util::resetAndWaitUntilDestroyed(runtime);
     }
     test::util::removeAllCreatedSettingsAndPersistencyFiles();
     EXPECT_TRUE(Mock::VerifyAndClearExpectations(mockHttpMessageReceiver.get()));
     EXPECT_TRUE(Mock::VerifyAndClearExpectations(mockMqttMessageReceiver.get()));
 }