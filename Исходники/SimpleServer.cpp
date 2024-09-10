// panic the client
void CPicoServSession::PanicClient(TInt aPanic) const
{
	Panic(_L("PicoN client"), aPanic);
	// client screwed up - there is nothing for us to do now
	RProcess me;
	me.Terminate(1);
}