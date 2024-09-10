// Open a local file (for example on an SD card).
// This is protected - only Platform can access it.
bool FileStore::Open(const char* directory, const char* fileName, OpenMode mode, uint32_t preAllocSize)
{
	String<MaxFilenameLength> location;
	MassStorage::CombineName(location.GetRef(), directory, fileName);
	const bool writing = (mode == OpenMode::write || mode == OpenMode::append);
	writeBuffer = nullptr;

	if (writing)
	{
		// Try to create the path of this file if we want to write to it
		String<MaxFilenameLength> filePath;
		filePath.copy(location.c_str());

		size_t i = (isdigit(filePath[0]) && filePath[1] == ':') ? 2 : 0;
		if (filePath[i] == '/')
		{
			++i;
		}

		while (i < filePath.strlen())
		{
			if (filePath[i] == '/')
			{
				filePath[i] = 0;
				if (!reprap.GetPlatform().GetMassStorage()->DirectoryExists(filePath.GetRef()) && !reprap.GetPlatform().GetMassStorage()->MakeDirectory(filePath.c_str()))
				{
					reprap.GetPlatform().MessageF(ErrorMessage, "Failed to create folder %s while trying to open file %s\n", filePath.c_str(), location.c_str());
					return false;
				}
				filePath[i] = '/';
			}
			++i;
		}

		// Also try to allocate a write buffer so we can perform faster writes
		// We only do this if the mode is write, not append, because we don't want to use up a large buffer to append messages to the log file,
		// especially as we need to flush messages to SD card regularly.
		// Currently, append mode is used for the log file and for appending simulated print times to GCodes files (which required read access too).
		if (mode == OpenMode::write)
		{
			writeBuffer = reprap.GetPlatform().GetMassStorage()->AllocateWriteBuffer();
		}
	}

	const FRESULT openReturn = f_open(&file, location.c_str(),
										(mode == OpenMode::write) ?  FA_CREATE_ALWAYS | FA_WRITE
											: (mode == OpenMode::append) ? FA_READ | FA_WRITE | FA_OPEN_ALWAYS
												: FA_OPEN_EXISTING | FA_READ);
	if (openReturn != FR_OK)
	{
		if (writeBuffer != nullptr)
		{
			reprap.GetPlatform().GetMassStorage()->ReleaseWriteBuffer(writeBuffer);
			writeBuffer = nullptr;
		}

		// We no longer report an error if opening a file in read mode fails unless debugging is enabled, because sometimes that is quite normal.
		// It is up to the caller to report an error if necessary.
		if (reprap.Debug(modulePlatform))
		{
			reprap.GetPlatform().MessageF(WarningMessage, "Failed to open %s to %s, error code %d\n", location.c_str(), (writing) ? "write" : "read", (int)openReturn);
		}
		return false;
	}

	crc.Reset();
	usageMode = (writing) ? FileUseMode::readWrite : FileUseMode::readOnly;
	openCount = 1;
	if (mode == OpenMode::write && preAllocSize != 0)
	{
		const FRESULT expandReturn = f_expand(&file, preAllocSize, 1);		// try to pre-allocate contiguous space - it doesn't matter if it fails
		if (reprap.Debug(moduleStorage))
		{
			debugPrintf("Preallocating %" PRIu32 " bytes returned %d\n", preAllocSize, (int)expandReturn);
		}
	}
	return true;
}