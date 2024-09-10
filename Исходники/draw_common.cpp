    bool GetResolution(const wchar_t* fileName, int & Width, int &Height, CApplicationFonts	* appFonts)
	{
		CBgraFrame image;
		MetaFile::CMetaFile meta_file(appFonts);

		if ( meta_file.LoadFromFile(fileName))
		{
			double dX = 0, dY = 0, dW = 0, dH = 0;
			meta_file.GetBounds(&dX, &dY, &dW, &dH);
			
			Width  = dW;
			Height = dH;
		}
		else if ( image.OpenFile(fileName, 0 ))
		{
			Width  = image.get_Width();
			Height = image.get_Height();

			return true;
		}


		return false;
	}