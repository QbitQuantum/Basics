otError Dhcp6Server::SendReply(otIp6Address &aDst, uint8_t *aTransactionId, ClientIdentifier &aClient, IaNa &aIaNa)
{
    otError error = OT_ERROR_NONE;
    Ip6::MessageInfo messageInfo;
    Message *message;

    VerifyOrExit((message = mSocket.NewMessage(0)) != NULL, error = OT_ERROR_NO_BUFS);
    SuccessOrExit(error = AppendHeader(*message, aTransactionId));
    SuccessOrExit(error = AppendServerIdentifier(*message));
    SuccessOrExit(error = AppendClientIdentifier(*message, aClient));
    SuccessOrExit(error = AppendIaNa(*message, aIaNa));
    SuccessOrExit(error = AppendStatusCode(*message, kStatusSuccess));
    SuccessOrExit(error = AppendIaAddress(*message, aClient));
    SuccessOrExit(error = AppendRapidCommit(*message));

    memset(&messageInfo, 0, sizeof(messageInfo));
    memcpy(&messageInfo.GetPeerAddr().mFields.m8, &aDst, sizeof(otIp6Address));
    messageInfo.mPeerPort = kDhcpClientPort;
    SuccessOrExit(error = mSocket.SendTo(*message, messageInfo));

exit:

    if (message != NULL && error != OT_ERROR_NONE)
    {
        message->Free();
    }

    return error;
}