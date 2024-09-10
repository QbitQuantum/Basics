void doProcess(unsigned int port, unsigned int num) {
    Thread *threads = new Thread[num];
    RequestProcessor *runnables = new RequestProcessor [num];
    assert(threads);
    assert(runnables);
    for (long i=0; i<num; i++) {
        ANET_LOG(DEBUG, "Starting thread(%d)", i);
        threads[i].start(&runnables[i], (void*)i);
    }

    Transport transport;
//    transport.start(); //using multithreads mode of anet
    DefaultPacketFactory factory;
    DefaultPacketStreamer streamer(&factory);
    MyServerAdapter serverAdapter;
    stringstream ss;
    char hostname[1024];
    if (gethostname(hostname, 1024) != 0) {
        ANET_LOG(ERROR, "Failed to get hostname");
        exit(-1);
    }
    ss << "tcp:" << hostname << ":" << port;
    string str = ss.str().c_str();
    const char *spec = str.c_str();
    ANET_LOG(INFO, "listen to %s", spec);
    IOComponent *ioc = transport.listen(spec, &streamer, &serverAdapter);
    if (ioc == NULL) {
        ANET_LOG(ERROR, "listen (%s) ERROR.", spec);
        return;
    }

    while (!globalStopFlag) {
//        usleep(100000);
        int64_t now;
        transport.runIteration(now);
    }
//    transport.stop();
//    transport.wait();
    transport.closeComponents();

    globalQueue._condition.lock();
    while (globalQueue._queue.size()) {
        RequestEntry entry = globalQueue._queue.front();
        DefaultPacket *packet = (DefaultPacket*)entry._packet;
        ANET_LOG(WARN,"Discard request %s", packet->getBody());
        entry._packet->free();
        entry._connection->subRef();
        globalQueue._queue.pop();
    }
    globalQueue._condition.broadcast();
    globalQueue._condition.unlock();

    for (long i=0; i<num; i++) {
        ANET_LOG(INFO, "Join thread(%d)",i);
        threads[i].join();
    }

    printf("*****************************************************\n"); 
    printf("Worker Summary\n"); 
    printf("THREAD_ID TOT_TIME(ms) LOCK_TIME(ms) TASK_TIME(ms) TASK_WAIT(ms) TASKS_PROCESSED\n");
    for (long i=0; i<num; i++) {
        printf("%8ld %12.2f %12.2f %12.2f %13.2f %12ld\n",
                 runnables[i].m_id, 
                 runnables[i].m_totalTime / 1000.0, 
                 runnables[i].m_lockTime / 1000.0, 
                 runnables[i].m_taskProcessTime / 1000.0, 
                 runnables[i].m_taskWaitTime / 1000.0, 
                 runnables[i].m_taskProcesssed);
    }
    printf("\n");
    printf("Queue Summary\n");
    printf("     #Enqueue Acc_Enqueue_Len #Signals Push_Time(ms) Push_Wait_Time(ms)\n"); 
    printf("%12ld %14ld %8ld %13.2f %18.2f\n",
           globalQueue.mEnqueueCount, 
           globalQueue.mAccDequeueLength,
           globalQueue.mSignalCount,
           globalQueue.mAccEnqueueTime / 1000.0,
           globalQueue.mAccEnqueueWaitTime / 1000.0);
    
    printf("     #Dequeue Acc_Dequeue_Len   #Waits  Pop_Time(ms)  Pop_Wait_Time(ms)\n"); 
    printf("%12ld %14ld %8ld %13.2f %18.2f\n",
           globalQueue.mDequeCount, 
           globalQueue.mAccDequeueLength,
           globalQueue.mWaitCount,
           globalQueue.mAccDequeueTime / 1000.0,
           globalQueue.mAccDequeueWaitTime / 1000.0);
    printf("*****************************************************\n"); 
    
    delete [] threads;
    delete [] runnables;
}