Time GSM::CCCHLogicalChannel::getNextMsgSendTime() {
	// Get the current frame.
	// DAB GPRS - This should call L1->resync() first, otherwise, in an idle system,
	// DAB GPRS - you can get times well into the past..
	// (pat) Above is done in the underlying getNextWriteTime()
	// Pats note: This may return the current frame number if it is ready to send now.
	// 3-18-2012: FIXME: This result is not monotonically increasing!!
	// That is screwing up GPRS sendAssignment.
	GSM::Time next = getNextWriteTime();
	int achload = load();
	if (mWaitingToSend) { achload++; }
	//old: GSM::Time result = next + (achload+3) * 51;	// add one to be safe.

	// (pat) TODO: We are adding a whole 51-multframe for each additional
	// CCCH message, which may not be correct.
	// Note: We dont need to carefully make sure the frame
	// numbers are valid (eg, by rollForward), because this code is used by GPRS
	// which is going to convert it to an RLC block time anyway.
	int fnresult = (next.FN() + achload * 51) % gHyperframe;
	GSM::Time result(fnresult);
	LOG(DEBUG) << "CCCHLogicalChannel::getNextSend="<< next.FN()
		<<" load="<<achload<<LOGVAR(mWaitingToSend) <<" now="<<gBTS.time().FN()<<LOGVAR(fnresult);
	return result;
}