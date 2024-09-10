    SstCloseTest() {
        plugins.load( "tcpsst" );

        uint32 randport = 3000 + (uint32)(Sirikata::Task::LocalTime::now().raw() % 20000);
        mPort = boost::lexical_cast<std::string>(randport);

        mBytes=65536;
        mChunks=3;
        mOffset=1;
        mSendService = new IOServicePool(4);
        mSendStrand = mSendService->service()->createStrand();
        mRecvService = new IOServicePool(4);
        mRecvStrand = mRecvService->service()->createStrand();
        mListener = StreamListenerFactory::getSingleton().getDefaultConstructor()(mRecvStrand,StreamListenerFactory::getSingleton().getDefaultOptionParser()(String()));
        using std::tr1::placeholders::_1;
        using std::tr1::placeholders::_2;
        mListener->listen(Address("127.0.0.1",mPort),std::tr1::bind(&SstCloseTest::listenerNewStreamCallback,this,_1,_2));

        mRecvService->run();
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif

    }