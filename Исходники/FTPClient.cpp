// Upload file
bool FtpClient::upload(const string & source, const string & destination)
{

	// Check connection
	if (mFtpHnd == NULL)
	{

		// Report error and break
		OutputDebugStringA("Not connected to FTP server:\n");
		showError();
		return false;

	}

	// Check if file exists
	if (!boost::filesystem::exists(boost::filesystem::path(source)))
	{

		// Report error and break
		OutputDebugStringA((string() + "\"" + source + "\" does not exist").c_str());
		return false;

	}

	// Split destination to vector
	vector<string> mPath;
	boost::split(mPath, destination, boost::is_any_of("/"));

	// Iterate through directories
	LPCSTR mFilename;
	for (vector<string>::const_iterator mDirectory = mPath.cbegin(); mDirectory != mPath.cend(); ++mDirectory)
	{

		// End of the line
		if (mDirectory == mPath.end() - 1)
		{

			// Convert to character array
			mFilename = (LPCSTR)mDirectory->c_str();

		}
		else
		{

			// Convert to character array
			LPCSTR nDirectory = (LPCSTR)mDirectory->c_str();

			// Open directory
			if (!FtpSetCurrentDirectoryA(mFtpHnd, nDirectory))
			{

				// Create directory
				if (!FtpCreateDirectoryA(mFtpHnd, nDirectory))
				{

					// Report error and break
					OutputDebugStringA("Unable to create directory:\n");
					showError();
					return false;

				}
				else
				{

					// Open new directory
					if (!FtpSetCurrentDirectoryA(mFtpHnd, nDirectory))
					{

						// Report error and break
						OutputDebugStringA("Unable to open new directory:\n");
						showError();
						return false;

					}

				}

			}

		}

	}

	// Check for existing file
	LPWIN32_FIND_DATAA mInfo = LPWIN32_FIND_DATAA();
	HINTERNET mRemoteFileHnd = FtpFindFirstFileA(mFtpHnd, mFilename, mInfo, INTERNET_FLAG_RELOAD, 0);

	// Clean up memory
	LocalFree(mInfo);
	delete mInfo;

	// File exists
	if (mRemoteFileHnd != NULL)
	{
		
		// Warn
		OutputDebugStringA("File already exists. Overwriting.\n");

		// Close remote file
		InternetCloseHandle(mRemoteFileHnd);

		// Delete file
		if (!FtpDeleteFileA(mFtpHnd, mFilename))
		{

			// Report error and break
			OutputDebugStringA("Unable to delete file from server:\n");
			showError();
			mPath.clear();
			return false;

		}

	}

	// Open remote file for upload
	HINTERNET mFileHnd = FtpOpenFileA(mFtpHnd, mFilename, GENERIC_WRITE, FTP_TRANSFER_TYPE_BINARY, 0);
	if (mFileHnd == NULL)
	{

		// Report error and break
		OutputDebugStringA("Unable to open remote file:\n");
		showError();
		return false;

	}

	// Open local file
	mFileIO.open(source.c_str(), ios::in|ios::binary|ios::ate);
	mFileSize = (DWORD)mFileIO.tellg();
	mFileIO.seekg(0, ios::beg);

	// Return flag
	bool mUploadSuccess = false;

	// Check file size
	if (mFileSize > 0)
	{

		// Allocate memory for buffer and read file
		mBuffer = new int_fast8_t[mFileSize];
		mFileIO.read(mBuffer, mFileSize);
		
		// Write buffer to remote file
		mBytesWritten = 0;
		mUploadSuccess = InternetWriteFile(mFileHnd, mBuffer, mFileSize, &mBytesWritten) == TRUE;
		if (!mUploadSuccess)
			showError();

		// Clean up
		delete [] mBuffer;

	}

	// Close file, clean up
	mFileIO.close();
	InternetCloseHandle(mFileHnd);
	mFileHnd = NULL;
	mPath.clear();

	// Write result
	OutputDebugStringA(mUploadSuccess ? "File uploaded.\n" : "Upload did not complete.\n");

	// Return flag
	return mUploadSuccess;

}