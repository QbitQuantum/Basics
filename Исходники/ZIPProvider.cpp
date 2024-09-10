AbstractFSProvider::status_t ZIPProvider::ZIPHandle::readFile(const FileName & file, std::vector<uint8_t> & data) {
	if (file.getFile().empty()) {
		return FAILURE;
	}

	const size_t size = fileSize(file);
	if (size == 0) {
		return FAILURE;
	}

	zip_file * fileHandle = zip_fopen(handle, file.getPath().c_str(), 0);
	if (fileHandle == nullptr) {
		WARN(zip_strerror(handle));
		return FAILURE;
	}

	data.resize(size);
	const int bytesRead = zip_fread(fileHandle, data.data(), data.size());
	if (bytesRead == -1) {
		WARN(zip_strerror(handle));
		zip_fclose(fileHandle);
		return FAILURE;
	}
	if (static_cast<size_t>(bytesRead) != size) {
		WARN("Sizes differ during read.");
		zip_fclose(fileHandle);
		return FAILURE;
	}

	if (zip_fclose(fileHandle) == -1) {
		WARN(zip_strerror(handle));
		return FAILURE;
	}

	return OK;
}