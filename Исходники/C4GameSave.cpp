bool C4GameSave::Save(const char *szFilename)
{
	// close any previous
	Close();
	// create group
	C4Group *pLSaveGroup = new C4Group();
	if (!SaveCreateGroup(szFilename, *pLSaveGroup))
	{
		LogF(LoadResStr("IDS_ERR_SAVE_TARGETGRP"), szFilename ? szFilename : "nullptr!");
		delete pLSaveGroup;
		return false;
	}
	// save to it
	return Save(*pLSaveGroup, true);
}