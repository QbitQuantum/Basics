otError DataPollManager::SendDataPoll(void)
{
    otError   error;
    Message * message;
    Neighbor *parent;

    VerifyOrExit(mEnabled, error = OT_ERROR_INVALID_STATE);
    VerifyOrExit(!Get<Mac::Mac>().GetRxOnWhenIdle(), error = OT_ERROR_INVALID_STATE);

    parent = Get<Mle::MleRouter>().GetParentCandidate();
    VerifyOrExit((parent != NULL) && parent->IsStateValidOrRestoring(), error = OT_ERROR_INVALID_STATE);

    mTimer.Stop();

    for (message = Get<MeshForwarder>().GetSendQueue().GetHead(); message; message = message->GetNext())
    {
        VerifyOrExit(message->GetType() != Message::kTypeMacDataPoll, error = OT_ERROR_ALREADY);
    }

    message = Get<MessagePool>().New(Message::kTypeMacDataPoll, 0);
    VerifyOrExit(message != NULL, error = OT_ERROR_NO_BUFS);

    error = Get<MeshForwarder>().SendMessage(*message);

    if (error != OT_ERROR_NONE)
    {
        message->Free();
    }

exit:

    switch (error)
    {
    case OT_ERROR_NONE:
        otLogDebgMac("Sending data poll");

        if (mNoBufferRetxMode == true)
        {
            mNoBufferRetxMode = false;
            ScheduleNextPoll(kRecalculatePollPeriod);
        }
        else
        {
            ScheduleNextPoll(kUsePreviousPollPeriod);
        }

        break;

    case OT_ERROR_INVALID_STATE:
        otLogWarnMac("Data poll tx requested while data polling was not enabled!");
        StopPolling();
        break;

    case OT_ERROR_ALREADY:
        otLogDebgMac("Data poll tx requested when a previous data request still in send queue.");
        ScheduleNextPoll(kUsePreviousPollPeriod);
        break;

    case OT_ERROR_NO_BUFS:
    default:
        mNoBufferRetxMode = true;
        ScheduleNextPoll(kRecalculatePollPeriod);
        break;
    }

    return error;
}