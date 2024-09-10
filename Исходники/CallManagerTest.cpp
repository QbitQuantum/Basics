    void testRefreshMgrUATeardown()
    {
        for (int i=0; i<NUM_OF_RUNS; ++i)
        {
            SipLineMgr*    lineMgr = new SipLineMgr();
            SipRefreshMgr* refreshMgr = new SipRefreshMgr();

            lineMgr->startLineMgr();
            lineMgr->initializeRefreshMgr( refreshMgr );

            SipUserAgent* sipUA = new SipUserAgent( 5090
                                                    ,5090
                                                    ,5091
                                                    ,NULL     // default publicAddress
                                                    ,NULL     // default defaultUser
                                                    ,"127.0.0.1" // default defaultSipAddress
                                                    ,NULL     // default sipProxyServers
                                                    ,NULL     // default sipDirectoryServers
                                                    ,NULL     // default sipRegistryServers
                                                    ,NULL     // default authenicateRealm
                                                    ,NULL     // default authenticateDb
                                                    ,NULL     // default authorizeUserIds
                                                    ,NULL     // default authorizePasswords
                                                    ,lineMgr
                                                  );

            sipUA->start();
            refreshMgr->init(sipUA);


            CallManager *pCallManager =
                new CallManager(FALSE,
                                NULL, //LineMgr
                                TRUE, // early media in 180 ringing
                                NULL, // CodecFactory
                                9000, // rtp start
                                9002, // rtp end
                                "sip:[email protected]",
                                "sip:[email protected]",
                                sipUA, //SipUserAgent
                                0, // sipSessionReinviteTimer
                                NULL, // mgcpStackTask
                                NULL, // defaultCallExtension
                                Connection::RING, // availableBehavior
                                NULL, // unconditionalForwardUrl
                                -1, // forwardOnNoAnswerSeconds
                                NULL, // forwardOnNoAnswerUrl
                                Connection::BUSY, // busyBehavior
                                NULL, // sipForwardOnBusyUrl
                                NULL, // speedNums
                                CallManager::SIP_CALL, // phonesetOutgoingCallProtocol
                                4, // numDialPlanDigits
                                CallManager::NEAR_END_HOLD, // holdType
                                5000, // offeringDelay
                                "", // pLocal
                                CP_MAXIMUM_RINGING_EXPIRE_SECONDS, //inviteExpireSeconds
                                QOS_LAYER3_LOW_DELAY_IP_TOS, // expeditedIpTos
                                10, //maxCalls
                                sipXmediaFactoryFactory(NULL)); //pMediaFactory
#if 0
            printf("Starting CallManager\n");
#endif
            pCallManager->start();

            lineMgr->requestShutdown();
            refreshMgr->requestShutdown();
            sipUA->shutdown(TRUE);
            pCallManager->requestShutdown();

#if 0
            printf("Deleting CallManager\n");
#endif

            delete pCallManager;
            delete refreshMgr;
            delete lineMgr;
        }

        for (int i=0; i<NUM_OF_RUNS; ++i)
        {
            sipxDestroyMediaFactoryFactory() ;
        }
    }