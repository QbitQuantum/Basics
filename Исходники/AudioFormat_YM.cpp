AudioFormat_YM::AudioFormat_YM(const Asset& asset):
	ymFile_(0),
	chunkStart_(0),
	chunkEnd_(0)
	{
	if (asset.Open())
		{
		int size=asset.GetSize();
		unsigned char* buffer=static_cast<unsigned char*>(Malloc(size));
		asset.Read(buffer,size);
		asset.Close();

		ymFile_=new CYmMusic();
		ymFile_->loadMemory(buffer,size);
		ymFile_->setLoopMode(true);
		ymFile_->play();
		Free(buffer);
		}
	// Report missing file
	#ifdef _DEBUG
	else
		{
		const char* filename=asset.GetFilename().GetString();
		if (filename)
			{
			char errorMessage[1024];
			SNPrintF(errorMessage,1024,"File not found: %s",filename);
			Assert(false,errorMessage);
			}
		else
			{
			Assert(false,"An asset could not be accessed.");
			}
		}
	#endif
	}