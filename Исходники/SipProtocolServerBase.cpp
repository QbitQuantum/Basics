UtlBoolean SipProtocolServerBase::send(SipMessage* message,
                            const char* hostAddress,
                            int hostPort)
{
    UtlBoolean sendOk = FALSE;


    UtlString localIp(message->getLocalIp());
    
    if (localIp.length() < 1)
    {
        localIp = mDefaultIp;
    }

    SipClient* client = createClient(hostAddress, hostPort, localIp);
    if(client)
    {
        int isBusy = client->isInUseForWrite();
        UtlString clientNames;

        client->getClientNames(clientNames);
        OsSysLog::add(FAC_SIP, PRI_DEBUG, "Sip%sServerBase::send %p isInUseForWrite %d, client info\n %s",
                mProtocolString.data(), client, isBusy, clientNames.data());

        sendOk = client->sendTo(*message, hostAddress, hostPort);
        if(!sendOk)
        {
            OsTask* pCallingTask = OsTask::getCurrentTask();
            OsTaskId_t callingTaskId = -1;
            OsTaskId_t clientTaskId = -1;

            if ( pCallingTask )
            {
               pCallingTask->id(callingTaskId);
            }
            client->id(clientTaskId);

            if (clientTaskId != callingTaskId)
            {
               // Do not need to clientLock.acquireWrite();
               // as deleteClient uses the locking list lock
               // which is all that is needed as the client is
               // already marked as busy when we called
               // createClient above.
               deleteClient(client);
               client = NULL;
            }
        }
    }

        if(client)
        {
            releaseClient(client);
        }

    return(sendOk);
}