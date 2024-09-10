ZLFileInfo ZLbadaFSManager::fileInfo(const std::string &path) const {
	AppLog("ZLbadaFSManager::fileInfo %s",path.c_str());
	ZLFileInfo info;
	//struct stat fileStat;
    result r = E_SUCCESS;
    FileAttributes attr;
    Tizen::Base::String badaPath(path.c_str());
    r = File::GetAttributes(badaPath, attr);
   //TODO if(IsFailed(r)) goto CATCH;

	//info.Exists = stat(path.c_str(), &fileStat) == 0; stat - не работает
    info.Exists = (r==E_SUCCESS);

	AppLog("ZLbadaFSManager::fileInfo r = %d", r);
	if (info.Exists) {
		info.Size = attr.GetFileSize();//fileStat.st_size;
		//AppLog("ZLbadaFSManager::fileInfo.Size %d",fileStat.st_size);
		AppLog("ZLbadaFSManager::fileInfo.Size %d",info.Size);
		//AppLog("ZLbadaFSManager::fileInfo.st_mode %x",fileStat.st_mode);
		info.IsDirectory = attr.IsDirectory();//S_ISDIR(fileStat.st_mode);
		if (info.IsDirectory) AppLog("ZLbadaFSManager::fileInfo.IsDirectory");
	}
	return info;
}