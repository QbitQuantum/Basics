bool Ps2SaveFileManager::removeSavefile(const Common::String &filename) {
	Common::FSNode savePath(ConfMan.get("savepath")); // TODO: is this fast?
	Common::FSNode file;

	if (!savePath.exists() || !savePath.isDirectory())
		return false;

	if (_getDev(savePath) == MC_DEV) {
	// if (strncmp(savePath.getPath().c_str(), "mc0:", 4) == 0) {
		char path[32], temp[32];
		strcpy(temp, filename.c_str());

		// mcSplit(temp, game, ext);
		char *game = strdup(strtok(temp, "."));
		char *ext = strdup(strtok(NULL, "*"));
		sprintf(path, "mc0:ScummVM/%s", game); // per game path
		mcCheck(path);
		sprintf(path, "mc0:ScummVM/%s/%s.sav", game, ext);
		file = Common::FSNode(path);
		free(game);
		free(ext);
	} else {
		file = savePath.getChild(filename);
	}

	if (!file.exists() || file.isDirectory())
		return false;

	fio.remove(file.getPath().c_str());

	return true;
}