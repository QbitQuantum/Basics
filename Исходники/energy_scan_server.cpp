otError EnergyScanServer::SendReport(void)
{
    otError                  error = OT_ERROR_NONE;
    Coap::Header             header;
    MeshCoP::ChannelMask0Tlv channelMask;
    MeshCoP::EnergyListTlv   energyList;
    Ip6::MessageInfo         messageInfo;
    Message *                message;

    header.Init(OT_COAP_TYPE_CONFIRMABLE, OT_COAP_CODE_POST);
    header.SetToken(Coap::Header::kDefaultTokenLength);
    header.AppendUriPathOptions(OT_URI_PATH_ENERGY_REPORT);
    header.SetPayloadMarker();

    VerifyOrExit((message = MeshCoP::NewMeshCoPMessage(GetNetif().GetCoap(), header)) != NULL,
                 error = OT_ERROR_NO_BUFS);

    channelMask.Init();
    channelMask.SetMask(mChannelMask);
    SuccessOrExit(error = message->Append(&channelMask, sizeof(channelMask)));

    energyList.Init();
    energyList.SetLength(mScanResultsLength);
    SuccessOrExit(error = message->Append(&energyList, sizeof(energyList)));
    SuccessOrExit(error = message->Append(mScanResults, mScanResultsLength));

    messageInfo.SetSockAddr(GetNetif().GetMle().GetMeshLocal16());
    messageInfo.SetPeerAddr(mCommissioner);
    messageInfo.SetPeerPort(kCoapUdpPort);
    SuccessOrExit(error = GetNetif().GetCoap().SendMessage(*message, messageInfo));

    otLogInfoMeshCoP(GetInstance(), "sent scan results");

exit:

    if (error != OT_ERROR_NONE && message != NULL)
    {
        message->Free();
    }

    mActive = false;

    return error;
}