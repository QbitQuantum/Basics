bool ImageFormat_PNG::TestAsset(const Asset& asset)
	{
	// Check if the header matches PNG files
	if (asset.Open())
		{
		unsigned char pngheader[]={137,80,78,71,13,10,26,10};
		unsigned char buffer[8];
		asset.Read(buffer,8);
		asset.Close();
		if (MemCmp(buffer,pngheader,8)==0)
			{
			return true;
			}
		}

	return false;
	}