bool cPenaltyList::RemPenalty(sPenalty &penal)
{
	SetBaseTo(&mModel);
	mModel.mNick = penal.mNick;
	mModel.mOpNick = penal.mOpNick;
	time_t Now = cTime().Sec();
	if(LoadPK()) {
		if(penal.mStartChat < Now) mModel.mStartChat = Now;
		if(penal.mStartCTM < Now) mModel.mStartCTM = Now;
		if(penal.mStartPM < Now) mModel.mStartPM = Now;
		if(penal.mStartSearch < Now) mModel.mStartSearch = Now;
		if(penal.mStopKick < Now) mModel.mStopKick = Now;
		if(penal.mStopShare0 < Now) mModel.mStopShare0 = Now;
		if(penal.mStopReg < Now) mModel.mStopReg = Now;
		if(penal.mStopOpchat < Now) mModel.mStopOpchat = Now;
	}
	if(mModel.ToKeepIt())
		return SavePK();
	else
		DeletePK();
	return true;
}