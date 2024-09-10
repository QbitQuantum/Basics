Common::OutSaveFile *DefaultSaveFileManager::openForSaving(const Common::String &filename, bool compress) {
	// Assure the savefile name cache is up-to-date.
	const Common::String savePathName = getSavePath();
	assureCached(savePathName);
	if (getError().getCode() != Common::kNoError)
		return nullptr;

	for (Common::StringArray::const_iterator i = _lockedFiles.begin(), end = _lockedFiles.end(); i != end; ++i) {
		if (filename == *i) {
			return nullptr; //file is locked, no saving available
		}
	}

#ifdef USE_LIBCURL
	// Update file's timestamp
	Common::HashMap<Common::String, uint32> timestamps = loadTimestamps();
	timestamps[filename] = INVALID_TIMESTAMP;
	saveTimestamps(timestamps);
#endif

	// Obtain node.
	SaveFileCache::const_iterator file = _saveFileCache.find(filename);
	Common::FSNode fileNode;

	// If the file did not exist before, we add it to the cache.
	if (file == _saveFileCache.end()) {
		const Common::FSNode savePath(savePathName);
		fileNode = savePath.getChild(filename);
	} else {
		fileNode = file->_value;
	}

	// Open the file for saving.
	Common::WriteStream *const sf = fileNode.createWriteStream();
	Common::OutSaveFile *const result = new Common::OutSaveFile(compress ? Common::wrapCompressedWriteStream(sf) : sf);

	// Add file to cache now that it exists.
	_saveFileCache[filename] = Common::FSNode(fileNode.getPath());

	return result;
}