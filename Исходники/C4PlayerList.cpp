C4Player* C4PlayerList::Join(const char *szFilename, bool fScenarioInit, int iAtClient, const char *szAtClientName, C4PlayerInfo *pInfo, C4ValueNumbers * numbers)
{
	assert(pInfo);
	assert(fScenarioInit || numbers);

	// safeties
	if (szFilename && !*szFilename) szFilename = NULL;

	// Log
	LogF(LoadResStr(fScenarioInit ? "IDS_PRC_JOINPLR" : "IDS_PRC_RECREATE"),pInfo->GetName());

	// Too many players
	if (1) // replay needs to check, too!
		if (GetCount()+1>Game.Parameters.MaxPlayers)
		{
			LogF(LoadResStr("IDS_PRC_TOOMANYPLRS"),Game.Parameters.MaxPlayers);
			return NULL;
		}

	// Check duplicate file usage
	if (szFilename) if (FileInUse(szFilename))
			{ Log(LoadResStr("IDS_PRC_PLRFILEINUSE")); return NULL; }

	// Create
	C4Player *pPlr = new C4Player;

	// Append to player list
	C4Player *pLast=First;
	while (pLast && pLast->Next) pLast=pLast->Next;
	if (pLast) pLast->Next=pPlr; else First = pPlr;

	// Init
	if (!pPlr->Init(GetFreeNumber(),iAtClient,szAtClientName,szFilename,fScenarioInit,pInfo, numbers))
		{ Remove(pPlr, false, false); Log(LoadResStr("IDS_PRC_JOINFAIL")); return NULL; }

	// Done
	return pPlr;
}