void Bitmap_RLE8::Load(const Asset& asset)
	{
	if (asset.Open())
		{
		char header[8];
		asset.Read(header,8);

		if (StrNCmp(header,"PIXRLE8B",8)==0)
			{
			int version=0;
			asset.Read(&version);
			if (version==0)
				{
				int celCount=0;
				asset.Read(&celCount);
				if (celCount>=1)
					{
					ReadFromAsset(&asset);
					}
				}
			}

		else if (StrNCmp(header,"PIXIE_RL",8)==0)
			{
			char c;
			asset.Read(&c);
			int version=0;
			asset.Read(&version);
			if (version==0)
				{
				int celCount=0;
				asset.Read(&celCount);
				if (celCount>=1)
					{
					ReadFromAsset(&asset);
					}
				}
			}
		else
			{
			Assert(false,"Invalid RLE header");
			}
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