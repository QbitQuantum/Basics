void MagicTowerLoader::loadGame(const QString& gamePath)
{
	SLGCResourceManager::init();
    loadResource(gamePath+"/res");
    loadPreset(gamePath + "/startup.mtpreset.ini");
}