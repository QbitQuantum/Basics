UtlBoolean SipPimClient::handleMessage(OsMsg& eventMessage)
{
    int msgType = eventMessage.getMsgType();
    int msgSubType = eventMessage.getMsgSubType();

    // SIP message
    if(msgType == OsMsg::PHONE_APP &&
       msgSubType == SipMessage::NET_SIP_MESSAGE)
    {
        const SipMessage* sipMessage = ((SipMessageEvent&)eventMessage).getMessage();

        // If this is a MESSAGE request
        UtlString method;
        if(sipMessage) sipMessage->getRequestMethod(&method);
        method.toUpper();
        UtlBoolean responseSent = FALSE;
        if(sipMessage &&
            method.compareTo(SIP_MESSAGE_METHOD) == 0 &&
            !sipMessage->isResponse())
        {
            const HttpBody* messageBody = sipMessage->getBody();
            UtlString contentType = messageBody->getContentType();
            // Trim off the MIME parameters if present
            contentType.remove(strlen(CONTENT_TYPE_TEXT_PLAIN));


            // We have a text body and a callback handler function
            if(messageBody &&
               mpTextHandlerFunction &&
               contentType.compareTo(CONTENT_TYPE_TEXT_PLAIN, UtlString::ignoreCase) == 0)
            {
                const char* bodyBytes;
                ssize_t bodyLength;
                messageBody->getBytes(&bodyBytes, &bodyLength);
                UtlString fromField;
                sipMessage->getFromField(&fromField);

                // Send back a 200 response
                SipMessage response;
                response.setResponseData(sipMessage, SIP_OK_CODE, SIP_OK_TEXT);
                mpUserAgent->send(response);
                responseSent = TRUE;

                // Invoke the call back with the info
                mpTextHandlerFunction(fromField, bodyBytes, bodyLength,
                    *sipMessage);

            }

            if(!responseSent)
            {
                // Send an error as we do not accept the content type
                SipMessage badContentResponse;
                badContentResponse.setResponseData(sipMessage,
                                                    SIP_BAD_MEDIA_CODE,
                                                    SIP_BAD_MEDIA_TEXT);
                mpUserAgent->send(badContentResponse);
            }

        }
    }
    return(TRUE);
}