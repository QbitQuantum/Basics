void JoinerRouter::HandleRelayTransmit(Coap::Message &aMessage, const Ip6::MessageInfo &aMessageInfo)
{
    OT_UNUSED_VARIABLE(aMessageInfo);

    otError            error;
    JoinerUdpPortTlv   joinerPort;
    JoinerIidTlv       joinerIid;
    JoinerRouterKekTlv kek;
    uint16_t           offset;
    uint16_t           length;
    Message *          message  = NULL;
    otMessageSettings  settings = {false, static_cast<otMessagePriority>(kMeshCoPMessagePriority)};
    Ip6::MessageInfo   messageInfo;

    VerifyOrExit(aMessage.GetType() == OT_COAP_TYPE_NON_CONFIRMABLE && aMessage.GetCode() == OT_COAP_CODE_POST,
                 error = OT_ERROR_DROP);

    otLogInfoMeshCoP("Received relay transmit");

    SuccessOrExit(error = Tlv::GetTlv(aMessage, Tlv::kJoinerUdpPort, sizeof(joinerPort), joinerPort));
    VerifyOrExit(joinerPort.IsValid(), error = OT_ERROR_PARSE);

    SuccessOrExit(error = Tlv::GetTlv(aMessage, Tlv::kJoinerIid, sizeof(joinerIid), joinerIid));
    VerifyOrExit(joinerIid.IsValid(), error = OT_ERROR_PARSE);

    SuccessOrExit(error = Tlv::GetValueOffset(aMessage, Tlv::kJoinerDtlsEncapsulation, offset, length));

    VerifyOrExit((message = mSocket.NewMessage(0, &settings)) != NULL, error = OT_ERROR_NO_BUFS);

    while (length)
    {
        uint16_t copyLength = length;
        uint8_t  tmp[16];

        if (copyLength >= sizeof(tmp))
        {
            copyLength = sizeof(tmp);
        }

        aMessage.Read(offset, copyLength, tmp);
        SuccessOrExit(error = message->Append(tmp, copyLength));

        offset += copyLength;
        length -= copyLength;
    }

    aMessage.CopyTo(offset, 0, length, *message);

    messageInfo.mPeerAddr.mFields.m16[0] = HostSwap16(0xfe80);
    memcpy(messageInfo.mPeerAddr.mFields.m8 + 8, joinerIid.GetIid(), 8);
    messageInfo.SetPeerPort(joinerPort.GetUdpPort());
    messageInfo.SetInterfaceId(GetNetif().GetInterfaceId());

    SuccessOrExit(error = mSocket.SendTo(*message, messageInfo));

    if (Tlv::GetTlv(aMessage, Tlv::kJoinerRouterKek, sizeof(kek), kek) == OT_ERROR_NONE)
    {
        otLogInfoMeshCoP("Received kek");

        DelaySendingJoinerEntrust(messageInfo, kek);
    }

exit:
    if (error != OT_ERROR_NONE && message != NULL)
    {
        message->Free();
    }
}