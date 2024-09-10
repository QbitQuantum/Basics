ThreadError DatasetManager::Register(void)
{
    ThreadError error = kThreadError_None;
    Coap::Header header;
    Message *message;
    Ip6::Address leader;
    Ip6::MessageInfo messageInfo;

    header.Init(kCoapTypeConfirmable, kCoapRequestPost);
    header.SetToken(Coap::Header::kDefaultTokenLength);
    header.AppendUriPathOptions(mUriSet);
    header.SetPayloadMarker();

    if (strcmp(mUriSet, OPENTHREAD_URI_PENDING_SET) == 0)
    {
        PendingDatasetBase *pending = static_cast<PendingDatasetBase *>(this);
        pending->UpdateDelayTimer();
    }

    VerifyOrExit((message = mNetif.GetCoapClient().NewMeshCoPMessage(header)) != NULL, error = kThreadError_NoBufs);

    SuccessOrExit(error = message->Append(mLocal.GetBytes(), mLocal.GetSize()));

    mNetif.GetMle().GetLeaderAloc(leader);

    messageInfo.SetPeerAddr(leader);
    messageInfo.SetPeerPort(kCoapUdpPort);
    SuccessOrExit(error = mNetif.GetCoapClient().SendMessage(*message, messageInfo));

    otLogInfoMeshCoP("sent dataset to leader");

exit:

    if (error != kThreadError_None && message != NULL)
    {
        message->Free();
    }

    return error;
}