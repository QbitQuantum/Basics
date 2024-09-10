otError Leader::SendPetitionResponse(const Coap::Header &aRequestHeader, const Ip6::MessageInfo &aMessageInfo,
                                     StateTlv::State aState)
{
    ThreadNetif &netif = GetNetif();
    otError error = OT_ERROR_NONE;
    Coap::Header responseHeader;
    StateTlv state;
    CommissionerSessionIdTlv sessionId;
    Message *message;

    responseHeader.SetDefaultResponseHeader(aRequestHeader);
    responseHeader.SetPayloadMarker();

    VerifyOrExit((message = NewMeshCoPMessage(netif.GetCoap(), responseHeader)) != NULL, error = OT_ERROR_NO_BUFS);

    state.Init();
    state.SetState(aState);
    SuccessOrExit(error = message->Append(&state, sizeof(state)));

    if (mTimer.IsRunning())
    {
        uint16_t len = sizeof(Tlv) + mCommissionerId.GetLength();
        SuccessOrExit(error = message->Append(&mCommissionerId, len));
    }

    if (aState == StateTlv::kAccept)
    {
        sessionId.Init();
        sessionId.SetCommissionerSessionId(mSessionId);
        SuccessOrExit(error = message->Append(&sessionId, sizeof(sessionId)));
    }

    SuccessOrExit(error = netif.GetCoap().SendMessage(*message, aMessageInfo));

    otLogInfoMeshCoP(GetInstance(), "sent petition response");

exit:

    if (error != OT_ERROR_NONE && message != NULL)
    {
        message->Free();
    }

    return error;
}