void CELauncherDialog::automaticScanDirectory(const Common::FSNode &node) {
	// First check if we have a recognized game in the current directory
	Common::FSList files;
	node.getChildren(files, Common::FSNode::kListFilesOnly);
	// detect
	GameList candidates(EngineMan.detectGames(files));
	// insert
	if (candidates.size() >= 1) {
		GameDescriptor result = candidates[0];
		result["path"] = node.getPath();
		addGameToConf(result);
	}
	// Then recurse on the subdirectories
	Common::FSList dirs;
	node.getChildren(dirs, Common::FSNode::kListDirectoriesOnly);
	for (Common::FSList::const_iterator currentDir = dirs.begin(); currentDir != dirs.end(); ++currentDir)
		automaticScanDirectory(*currentDir);

}