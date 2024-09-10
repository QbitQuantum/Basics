bool SimpleCache::GetFileForIndex(int index, ByteBuffer & data) {

	String filePath;
	BuildPathForFileInCache(index, filePath);

	if (!File::IsFileExist(filePath)) {
		return false;
	}

	AppLog("Reading data from cached file at %S", filePath.GetPointer());

	File cachedFile;
	cachedFile.Construct(filePath, L"r+");
	if (IsFailed(GetLastResult())) {
		AppLog("Error opening destination file in cache");
		return false;
	}

	FileAttributes fAttributes;
	File::GetAttributes(filePath, fAttributes);

	data.Construct(fAttributes.GetFileSize());
	cachedFile.Read(data);
	AppLog("Read cache: %d bytes", data.GetCapacity());
	if (IsFailed(GetLastResult())) {
		AppLog("Error reading from cached file");
		return false;
	}

	return true;

}