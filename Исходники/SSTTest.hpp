    void testListenConnect() {
        using std::tr1::placeholders::_1;
        using std::tr1::placeholders::_2;

        // Test that A listens, B tries to connect
        _conn_mgr->listen(
            std::tr1::bind(&SstTest::onConnectNotify, this, _endpoints[0], _1, _2),
            Mock::Endpoint(_endpoints[0], 1)
        );
        _conn_mgr->connectStream(
            Mock::Endpoint(_endpoints[1], 1),
            Mock::Endpoint(_endpoints[0], 1),
            std::tr1::bind(&SstTest::onConnectNotify, this, _endpoints[1], _1, _2)
        );

        EventSet conn_evts;
        conn_evts.insert("a connected");
        conn_evts.insert("b connected");
        waitForEventSet(conn_evts);
    }