bool FilesPageHandler::listDirectory(Common::String path, Common::String &content, const Common::String &itemTemplate) {
	if (path == "" || path == "/") {
		if (ConfMan.hasKey("rootpath", "cloud"))
			addItem(content, itemTemplate, IT_DIRECTORY, "/root/", _("File system root"));
		addItem(content, itemTemplate, IT_DIRECTORY, "/saves/", _("Saved games"));
		return true;
	}

	if (HandlerUtils::hasForbiddenCombinations(path))
		return false;

	Common::String prefixToRemove = "", prefixToAdd = "";
	if (!transformPath(path, prefixToRemove, prefixToAdd))
		return false;

	Common::FSNode node = Common::FSNode(path);
	if (path == "/")
		node = node.getParent(); // absolute root

	if (!HandlerUtils::permittedPath(node.getPath()))
		return false;

	if (!node.isDirectory())
		return false;

	// list directory
	Common::FSList _nodeContent;
	if (!node.getChildren(_nodeContent, Common::FSNode::kListAll, false)) // do not show hidden files
		_nodeContent.clear();
	else
		Common::sort(_nodeContent.begin(), _nodeContent.end());

	// add parent directory link
	{
		Common::String filePath = path;
		if (filePath.hasPrefix(prefixToRemove))
			filePath.erase(0, prefixToRemove.size());
		if (filePath == "" || filePath == "/" || filePath == "\\")
			filePath = "/";
		else
			filePath = parentPath(prefixToAdd + filePath);
		addItem(content, itemTemplate, IT_PARENT_DIRECTORY, filePath, _("Parent directory"));
	}

	// fill the content
	for (Common::FSList::iterator i = _nodeContent.begin(); i != _nodeContent.end(); ++i) {
		Common::String name = i->getDisplayName();
		if (i->isDirectory())
			name += "/";

		Common::String filePath = i->getPath();
		if (filePath.hasPrefix(prefixToRemove))
			filePath.erase(0, prefixToRemove.size());
		filePath = prefixToAdd + filePath;

		addItem(content, itemTemplate, detectType(i->isDirectory(), name), filePath, name);
	}

	return true;
}