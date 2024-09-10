UtlBoolean SipConfigServerAgent::handleMessage(OsMsg& eventMessage)
{

        osPrintf("---> SipConfigServerAgent: handleMessage...\r\n") ;

    int msgType = eventMessage.getMsgType();
    int msgSubType = eventMessage.getMsgSubType();

    // if this is a SIP message
    if(msgType == OsMsg::PHONE_APP &&
                msgSubType == SipMessage::NET_SIP_MESSAGE)
        {
                const SipMessage* sipMessage = ((SipMessageEvent&)eventMessage).getMessage();
                int messageType = ((SipMessageEvent&)eventMessage).getMessageStatus();
                osPrintf("SipConfigServerAgent::messageType: %d\n", messageType);
        UtlString method;

        // This is a request which failed to get sent
                if(messageType == SipMessageEvent::TRANSPORT_ERROR)
                {
            sipMessage->getRequestMethod(&method);
            osPrintf("SipConfigServerAgent:: Processing message transport error method: %s\n",
                sipMessage->isResponse() ? method.data() : "response");

            if(sipMessage->isResponse())
            {
                int seqNum;
                sipMessage->getCSeqField(&seqNum, &method);
                // SUBSCIBE (enrollment) response
                if(method.compareTo(SIP_SUBSCRIBE_METHOD))
                {
                    // We are sad the device is not there
                    osPrintf("SipConfigServerAgent::handleMessage enroll FAILURE: no response\n");
                }

            }
        }

        else if(messageType == SipMessageEvent::AUTHENTICATION_RETRY)
        {
        }

        // If this is a response
        else if(sipMessage->isResponse())
        {
            int seqNum;
            sipMessage->getCSeqField(&seqNum, &method);
            // SUBSCIBE (enrollment) response
            if(method.compareTo(SIP_NOTIFY_METHOD) &&
                mfpNotifyResponseCallbackFunc)
            {
                mfpNotifyResponseCallbackFunc(*sipMessage);
            }

        }

        // This is a request
        else
        {
            sipMessage->getRequestMethod(&method);
            UtlString eventType;
            sipMessage->getEventField(eventType);
            eventType.toLower();
            // SUBSRIBE (enrollment) request
            if(method.compareTo(SIP_SUBSCRIBE_METHOD) == 0 &&
                eventType.index(SIP_EVENT_CONFIG) >= 0 &&
                mfpEnrollmentCallbackFunc)
            {
               SipMessage response;
               SipMessage copyOfRequest(*sipMessage);

               // add a to tag to the sip message. This to tag will
               // be bubbled up to the Java layer. Also the same to tag will
               // be sent back in the response
               UtlString toAddr;
               UtlString toProto;
               int toPort;
               UtlString toTag;
               sipMessage->getToAddress(&toAddr, &toPort, &toProto, NULL, NULL, &toTag);
               if( toTag.isNull())
               {
                  int epochTime = (int)OsDateTime::getSecsSinceEpoch();
                  // Build a to tag
                  char tagBuffer[100];
                  sprintf(tagBuffer, "%dasd", epochTime);
                  copyOfRequest.setToFieldTag(tagBuffer);
               }

                int responseCode = mfpEnrollmentCallbackFunc(copyOfRequest);
                switch(responseCode)
                {
                    case SIP_ACCEPTED_CODE:
                       {
                          response.setExpiresField(DEFAULT_EXPIRES);
                          response.setResponseData(&copyOfRequest, SIP_ACCEPTED_CODE,
                            SIP_ACCEPTED_TEXT);
                       }
                        break;

                    default:
                        response.setResponseData(&copyOfRequest, SIP_BAD_REQUEST_CODE,
                            SIP_BAD_REQUEST_TEXT);
                        break;

                }
                if(mpSipUserAgent) mpSipUserAgent->send(response);
            }
        }
    }

    return(TRUE);
}