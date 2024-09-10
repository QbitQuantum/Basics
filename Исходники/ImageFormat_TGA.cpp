bool ImageFormat_TGA::TestAsset(const Asset& asset)
	{
	// Check if the footer says that this is a TGA file
	if (asset.Open())
		{
		asset.Seek(-18,Asset::SEEK_FROM_END);
		char buffer[16];
		asset.Read(buffer,16);
		asset.Close();
		if (StrNCmp(buffer,"TRUEVISION-XFILE",16)==0)
			{
			return true;
			}
		}

	// If the footer doesn't match, this might still be a tga file (version < 2)
	// so try and load it as a tga and see if it works...
	int size=asset.GetSize();
	char* buffer=new char[size];
	asset.Open();
	asset.Read(buffer,size);
    asset.Close();

	tga_image image;
	tga_read_from_Buffer(&image,buffer);

	delete[] buffer;

	// Check to see if the header data makes sense...
	if (image.width<32767 && image.height<32767 && image.image_data && (image.pixel_depth==8 || image.pixel_depth==24 || image.pixel_depth==16 || image.pixel_depth==32))
		{
		// Yeah, sure, this looks like proper data, so give thumbs up and hope for the best
		return true;
		}

	tga_free_buffers(&image);

	// Nope, not likely to be a TGA
	return false;
	}