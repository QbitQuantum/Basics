void CoapSecure::HandleDtlsReceive(uint8_t *aBuf, uint16_t aLength)
{
    Message *message = NULL;

    VerifyOrExit((message = GetInstance().GetMessagePool().New(Message::kTypeIp6, 0)) != NULL);
    SuccessOrExit(message->Append(aBuf, aLength));

    CoapBase::Receive(*message, mPeerAddress);

exit:

    if (message != NULL)
    {
        message->Free();
    }
}