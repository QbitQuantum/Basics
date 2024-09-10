	/*!
	 * Copies file from source path to destination.
	 *
	 * @param sourceFilename Path to the file.
	 * @param destFilename Destination file path.
	 * @param doOverwrite Do overwrite destination file if it exists.
	 * @returns True if file was successfully moved.
	 */
	GDAPI bool FileUtilitiesWindows::FileCopy(WideString const& sourceFilename, WideString const& destFilename, bool const doOverwrite /*= false*/)
	{
		auto const sourceFilenameSystem = Paths::Platformize(sourceFilename);
		auto const destFilenameSystem = Paths::Platformize(destFilename);
		if (CopyFileW(sourceFilenameSystem.CStr(), destFilenameSystem.CStr(), !doOverwrite) == FALSE)
		{
			Sleep(0);
			return CopyFileW(sourceFilenameSystem.CStr(), destFilenameSystem.CStr(), !doOverwrite) == TRUE;
		}
		return true;
	}