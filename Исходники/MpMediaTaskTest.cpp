    void testCreators()
    {
        MpMediaTask* pMediaTask = 0;
        OsStatus     res;

        int          numFramesAlready;

        // Call getMediaTask() which causes the task to get instantiated
        pMediaTask = MpMediaTask::getMediaTask(10);
        CPPUNIT_ASSERT(pMediaTask != NULL);

        // Check the initial state of the MpMediaTask object
 // ****************************************************************************
 // **** This is NOT THE INITIAL STATE UNLESS THE ABOVE CALL to getMediaTask()
 // **** is the very first call to that function.  The problem with these
 // **** tests is that they were meant to be run separately, but that is not
 // **** the case with our self-starting singleton tasks.  This one has been
 // **** around the track a few times already, we get whatever we get.
 // ****************************************************************************
        // Not anymore... CPPUNIT_ASSERT(pMediaTask->getDebugMode() == FALSE);
        // Good luck with the rest!
        CPPUNIT_ASSERT(pMediaTask->getFocus() == NULL);
        // Not anymore... CPPUNIT_ASSERT_EQUAL(0, pMediaTask->getLimitExceededCnt());
        CPPUNIT_ASSERT(pMediaTask->getTimeLimit() == MpMediaTask::DEF_TIME_LIMIT_USECS);
        CPPUNIT_ASSERT(pMediaTask->getWaitTimeout() == MpMediaTask::DEF_SEM_WAIT_MSECS);
        // Not anymore... CPPUNIT_ASSERT_EQUAL(0, pMediaTask->getWaitTimeoutCnt());
        CPPUNIT_ASSERT_EQUAL(0, pMediaTask->numManagedFlowGraphs());
        // Not anymore... CPPUNIT_ASSERT_EQUAL(0, pMediaTask->numProcessedFrames());
        numFramesAlready = pMediaTask->numProcessedFrames();
        CPPUNIT_ASSERT_EQUAL(0, pMediaTask->numStartedFlowGraphs());

        // Verify that the task is actually running by:
        //   enabling debug mode
        //   calling signalFrameStart()
        //   checking the processed frame count
        res = pMediaTask->setDebug(TRUE);
        CPPUNIT_ASSERT(res == OS_SUCCESS);

        res = MpMediaTask::signalFrameStart();  // send a signal to the task
        CPPUNIT_ASSERT(res == OS_SUCCESS);      // and give it a chance to run
        OsTask::delay(20);

        // Not anymore... CPPUNIT_ASSERT_EQUAL(1, pMediaTask->numProcessedFrames());
        CPPUNIT_ASSERT_EQUAL((numFramesAlready+1), pMediaTask->numProcessedFrames());
    }