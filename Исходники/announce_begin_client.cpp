otError AnnounceBeginClient::SendRequest(uint32_t aChannelMask, uint8_t aCount, uint16_t aPeriod,
                                         const Ip6::Address &aAddress)
{
    otError error = OT_ERROR_NONE;
    Coap::Header header;
    MeshCoP::CommissionerSessionIdTlv sessionId;
    MeshCoP::ChannelMask0Tlv channelMask;
    MeshCoP::CountTlv count;
    MeshCoP::PeriodTlv period;

    Ip6::MessageInfo messageInfo;
    Message *message = NULL;

    VerifyOrExit(GetNetif().GetCommissioner().IsActive(), error = OT_ERROR_INVALID_STATE);

    header.Init(aAddress.IsMulticast() ? OT_COAP_TYPE_NON_CONFIRMABLE : OT_COAP_TYPE_CONFIRMABLE,
                OT_COAP_CODE_POST);
    header.SetToken(Coap::Header::kDefaultTokenLength);
    header.AppendUriPathOptions(OT_URI_PATH_ANNOUNCE_BEGIN);
    header.SetPayloadMarker();

    VerifyOrExit((message = MeshCoP::NewMeshCoPMessage(GetNetif().GetCoap(), header)) != NULL,
                 error = OT_ERROR_NO_BUFS);

    sessionId.Init();
    sessionId.SetCommissionerSessionId(GetNetif().GetCommissioner().GetSessionId());
    SuccessOrExit(error = message->Append(&sessionId, sizeof(sessionId)));

    channelMask.Init();
    channelMask.SetMask(aChannelMask);
    SuccessOrExit(error = message->Append(&channelMask, sizeof(channelMask)));

    count.Init();
    count.SetCount(aCount);
    SuccessOrExit(error = message->Append(&count, sizeof(count)));

    period.Init();
    period.SetPeriod(aPeriod);
    SuccessOrExit(error = message->Append(&period, sizeof(period)));

    messageInfo.SetSockAddr(GetNetif().GetMle().GetMeshLocal16());
    messageInfo.SetPeerAddr(aAddress);
    messageInfo.SetPeerPort(kCoapUdpPort);
    messageInfo.SetInterfaceId(GetNetif().GetInterfaceId());

    SuccessOrExit(error = GetNetif().GetCoap().SendMessage(*message, messageInfo));

    otLogInfoMeshCoP(GetInstance(), "sent announce begin query");

exit:

    if (error != OT_ERROR_NONE && message != NULL)
    {
        message->Free();
    }

    return error;
}