void PSPSaveFileManager::checkPath(const Common::FSNode &dir) {
	const char *savePath = dir.getPath().c_str();
	clearError();

	PowerMan.beginCriticalSection();
	
	//check if the save directory exists
	SceUID fd = sceIoDopen(savePath);
	if (fd < 0) {
		//No? then let's create it.
		sceIoMkdir(savePath, 0777);
	} else {
		//it exists, so close it again.
		sceIoDclose(fd);
	}
	
	PowerMan.endCriticalSection();
}