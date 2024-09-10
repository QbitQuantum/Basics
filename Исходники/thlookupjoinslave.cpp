    bool receive(MemoryBuffer &mb)
    {
#ifdef _TRACEBROADCAST
        ActPrintLog(activity, "Broadcast node %d Receiving on tag %d",nodeindex,(int)mpTag);
#endif
        CMessageBuffer msg;
        rank_t sender;
        BooleanOnOff onOff(receiving);
        if (comm->recv(msg, RANK_ALL, mpTag, &sender))
        {
#ifdef _TRACEBROADCAST
            ActPrintLog(activity, "Broadcast node %d Received %d from %d",nodeindex, msg.length(), sender);
#endif
            try
            {
                mb.swapWith(msg);
                msg.clear(); // send empty reply
#ifdef _TRACEBROADCAST
                ActPrintLog(activity, "Broadcast node %d reply to %d",nodeindex, sender);
#endif
                comm->reply(msg);
                if (aborted) 
                    return false;
#ifdef _TRACEBROADCAST
                ActPrintLog(activity, "Broadcast node %d Received %d",nodeindex, mb.length());
#endif
            }
            catch (IException *e)
            {
                ActPrintLog(activity, e, "CBroadcaster::recv(2): exception");
                throw;
            }
        }
#ifdef _TRACEBROADCAST
        ActPrintLog(activity, "receive done");
#endif
        return (0 != mb.length());
    }