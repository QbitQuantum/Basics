TTErr MinuitSenderManager::send(TTSymbol applicationName, TTSymbol ip, TTUInt16 port, const TTValue& message)
{
    TTValue  last;
    
    // if nothing is being sent to an application
    if (mSending.findEquals(applicationName, last))
    {
        // lock application
        mSending.append(applicationName);
        
        TTObject anOscSender;
        
        TTErr err = mSenders.lookup(applicationName, last);
        
        if (err)
        {
            anOscSender = TTObject("osc.send");
            
            anOscSender.set("address", ip);
            anOscSender.set("port", port);
            
            TTValue cache(anOscSender, ip, port);
            mSenders.append(applicationName, cache);
        }
        else
        {
            anOscSender = last[0];
            TTSymbol lastIp = last[1];
            TTUInt16 lastPort = last[2];
            
            if (lastIp == ip && lastPort == port)
                ;
            
            else
            {
                anOscSender.set("address", ip);
                anOscSender.set("port", port);
                
                TTValue cache(anOscSender, ip, port);
                mSenders.remove(applicationName);
                mSenders.append(applicationName, cache);
            }
        }
        
        err = anOscSender.send("send", message);
        
        // unlock application
        mSending.remove(applicationName);
        
        return kTTErrNone;
    }

    return kTTErrGeneric;
}