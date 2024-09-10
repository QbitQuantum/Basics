void Synchro::FirstSynchro()
{
	GetJSON();
	std::map<int, Folder *> FolderMap = myparse.getFoldermap();
	typedef std::map<int, Folder *>::iterator it_type2;
	for (it_type2 iterator = FolderMap.begin(); iterator != FolderMap.end(); iterator++) {
		Folder *fold = iterator->second;
		std::string str = this->folder + fold->getChosenPath() + "/" + fold->getName();
		char *cstr = new char[str.length() + 1];
		strcpy(cstr, str.c_str());
		if (QDir(cstr).exists() == true)
			return;
		else
			QDir().mkdir(cstr);
		delete[] cstr;
	}

	std::map<int, File *> fileMap = myparse.getFileMap();
	std::string StrignUpload = "uploads/";
	typedef std::map<int, File *>::iterator it_type;
	for (it_type iterator = fileMap.begin(); iterator != fileMap.end(); iterator++) {
		File *test = iterator->second;
		std::string urltodown = this->URL + StrignUpload + test->getPseudoOwner() + "/" + test->getRealPath() + test->getPath();
		while (urltodown.find('\\') != std::string::npos)
			replace(urltodown, "\\", "/");
		char *cstr1 = new char[urltodown.length() + 1];
		strcpy(cstr1, urltodown.c_str());

		std::string str = test->getName() + "." + test->getMimeType();
		char *cstr = new char[str.length() + 1];
		strcpy(cstr, str.c_str());

		str = this->folder + test->getChosenPath() + "/";
		char *pathDisk = new char[str.length() + 1];
		strcpy(pathDisk, str.c_str());

		std::string ty = pathDisk + str;
		QString URI(ty.c_str());
		DownloadFile(cstr1, URI);

		delete[] cstr;
		delete[] cstr1;
	}

	char acsjson[1024];
	strcpy(acsjson, this->folder);
	strcat(acsjson, ".acsilserver");
	QFile txt(acsjson);

	txt.open(QIODevice::ReadWrite | QIODevice::Text);
	txt.write(myparse.getJSON().c_str());
	txt.close();
}