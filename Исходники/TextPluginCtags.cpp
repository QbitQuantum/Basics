void appl::TextPluginCtags::jumpTo(const std::string& _name) {
	if (m_ctagFile == nullptr) {
		APPL_WARNING("No ctags file open");
		return;
	}
	tagEntry entry;
	APPL_INFO("try to find the tag : " << _name);
	if (tagsFind (m_ctagFile, &entry, _name.c_str(), 0) != TagSuccess) {
		APPL_INFO("no tag find ...");
		return;
	}
	tagEntry entrySave = entry;
	int32_t numberOfTags = 0;
	
	// For all tags : Save in an internal Structure :
	std::string tmpFile(m_tagFolderBase + "/" + entry.file);
	etk::FSNode myfile(tmpFile);
	int32_t lineID = entry.address.lineNumber;
	printTag(&entry);
	
	if (tagsFindNext (m_ctagFile, &entry) == TagSuccess) {
		APPL_INFO("Multiple file destination ...");
		ememory::SharedPtr<appl::TagFileSelection> tmpWidget = appl::TagFileSelection::create();
		if (tmpWidget == nullptr) {
			APPL_ERROR("Can not allocate widget  == > display might be in error");
		} else {
			tmpWidget->addCtagsNewItem(myfile.getFileSystemName(), lineID);
			do {
				tmpFile = m_tagFolderBase + "/" + entry.file;
				myfile = tmpFile;
				lineID = entry.address.lineNumber;
				printTag(&entry);
				tmpWidget->addCtagsNewItem(myfile.getFileSystemName(), lineID);
			} while (tagsFindNext (m_ctagFile, &entry) == TagSuccess);
			ewol::getContext().getWindows()->popUpWidgetPush(tmpWidget);
			tmpWidget->signalSelect.connect(sharedFromThis(), &appl::TextPluginCtags::onCallbackOpenCtagsSelectReturn);
		}
	} else {
		jumpFile(myfile.getName(), lineID - 1);
	}
}