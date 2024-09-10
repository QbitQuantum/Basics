Common::String PersistenceService::getSavegameDirectory() {
	Common::FSNode node(FileSystemUtil::getUserdataDirectory());
	Common::FSNode childNode = node.getChild(SAVEGAME_DIRECTORY);

	// Try and return the path using the savegame subfolder. But if doesn't exist, fall back on the data directory
	if (childNode.exists())
		return childNode.getPath();

	return node.getPath();
}