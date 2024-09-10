void DataAccumulator::FlushChunk() {
	// Between flush operations the log is retained as valid HTML file!
	const WCHAR* HTML_FOOTER = L"\t\t\t</table>\n\t\t</center>\n\t</body>\n</html>";
	// TODO: Who will close log for previous day???
 	WCHAR footer[512] = {0}; // Yeah! Call it magic number!

	// Build the page footer
	if (mPreviousRowExists) {
		wcscpy(footer, SECTION_END_TAGS);
	}
	wcscat(footer, HTML_FOOTER);

	// Compile full log file name
	CHAR fileName[LOG_FILE_NAME_LENGTH];
	GenerateLogFileName(fileName);
	MakeSureDirectoryPathExists(fileName);

	// TODO: simplify this:
	if (mIsFirstLog) {
		// Write to yesterday's log
		if (mIsLogFileGenerated) { // if not yet generated
			strcpy(mCurrentLogFile, fileName);
		}
	} else {
		// Write to today's log
		strcpy(mCurrentLogFile, fileName);
	}
	mIsLogFileGenerated = TRUE;

	// Create new log file or use existing
	HANDLE logHandle = CreateFileA(mCurrentLogFile, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD writtenBytes;
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		// In case the file exists, seek to where last log entry was written
		// NOTE: Actually we should keep last footer lenght in some field and use it for seeking here.
		//       But since length of footer for second and further flush operations always includes 
		//       length of previous row closing tags (see the if condition above) its OK to use it for
		//       all subsequent seek-in-file operations.
		SetFilePointer(logHandle, wcslen(footer) * (-1 * sizeof(wchar_t)), NULL, FILE_END);
	}
	else { // ERROR_SUCCESS assumed - the file was created
		WORD headerSize;
		LPCWSTR header = GetHtmlFromResource(LOG_HEADER, &headerSize);
		WriteFile(logHandle, header, headerSize, &writtenBytes, NULL);
	}

	// Write log chunk and footer (to make HTML valid)
	WriteFile(logHandle, chunk, mCurrentChunkLength*sizeof(wchar_t), &writtenBytes, NULL);
	WriteFile(logHandle, footer, wcslen(footer)*sizeof(wchar_t), &writtenBytes, NULL);
	CloseHandle(logHandle);

	// Reset chunk
	memset(chunk, 0, BUFFER_SIZE * sizeof(WCHAR));
};