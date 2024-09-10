int HtiStifMsg::CheckResponseCommandCode(struct soap *soap, BYTE commandCode)
{
    int result = SOAP_OK;

    if( msgBody[0] != commandCode )
    {
        char msg[] = "incorrect response CommandCode (expected 0x%x, got 0x%x)";
        int msgLen = _scprintf(msg, commandCode, msgBody[0])+1; // +1 for nul char
        char *buf = new char[msgLen];
        sprintf(buf, msg, commandCode, msgBody[0]);
        soap->error = soap_receiver_fault(soap, "HtiError", buf);
        delete buf;
        result = SOAP_FAULT;
    }

    return result;
}