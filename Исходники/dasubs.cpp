    void notify(MemoryBuffer &returndata)   // if returns false should unsubscribe
    {
        if (hasaborted) {
            throw MakeStringException(-1,"Subscription notification aborted");
            return;
        }
        size32_t dlen = returndata.length();
        CMessageBuffer mb;
        mb.append(tag).append(sid).append(dlen).append(returndata);
        try {
            if (!queryWorldCommunicator().send(mb,dst,MPTAG_DALI_SUBSCRIPTION_FULFILL,1000*60*3))  {
                // Must reply in 3 Minutes
                // Kludge to avoid locking SDS on blocked client
                hasaborted = true;
                StringBuffer tmp;
                throw MakeStringException(-1,"Subscription notification to %s timed out",dst->endpoint().getUrlStr(tmp).str());
                return;
            }

        }
        catch (IMP_Exception *e) {
            PrintExceptionLog(e,"Dali CSubscriptionStub");

            hasaborted = true;
            throw;
        }
    }