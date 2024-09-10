void CEditorGame::OnSaveLevel()
{
	ILevel* pCurrentLevel = m_pGame->GetIGameFramework()->GetILevelSystem()->GetCurrentLevel();

	if (pCurrentLevel)
	{
		ILevelInfo* pLevelInfo = pCurrentLevel->GetLevelInfo();
		string levelPath = PathUtil::GetGameFolder() + "/" + pLevelInfo->GetPath();
		InitEntityArchetypeEnums(m_pGTE, levelPath, PathUtil::GetFile(pLevelInfo->GetName()));
	}
}