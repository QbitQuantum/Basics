    void testDrop (beast::Journal j)
    {
        testcase ("Warn/drop");

        TestLogic logic (j);

        Charge const fee (dropThreshold + 1);
        beast::IP::Endpoint const addr (
            beast::IP::Endpoint::from_string ("207.127.82.2"));

        {
            Consumer c (logic.newInboundEndpoint (addr));

            // Create load until we get a warning
            int n = 10000;

            while (--n >= 0)
            {
                if (n == 0)
                {
                    fail ("Loop count exceeded without warning");
                    return;
                }

                if (c.charge (fee) == warn)
                {
                    pass ();
                    break;
                }
                ++logic.clock ();
            }

            // Create load until we get dropped
            while (--n >= 0)
            {
                if (n == 0)
                {
                    fail ("Loop count exceeded without dropping");
                    return;
                }

                if (c.charge (fee) == drop)
                {
                    // Disconnect abusive Consumer
                    expect (c.disconnect ());
                    break;
                }
                ++logic.clock ();
            }
        }

        // Make sure the consumer is on the blacklist for a while.
        {
            Consumer c (logic.newInboundEndpoint (addr));
            logic.periodicActivity();
            if (c.disposition () != drop)
            {
                fail ("Dropped consumer not put on blacklist");
                return;
            }
        }

        // Makes sure the Consumer is eventually removed from blacklist
        bool readmitted = false;
        {
            // Give Consumer time to become readmitted.  Should never
            // exceed expiration time.
            std::size_t n (secondsUntilExpiration + 1);
            while (--n > 0)
            {
                ++logic.clock ();
                logic.periodicActivity();
                Consumer c (logic.newInboundEndpoint (addr));
                if (c.disposition () != drop)
                {
                    readmitted = true;
                    break;
                }
            }
        }
        if (readmitted == false)
        {
            fail ("Dropped Consumer left on blacklist too long");
            return;
        }
        pass();
    }