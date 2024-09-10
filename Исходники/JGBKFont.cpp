bool JGBKFont::Init(const char* engFileName, const char* chnFileName, int fontsize, bool smallEnglishFont)
{
	mSmallEnglishFont = smallEnglishFont;
	mFontSize = fontsize;

	mCacheImageWidth = 256;
	mCacheImageHeight = 256;

	mBytesPerRow = (mFontSize+7)/8;
	mBytesPerChar = mBytesPerRow*mFontSize;

	mCol = mCacheImageWidth/mFontSize;
	mRow = mCacheImageHeight/mFontSize;
	mCacheSize = mCol*mRow;

	mSprites = new JQuad*[mCacheSize];
	mGBCode = new int[mCacheSize];

#if defined (WIN32) || defined (LINUX)
	mCharBuffer = new DWORD[mFontSize*mFontSize];
#endif

	mTexture = mRenderer->CreateTexture(mCacheImageWidth, mCacheImageHeight, true);

	int index = 0;
	for (int y=0;y<mRow;y++)
	{
		for (int x=0;x<mCol;x++)
		{
			mGBCode[index] = -1;

			mSprites[index] = new JQuad(mTexture, 
                                        static_cast<float>(x*mFontSize),
                                        static_cast<float>(y*mFontSize),
                                        static_cast<float>(mFontSize),
                                        static_cast<float>(mFontSize));
			mSprites[index]->SetHotSpot(static_cast<float>(mFontSize/2), static_cast<float>(mFontSize/2));

			index++;
		}
	}

	int size;

	JFileSystem *fileSys = JFileSystem::GetInstance();
	if (!fileSys->OpenFile(engFileName))
		return false;

	size = fileSys->GetFileSize();
	mEngFont = new BYTE[size];

	fileSys->ReadFile(mEngFont, size);
	fileSys->CloseFile();


	if (!fileSys->OpenFile(chnFileName))
		return false;

	size = fileSys->GetFileSize();

	mChnFont = new BYTE[size];

	fileSys->ReadFile(mChnFont, size);
	fileSys->CloseFile();

	return true;
}