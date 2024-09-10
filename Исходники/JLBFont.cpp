JLBFont::JLBFont(const char *fontname, int lineheight, bool useVideoRAM)
{
	mRenderer = JRenderer::GetInstance();
	 
	mHeight = 0;
	mScale = 1.0f;
	mRotation = mSpacing = 0.0f;
	mTracking = 0.0f;
	mColor = ARGB(255,255,255,255);

	mTexture = NULL;
	mQuad = NULL;
	mBase = 0;
	
	char filename[256];
	short buffer[1024];
	 
      
	sprintf(filename, "%s.dat", fontname);
	 
	//FILE *file;
	JFileSystem *fileSys = JFileSystem::GetInstance();
	if (!fileSys->OpenFile(filename)) return;

	fileSys->ReadFile((u8 *)buffer, 2048);
	fileSys->CloseFile();
 	
    sprintf(filename, "%s.png", fontname);
	mTexture = mRenderer->LoadTexture(filename, useVideoRAM);

	if (mTexture == NULL) return;
	
	mHeight = (float) lineheight;
	
	mQuad = new JQuad(mTexture, 0.0f, 0.0f, 16.0f, mHeight);

	float a, b, c;

    float y = 0.0f;
	float x;

	// there are 16x16 characters in the texture map.
	float cellHeight = mTexture->mHeight/16.0f;
	
	int n = 0;
	for (int i=0;i<16;i++)
	{
		for (int j=0;j<16;j++)
		{
			x = (float)buffer[n*4];			// x offset
			a = (float)buffer[n*4+1];		// character width
			b = (float)buffer[n*4+2];
			c = (float)buffer[n*4+3];
		  
			mXPos[n] = x;
			mYPos[n] = y;
			mCharWidth[n] = a+b+c;

			n++;
		}

		y += cellHeight;
	}
      
}