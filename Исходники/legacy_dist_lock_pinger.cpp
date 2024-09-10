    Status LegacyDistLockPinger::startPing(const DistributedLock& lock,
                                           stdx::chrono::milliseconds sleepTime) {
        const ConnectionString& conn = lock.getRemoteConnection();
        const string& processId = lock.getProcessId();
        string pingID = pingThreadId(conn, processId);

        {
            // Make sure we don't start multiple threads for a process id.
            boost::lock_guard<boost::mutex> lk(_mutex);

            if (_inShutdown) {
                return Status(ErrorCodes::ShutdownInProgress,
                              "shutting down, will not start ping");
            }

            // Ignore if we already have a pinging thread for this process.
            if (_seen.count(pingID) > 0) {
                return Status::OK();
            }

            // Check the config server clock skew.
            if (lock.isRemoteTimeSkewed()) {
                return Status(ErrorCodes::DistributedClockSkewed,
                              str::stream() << "clock skew of the cluster " << conn.toString()
                                            << " is too far out of bounds "
                                            << "to allow distributed locking.");
            }
        }

        {
            boost::lock_guard<boost::mutex> lk(_mutex);
            boost::thread thread(stdx::bind(&LegacyDistLockPinger::distLockPingThread,
                                            this,
                                            conn,
                                            getJSTimeVirtualThreadSkew(),
                                            processId,
                                            sleepTime));
            _pingThreads.insert(std::make_pair(pingID, std::move(thread)));

            _seen.insert(pingID);
        }

        return Status::OK();
    }