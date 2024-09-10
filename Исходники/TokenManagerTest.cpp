        // Test which verifies distribution of tokens and starting/stopping
        // token trackers.
        TEST(TokenManager, WithTrackersTest)
        {
            static const unsigned c_threadCount = 16;
            // static const unsigned c_testDuration = 5 * 1000; TODO

            TokenManager tokenManager;

            std::unique_ptr<Logging::ILogger> logger(new Logging::ConsoleLogger());
            Logging::RegisterLogger(logger.get());

            TokenThreadHolder tokenDistributor(c_threadCount, tokenManager);

            std::atomic<bool> isRunning(true);

            // Add a thread that periodically starts tracking tokens.
            TokenTrackerThread * trackerThread = new TokenTrackerThread(tokenManager, isRunning);
            tokenDistributor.AddThread(trackerThread);

            tokenDistributor.Start();

            // DESIGN NOTE: this test used to have random sleeps in the methods
            // and a 5 second sleep here. All the sleeps were reduced because we
            // still get some randomness in ordering and this test shouldn't
            // take 5+ seconds to run. However, it's possible that's too extreme
            // and we should larger sleeps.
            // This test, with the reduced sleeps, found a threading bug that
            // was triggered every 10s to 100s of executions. With the old version
            // of this test, that would have taken an unreasonably long time, so
            // even if this test is sacrificing some "randomness" by having
            // a shorter duration, I believe it makes up for it by the increased
            // number of executions possible per unit time, and that we should
            // really have a seperate test that's designed for overnight use
            // that can be more comprehensive.
            // 5 is an arbitrary number that's > 2x 2.
            std::this_thread::sleep_for(std::chrono::milliseconds(5));

            isRunning = false;
            tokenDistributor.Stop();

            {
                const Token lastToken = tokenManager.RequestToken();

                // Sanity check that some tokens have actually been issued.
                ASSERT_TRUE(lastToken.GetSerialNumber() > 0);

                LogB(Logging::Info,
                     "TokenManagerWithTrackersTest",
                     "Last serial num: %u",
                     lastToken.GetSerialNumber());
            }
        }