bool CIwGameImage::Init(void* memory_file, int memory_file_size)
{
	CIwGameFile file;
	if (file.Open(memory_file, memory_file_size))
	{
		// Load the image
		CIwImage image;
		image.ReadFile((s3eFile*)file.getFileHandle());

		// if required format is different then convert it
		if (FormatSet && image.GetFormat() != Format)
		{
			CIwImage* new_image = ConvertToFormat(image, Format);
			Image2D = Iw2DCreateImage(*new_image);
			delete new_image;
		}
		else
			Image2D = Iw2DCreateImage(image);

		if (FilterSet)
			setFilter(Filter);

		if (Image2D == NULL || image.GetFormat() == CIwImage::FORMAT_UNDEFINED)
		{
#if defined(_DEBUG)
			CIwGameError::LogError("Error: CIwGameImage::Init() - Could not create image!");
#endif	// _DEBUG
			return false;
		}
		else
		{
			Width = Image2D->GetWidth();
			Height = Image2D->GetHeight();
#if defined(_DEBUG)
			CIwGameError::LogError("Info: CIwGameImage::Init() - Size = ", CIwGameString(memory_file_size).c_str());
			CIwGameError::LogError("Info: CIwGameImage::Init() - Width = ", CIwGameString(Width).c_str());
			CIwGameError::LogError("Info: CIwGameImage::Init() - Height = ", CIwGameString(Height).c_str());
			CIwGameError::LogError("Info: CIwGameImage::Init() - Bit depth = ", CIwGameString(image.GetBitDepth()).c_str());
			CIwGameError::LogError("Info: CIwGameImage::Init() - Format = ", CIwGameString(image.GetFormat()).c_str());
#endif	// _DEBUG
		}
	}

	// Sanity check
	if (Width <= 0 || Height <= 0 || Width > 16384 || Height > 16384)
		return false;

	State = State_Loaded;

	return true;
}