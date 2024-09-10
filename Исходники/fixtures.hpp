~OmniNamesFixture() {
  BOOST_TEST_MESSAGE("== Test teardown [BEGIN]: Stopping OmniNames ==");
  bf::remove_all(logdir);

  if (processNamingService) {
    try {
     processNamingService->terminate();
     processNamingService->wait();
    } catch (...) {
      BOOST_TEST_MESSAGE("== Problem while ending OmniNames ==");
    }
  }
  boost::this_thread::sleep(boost::posix_time::milliseconds(SLEEP_TIME));
  BOOST_TEST_MESSAGE("== Test teardown [END]: Stopping OmniNames ==");
}