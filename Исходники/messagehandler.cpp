void CStunThreadMessageHandler::ProcessRequest(StunMessageEnvelope& message)
{
    CStunMessageReader reader;
    CStunMessageReader::ReaderParseState state;
    uint16_t responsePort = 0;
    HRESULT hr = S_OK;


    ChkIfA(_spStunResponder == NULL, E_FAIL);

    _spReaderBuffer->SetSize(0);
    _spResponseBuffer->SetSize(0);
    _message = message;

    _addrResponse = message.remoteAddr;
    _socketOutput = message.localSocket;
    _fRequestHasResponsePort = false;
    
    // zero out _error without the overhead of zero'ing out every byte in the strings
    _error.errorcode = 0;
    _error.szNonce[0] = 0;
    _error.szRealm[0] = 0;
    _error.attribUnknown = 0;
    
    _integrity.fSendWithIntegrity = false;
    _integrity.szUser[0] = '\0';
    _integrity.szRealm[0] = '\0';
    _integrity.szPassword[0] = '\0';
    
    
    // attach the temp buffer to reader
    reader.GetStream().Attach(_spReaderBuffer, true);


    reader.SetAllowLegacyFormat(true);

    // parse the request
    state = reader.AddBytes(message.spBuffer->GetData(), message.spBuffer->GetSize());

    // If we get something that can't be validated as a stun message, don't send back a response
    // STUN RFC may suggest sending back a "500", but I think that's the wrong approach.
    ChkIf (state != CStunMessageReader::BodyValidated, E_FAIL);
    
    // Regardless of what we send back, let's always attempt to honor a response port request
    // Fix the destination port if the client asked for us to send back to another port
    if (SUCCEEDED(reader.GetResponsePort(&responsePort)))
    {
        _addrResponse.SetPort(responsePort);
        _fRequestHasResponsePort = true;
    }

    reader.GetTransactionId(&_transid);

    // ignore anything that is not a request (with no response)
    ChkIf(reader.GetMessageClass() != StunMsgClassRequest, E_FAIL);

    // pre-prep the error message in case we wind up needing to send it
    _error.msgtype = reader.GetMessageType();
    _error.msgclass = StunMsgClassFailureResponse;

    if (reader.GetMessageType() != StunMsgTypeBinding)
    {
        // we're going to send back an error response
        _error.errorcode = STUN_ERROR_BADREQUEST; // invalid request
    }
    else
    {
        // handle authentication - but only if an auth provider has been set
        hr = ValidateAuth(reader);

        // if auth succeeded, then carry on to handling the request
        if (SUCCEEDED(hr) && (_error.errorcode==0))
        {
            // handle the binding request
            hr = ProcessBindingRequest(reader);
        }

        // catch all for any case where an error occurred
        if (FAILED(hr) && (_error.errorcode==0))
        {
            _error.errorcode = STUN_ERROR_BADREQUEST;
        }
    }

    if (_error.errorcode != 0)
    {
        // if either ValidateAuth or ProcessBindingRequest set an errorcode, or a fatal error occurred
        SendErrorResponse();
    }
    else
    {
        SendResponse();
    }


Cleanup:
    return;
}