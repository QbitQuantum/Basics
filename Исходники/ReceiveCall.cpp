int main(int argc, char* argv[])
{
    bool bError = true ;
    int iSipPort, iRtpPort ;
    bool bLoopback ;
    char* szIdentity ;
    char* szUsername ;
    char* szPassword ;
    char* szRealm ;
    char* szStunServer ;
    char* szProxy ;
    bool bDialogEvents ;
    // The default run time is 2^31-1 seconds, which is over 68 years.
    long int runTime = LONG_MAX;
    SIPX_INST hInst ;
    SIPX_LINE hLine ;
    // Support for the dialog event notifier.
    // Component for holding the subscription data
    SipSubscriptionMgr* pSubscriptionMgr;
    // Component for granting the subscription rights
    SipSubscribeServerEventHandler* pPolicyHolder;
    // Component for publishing the event contents
    SipPublishContentMgr* pPublisher;
    SipSubscribeServer* pSubscribeServer;
    // The dialog event publisher
    DialogEventPublisher* pDialogEvents;

    // Parse Arguments
    if (parseArgs(argc, argv, &iDuration, &iSipPort, &iRtpPort, &g_szPlayTones,
                  &g_szFile, &bLoopback, &szIdentity, &szUsername, &szPassword,
                  &szRealm, &szStunServer, &szProxy, &bDialogEvents,
                  &g_callAnswerDelay, &g_timestamp, &runTime) &&
        (iDuration > 0) && (portIsValid(iSipPort)) && (portIsValid(iRtpPort)))
    {
        if (bLoopback)
        {
            initLoopback() ;
        }

        // initialize sipx TAPI-like API
        sipxConfigSetLogLevel(LOG_LEVEL_DEBUG) ;
        sipxConfigSetLogFile("ReceiveCall.log");
        if (sipxInitialize(&hInst, iSipPort, iSipPort, 5061, iRtpPort, 16, szIdentity) == SIPX_RESULT_SUCCESS)
        {
           // Start dialog event notifier if requested.
           if (bDialogEvents)
           {
              // Get pointer to the call manager.
              CallManager* pCallManager =
                 ((SIPX_INSTANCE_DATA*) hInst)->pCallManager;
              SipUserAgent* pUserAgent =
                 ((SIPX_INSTANCE_DATA*) hInst)->pSipUserAgent;

              // Start the SIP Subscribe Server
              pSubscriptionMgr = new SipSubscriptionMgr();
              pPolicyHolder = new SipSubscribeServerEventHandler;
              pPublisher = new SipPublishContentMgr;
              pSubscribeServer = new SipSubscribeServer(*pUserAgent,
                                                        *pPublisher,
                                                        *pSubscriptionMgr,
                                                        *pPolicyHolder);
              pSubscribeServer->enableEventType(DIALOG_EVENT_TYPE,
                                                NULL,
                                                NULL,
                                                NULL,
                                                NULL,
                                                SipSubscribeServer::standardVersionCallback);
              pSubscribeServer->start();

              // Create the dialog event publisher
              pDialogEvents = new DialogEventPublisher(pCallManager,
                                                       pPublisher);
              pCallManager->addTaoListener(pDialogEvents);
              pDialogEvents->start();
           }

            if (szProxy)
            {
                sipxConfigSetOutboundProxy(hInst, szProxy);
            }
            sipxConfigEnableRport(hInst, true) ;
            if (szStunServer)
            {
                sipxConfigEnableStun(hInst, szStunServer, 28) ;
            }
            sipxEventListenerAdd(hInst, EventCallBack, NULL) ;
            hLine = lineInit(hInst, szIdentity, szUsername, szPassword, szRealm) ;

            dumpLocalContacts(hInst) ;

            // Run as long as requested.
            for (long int i = 0; i < runTime; i++)
            {
                SLEEP(1000) ;
            }

            lineShutdown(hInst, hLine);
            // Wait a bit, so that we can re-send the REGISTER if it needs
            // authorization.
            SLEEP(5000);
        }
        else
        {
            printf("unable to initialize sipXtapi layer\n") ;
        }
    }
    else
    {
        usage(argv[0]) ;
    }

    return (int) bError ;
}