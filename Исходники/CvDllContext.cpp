//------------------------------------------------------------------------------
bool CvDllGameContext::RandomNumberGeneratorSyncCheck(PlayerTypes ePlayer, ICvRandom1* pRandom, bool bIsHost)
{
	// uh oh! Check the Random number generator!
	const CvRandom& localSimRandomNumberGenerator = GC.getGame().getJonRand();
	CvRandom* pkRandom = GC.UnwrapRandomPointer(pRandom);

	if(localSimRandomNumberGenerator != *pkRandom)
	{
		FILogFile* logFile = LOGFILEMGR.GetLog("net_message_debug.log", 0);

		char formatBuf[128] = {"\0"};
		std::string rngLogMessage = "Game Random Number Generators are out of sync : local.seed=";
		_i64toa_s(localSimRandomNumberGenerator.getSeed(), formatBuf, 127, 10);	rngLogMessage += formatBuf;
		rngLogMessage += ", remote.seed=";
		_i64toa_s(pkRandom->getSeed(), formatBuf, 127, 10);	rngLogMessage += formatBuf; 
		rngLogMessage += "\n\tlocal.callCount=";
		_itoa_s(localSimRandomNumberGenerator.getCallCount(), formatBuf, 10); rngLogMessage += formatBuf;
		rngLogMessage += ", remote.callCount=";
		_itoa_s(pkRandom->getCallCount(), formatBuf, 10); rngLogMessage += formatBuf;
		rngLogMessage += "\n\tlocal.resetCount=";
		_itoa_s(localSimRandomNumberGenerator.getResetCount(), formatBuf, 10); rngLogMessage += formatBuf;
		rngLogMessage += ", remote.resetCount=";
		_itoa_s(pkRandom->getResetCount(), formatBuf, 10); rngLogMessage += formatBuf;
		rngLogMessage += "\n";

		if(logFile)
			logFile->DebugMsg(rngLogMessage.c_str());

		return false;
	}

	return true;
}