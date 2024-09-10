        void runThread(ConnectionString& hostConn, unsigned threadId, unsigned seed,
                       BSONObj& cmdObj, BSONObjBuilder& result) {

            stringstream ss;
            ss << "thread-" << threadId;
            setThreadName(ss.str().c_str());

            // Lock name
            string lockName = string_field(cmdObj, "lockName", this->name + "_lock");

            // Range of clock skew in diff threads
            int skewRange = (int) number_field(cmdObj, "skewRange", 1);

            // How long to wait with the lock
            int threadWait = (int) number_field(cmdObj, "threadWait", 30);
            if(threadWait <= 0) threadWait = 1;

            // Max amount of time (ms) a thread waits before checking the lock again
            int threadSleep = (int) number_field(cmdObj, "threadSleep", 30);
            if(threadSleep <= 0) threadSleep = 1;

            // How long until the lock is forced in ms, only compared locally
            unsigned long long takeoverMS = (unsigned long long) number_field(cmdObj, "takeoverMS", 0);

            // Whether or not we should hang some threads
            int hangThreads = (int) number_field(cmdObj, "hangThreads", 0);


            boost::mt19937 gen((boost::mt19937::result_type) seed);

            boost::variate_generator<boost::mt19937&, boost::uniform_int<> > randomSkew(gen, boost::uniform_int<>(0, skewRange));
            boost::variate_generator<boost::mt19937&, boost::uniform_int<> > randomWait(gen, boost::uniform_int<>(1, threadWait));
            boost::variate_generator<boost::mt19937&, boost::uniform_int<> > randomSleep(gen, boost::uniform_int<>(1, threadSleep));
            boost::variate_generator<boost::mt19937&, boost::uniform_int<> > randomNewLock(gen, boost::uniform_int<>(0, 3));


            int skew = 0;
            if (!lock.get()) {

                // Pick a skew, but the first two threads skew the whole range
                if(threadId == 0)
                    skew = -skewRange / 2;
                else if(threadId == 1)
                    skew = skewRange / 2;
                else skew = randomSkew() - (skewRange / 2);

                // Skew this thread
                jsTimeVirtualThreadSkew( skew );

                log() << "Initializing lock with skew of " << skew << " for thread " << threadId << endl;

                lock.reset(new DistributedLock(hostConn, lockName, takeoverMS, true ));

                log() << "Skewed time " << jsTime() << "  for thread " << threadId << endl
                      << "  max wait (with lock: " << threadWait << ", after lock: " << threadSleep << ")" << endl
                      << "  takeover in " << takeoverMS << "(ms remote)" << endl;

            }

            DistributedLock* myLock = lock.get();

            bool errors = false;
            BSONObj lockObj;
            while (keepGoing.loadRelaxed()) {
                Status pingStatus = _pinger.startPing(*myLock,
                        stdx::chrono::milliseconds(takeoverMS / LOCK_SKEW_FACTOR));

                if (!pingStatus.isOK()) {
                    log() << "**** Not good for pinging: " << pingStatus;
                    break;
                }

                try {

                    if (myLock->lock_try("Testing distributed lock with skew.", &lockObj)) {

                        log() << "**** Locked for thread " << threadId << " with ts " << lockObj["ts"] << endl;

                        if (count.loadRelaxed() % 3 == 1 &&
                                myLock->lock_try( "Testing lock non-re-entry.")) {
                            errors = true;
                            log() << "**** !Invalid lock re-entry" << endl;
                            break;
                        }

                        int before = count.addAndFetch(1);
                        int sleep = randomWait();
                        sleepmillis(sleep);
                        int after = count.loadRelaxed();

                        if(after != before) {
                            errors = true;
                            log() << "**** !Bad increment while sleeping with lock for: " << sleep << "ms" << endl;
                            break;
                        }

                        // Unlock only half the time...
                        if(hangThreads == 0 || threadId % hangThreads != 0) {
                            log() << "**** Unlocking for thread " << threadId << " with ts " << lockObj["ts"] << endl;
                            myLock->unlock(lockObj["ts"].OID());
                        }
                        else {
                            log() << "**** Not unlocking for thread " << threadId << endl;
                            _pinger.stopPing(myLock->getRemoteConnection(), myLock->getProcessId());
                            // We're simulating a crashed process...
                            break;
                        }
                    }

                }
                catch( const DBException& ex ) {
                    log() << "*** !Could not try distributed lock." << causedBy( ex ) << endl;
                    break;
                }

                // Create a new lock 1/3 of the time
                if( randomNewLock() > 1 ){
                    lock.reset(new DistributedLock( hostConn, lockName, takeoverMS, true ));
                    myLock = lock.get();
                }

                sleepmillis(randomSleep());
            }

            result << "errors" << errors
                   << "skew" << skew
                   << "takeover" << (long long) takeoverMS
                   << "localTimeout" << (takeoverMS > 0);

        }