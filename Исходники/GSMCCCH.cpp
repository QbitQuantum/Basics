bool CCCHLogicalChannel::sendGprsCcchMessage(NewPagingEntry *gprsMsg, GSM::Time &frameTime)
{
    if (! gprsPageCcchSetTime(gprsMsg->mGprsClient,gprsMsg->mImmAssign,frameTime.FN())) {
        return false;
    }
    L2LogicalChannelBase::l2sendm(*(gprsMsg->mImmAssign),L3_UNIT_DATA);
    return true;
}