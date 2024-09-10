cpiMessanger::cpiMessanger() : mConsole(this), mMsgs(NULL), mReloadTimer(30., 0., cTime())
{
	mName = "Messanger";
	mVersion = MESSENGER_VERSION;
}