    void tearDown() {
        for(int i = 0; i < 2; i++)
            _storage->releaseBucket(_buckets[i]);

        delete _work;
        _work = NULL;

        _ctx->shutdown();

        _trace->prepareShutdown();

        delete _storage;
        _storage = NULL;

        delete _ctx;
        _ctx = NULL;

        _trace->shutdown();
        delete _trace;
        _trace = NULL;

        delete _sstConnMgr;
        _sstConnMgr = NULL;

        delete _ohSSTConnMgr;
        _ohSSTConnMgr = NULL;

        delete _mainStrand;
        _mainStrand = NULL;
        delete _ios;
        _ios = NULL;
    }