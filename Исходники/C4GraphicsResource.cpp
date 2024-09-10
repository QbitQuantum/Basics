bool C4GraphicsResource::LoadFile(C4FacetID &fct, const char *szName, C4GroupSet &rGfxSet, int32_t iWdt, int32_t iHgt, bool fNoWarnIfNotFound, int iFlags)
{
	char FileName[_MAX_FNAME]; int32_t ID = 0;
	C4Group *pGrp = FindSuitableFile(szName, rGfxSet, FileName, &ID);
	if (!pGrp)
	{
		// FIXME: Use LogFatal here
		if (!fNoWarnIfNotFound)
		{
			LogF(LoadResStr("IDS_PRC_NOGFXFILE"), szName, LoadResStr("IDS_PRC_FILENOTFOUND"));
		}
		return false;
	}
	// check group
	if (fct.idSourceGroup == ID)
		// already up-to-date
		return true;
	// load
	if (!fct.Load(*pGrp, FileName, iWdt, iHgt, false, iFlags))
	{
		LogF(LoadResStr("IDS_PRC_NOGFXFILE"), FileName, LoadResStr("IDS_ERR_NOFILE"));
		return false;
	}
	fct.idSourceGroup = ID;
	Game.SetInitProgress(ProgressStart);
	ProgressStart += ProgressIncrement;
	return true;
}