bool ImageFormat_GIF::TestAsset(const Asset& asset)
	{
	if (asset.Open())
		{
		char buffer[3];
		asset.Read(buffer,3);
		asset.Close();
		if (StrNCmp(buffer,"GIF",3)==0)
			{
			return true;
			}
		}

	return false;
	}