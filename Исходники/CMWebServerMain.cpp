void doProcess(unsigned int port, unsigned int num, CMClient& client) 
{
    Transport transport;
    transport.start(); //using multithreads mode of anet    

    Thread *threads = new Thread[num];
    RequestProcessor *runnables = new RequestProcessor [num];
    assert(threads);
    assert(runnables);
    for (long i=0; i<num; i++) {
        threads[i].start(runnables + i, (void*)&client);
    }

    HTTPPacketFactory factory;
    HTTPStreamer streamer(&factory);
    HTTPServerAdapter serverAdapter;
    stringstream ss;
    char hostname[1024];
    if (gethostname(hostname, 1024) != 0) {
        transport.stop();
        transport.wait();
        delete [] threads;
        delete [] runnables;
        exit(-1);
    }
    //    ss << "tcp:" << hostname << ":" << port;
    ss << "tcp:" << ":" << port;
    string str = ss.str();
    const char *spec = str.c_str();
    IOComponent *ioc = transport.listen(spec, &streamer, &serverAdapter);
    if (ioc == NULL) {
        printf("create listen port error\n");
        transport.stop();
        transport.wait();
        delete [] threads;
        delete [] runnables;
        return;
    }
    printf("webserver start ok\n");

    while (!globalStopFlag) {
        usleep(100000);
    }
    transport.stop();
    transport.wait();

    globalQueue._condition.lock();
    while (globalQueue._queue.size()) {
        HTTPRequestEntry entry = globalQueue._queue.front();
        entry._packet->free();
        entry._connection->subRef();
        globalQueue._queue.pop();
    }
    globalQueue._condition.broadcast();
    globalQueue._condition.unlock();

    for (long i=0; i<num; i++) {
        threads[i].join();
    }

    delete [] threads;
    delete [] runnables;
}