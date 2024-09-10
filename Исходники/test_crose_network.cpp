TEST(TestRoseNetwork, TestConnectIp) {
  //	std::mutex mutex;
  //	std::condition_variable cv;
  //	bool done = false;

  CRoseServer network;
  EXPECT_EQ(true,
            network.Init("63.117.14.24",
                         80));  // We are going to connect to google's website
  EXPECT_NO_FATAL_FAILURE(network.Connect());
  //	EXPECT_CALL( network, OnConnect() )
  //                                .WillOnce(testing::Invoke([&]()->int {
  //                                            std::lock_guard<std::mutex>
  //                                            lock(mutex);
  //                                            done = true;
  //                                            cv.notify_all();
  //                                            return 1; }));

  //	EXPECT_CALL( network, OnConnected() )
  //				.WillOnce(testing::Invoke([&]()->int {
  //				            std::lock_guard<std::mutex>
  //lock(mutex);
  //				            done = true;
  //				            cv.notify_all();
  //				            return 1; }));

  //	std::unique_lock<std::mutex> lock(mutex);
  //	std::unique_lock<std::mutex> lock2(mutex2);
  //	EXPECT_TRUE(cv.wait_for(lock,
  //					std::chrono::seconds(1),
  //					[&done] { return done; })
  //					);
  //	EXPECT_TRUE(cv.wait_for(lock,
  //                                        std::chrono::seconds(1),
  //                                        [&done] { return done; })
  //                                        );
  //	std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_NO_FATAL_FAILURE(network.Shutdown());
}