otError PanIdQueryClient::SendQuery(uint16_t aPanId, uint32_t aChannelMask, const Ip6::Address &aAddress,
                                    otCommissionerPanIdConflictCallback aCallback, void *aContext)
{
    ThreadNetif &netif = GetNetif();
    otError error = OT_ERROR_NONE;
    Coap::Header header;
    MeshCoP::CommissionerSessionIdTlv sessionId;
    MeshCoP::ChannelMask0Tlv channelMask;
    MeshCoP::PanIdTlv panId;
    Ip6::MessageInfo messageInfo;
    Message *message = NULL;

    VerifyOrExit(netif.GetCommissioner().IsActive(), error = OT_ERROR_INVALID_STATE);

    header.Init(aAddress.IsMulticast() ? OT_COAP_TYPE_NON_CONFIRMABLE : OT_COAP_TYPE_CONFIRMABLE,
                OT_COAP_CODE_POST);
    header.SetToken(Coap::Header::kDefaultTokenLength);
    header.AppendUriPathOptions(OT_URI_PATH_PANID_QUERY);
    header.SetPayloadMarker();

    VerifyOrExit((message = MeshCoP::NewMeshCoPMessage(netif.GetCoap(), header)) != NULL,
                 error = OT_ERROR_NO_BUFS);

    sessionId.Init();
    sessionId.SetCommissionerSessionId(netif.GetCommissioner().GetSessionId());
    SuccessOrExit(error = message->Append(&sessionId, sizeof(sessionId)));

    channelMask.Init();
    channelMask.SetMask(aChannelMask);
    SuccessOrExit(error = message->Append(&channelMask, sizeof(channelMask)));

    panId.Init();
    panId.SetPanId(aPanId);
    SuccessOrExit(error = message->Append(&panId, sizeof(panId)));

    messageInfo.SetSockAddr(netif.GetMle().GetMeshLocal16());
    messageInfo.SetPeerAddr(aAddress);
    messageInfo.SetPeerPort(kCoapUdpPort);
    messageInfo.SetInterfaceId(netif.GetInterfaceId());
    SuccessOrExit(error = netif.GetCoap().SendMessage(*message, messageInfo));

    otLogInfoMeshCoP(GetInstance(), "sent panid query");

    mCallback = aCallback;
    mContext = aContext;

exit:

    if (error != OT_ERROR_NONE && message != NULL)
    {
        message->Free();
    }

    return error;
}