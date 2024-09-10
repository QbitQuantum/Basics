	//! retrieves the file size of the open file
	void getFileSize()
	{
		fseek(File, 0, SEEK_END);
		Size = ftell(File);
		fseek(File, 0, SEEK_SET);
	}