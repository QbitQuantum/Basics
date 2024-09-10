static bool determineEntryCountAndWriteHeader(NexasPackage* package, const wchar_t* sourceDir, bool isBfeFormat) {
	writeLog(LOG_VERBOSE, L"Generating package header......");
	package->header = malloc(sizeof(Header));
	memcpy(package->header->typeTag, "PAC", 3);
	package->header->magicByte = 0;
	package->header->variantTag = isBfeFormat ? CONTENT_LZSS : CONTENT_MAYBE_DEFLATE;
	package->header->entryCount = 0;

	writeLog(LOG_VERBOSE, L"Moving into source directory......");
	if (_wchdir(sourceDir) != 0) {
		writeLog(LOG_QUIET, L"ERROR: Unable to read the source directory!");
		return false;
	}

	struct _wfinddata_t foundFile;
	intptr_t handle = _wfindfirst(L"*", &foundFile);
	int status = 0;
	while (status == 0) {
		if ((foundFile.attrib & _A_SUBDIR) == 0)
			++(package->header->entryCount);
		status = _wfindnext(handle, &foundFile);
	}
	_findclose(handle);

	writeLog(LOG_NORMAL, L"Found %u entries in the source directory.",
			package->header->entryCount);

	if (package->header->entryCount == 0) {
		writeLog(LOG_QUIET, L"ERROR: There is nothing to pack!");
		return false;
	}

	/// Write the header.
	if (fwrite(package->header, sizeof(Header), 1, package->file) != 1) {
		writeLog(LOG_QUIET, L"ERROR: Unable to write to the target package!");
		return false;
	}

	writeLog(LOG_VERBOSE, L"Package Header Written.");

	return true;
}