void ResourceManager::addResources(const Common::FileList &files, ChangeID &change, uint32 priority) {
	for (Common::FileList::const_iterator file = files.begin(); file != files.end(); ++file) {
		Resource res;
		res.priority = priority;
		res.source   = kSourceFile;
		res.path     = *file;
		res.type     = getFileType(*file);

		addResource(res, Common::FilePath::getStem(*file), change);
	}
}