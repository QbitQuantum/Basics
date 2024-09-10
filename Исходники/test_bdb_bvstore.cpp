int CBDB_TestThreads::Run(void)
{
    const CArgs& args = GetArgs();

    NcbiCout << "Initialize transactional environment..." << flush;

    string path = "./bvstore_test_thr";
    path = CDirEntry::AddTrailingPathSeparator(path);

    {{
        CDir dir(path);
        if ( !dir.Exists() ) {
            dir.Create();
        }
    }}


    CBDB_Env env;

    // Error file for Berkeley DB
    string err_file = path + "err_bvstore_test.log";
    env.OpenErrFile(err_file.c_str());

    env.SetLogFileMax(50 * 1024 * 1024);

    // use in-memory logging to improve performance (warning: not durable)
    env.SetLogInMemory(true);
    env.SetLogBSize(100 * 1024 * 1024);

    env.SetLogAutoRemove(true);

    env.SetCacheSize(5 * 1024 * 1024);

    env.OpenWithTrans(path.c_str(), CBDB_Env::eThreaded /*| CBDB_Env::eRunRecovery*/);
    env.SetDirectDB(true);
    env.SetDirectLog(true);
    env.SetLockTimeout(10 * 1000000); // 10 sec
    env.SetTasSpins(5);

    {{
        SBVStoreDB db;
        db.SetEnv(env);
        db.Open("bvdata.db", CBDB_RawFile::eCreate);

        CBDB_Transaction trans(*db.GetEnv(),
                            CBDB_Transaction::eTransASync,
                            CBDB_Transaction::eNoAssociation);
        db.SetTransaction(&trans);

        db.thr_id = 1;
        db.rec_id = 1;

        bm::bvector<> bv;
        FillBV(&bv, 1000000);

        db.WriteVector(bv, SBVStoreDB::eCompact);

        trans.Commit();
    }}
    {{
        SBVStoreDB db;
        db.SetEnv(env);
        db.Open("bvdata.db", CBDB_RawFile::eReadWrite);

        db.thr_id = 1;
        db.rec_id = 1;
        bm::bvector<> bv;

        EBDB_ErrCode err = db.ReadVector(&bv);
        assert(err == eBDB_Ok);
        NcbiCout << bv.count() << NcbiEndl;

    }}

    NcbiCout << "Ok." << NcbiEndl;

    try
    {
        unsigned kProcessingRecs = 100000;
        if (args["recs"]) {
            kProcessingRecs = args["recs"].AsInteger();
        }

        unsigned kThreadCount = 2;
        if (args["threads"]) {
            kThreadCount = args["threads"].AsInteger();
        }


        vector<CRef<CThread> > thread_list;
        thread_list.reserve(kThreadCount);

        CStopWatch sw(CStopWatch::eStart);

        NcbiCout << "Starting " << kThreadCount << " threads..." << flush;
        for (unsigned i = 0; i < kThreadCount; ++i) {
            CRef<CThread> bdb_thread(
                new CBDB_BVTestThread(env, i, kProcessingRecs));
            thread_list.push_back(bdb_thread);
            bdb_thread->Run();
        } // for
        NcbiCout << "Ok." << NcbiEndl;

        NcbiCout << "Waiting for threads to finish..." << flush;

        NON_CONST_ITERATE(vector<CRef<CThread> >, it, thread_list) {
            CRef<CThread> bdb_thread(*it);
            bdb_thread->Join();
        }

        NcbiCout << "Ok." << NcbiEndl;

        double elapsed = sw.Elapsed();
        unsigned total_recs = kProcessingRecs * kThreadCount;
        double rate = total_recs / elapsed;
        double rate_per_thread = kProcessingRecs / elapsed;

        NcbiCout.setf(IOS_BASE::fixed, IOS_BASE::floatfield);
        NcbiCout << "Elapsed: " << elapsed << " secs." << NcbiEndl;
        NcbiCout << "Transaction rate: " << rate << " recs/secs." << NcbiEndl;
        NcbiCout << "Rate per thread: " << rate_per_thread << " recs/secs."
                 << NcbiEndl;
    }