BOOL LLViewerTextureList::createUploadFile(const std::string& filename,
										 const std::string& out_filename,
										 const U8 codec)
{	
	// Load the image
	LLPointer<LLImageFormatted> image = LLImageFormatted::createFromType(codec);
	if (image.isNull())
	{
		image->setLastError("Couldn't open the image to be uploaded.");
		return FALSE;
	}	
	if (!image->load(filename))
	{
		image->setLastError("Couldn't load the image to be uploaded.");
		return FALSE;
	}
	// Decompress or expand it in a raw image structure
	LLPointer<LLImageRaw> raw_image = new LLImageRaw;
	if (!image->decode(raw_image, 0.0f))
	{
		image->setLastError("Couldn't decode the image to be uploaded.");
		return FALSE;
	}
	// Check the image constraints
	if ((image->getComponents() != 3) && (image->getComponents() != 4))
	{
		image->setLastError("Image files with less than 3 or more than 4 components are not supported.");
		return FALSE;
	}
	// Convert to j2c (JPEG2000) and save the file locally
	LLPointer<LLImageJ2C> compressedImage = convertToUploadFile(raw_image);	
	if (compressedImage.isNull())
	{
		image->setLastError("Couldn't convert the image to jpeg2000.");
		llinfos << "Couldn't convert to j2c, file : " << filename << llendl;
		return FALSE;
	}
	if (!compressedImage->save(out_filename))
	{
		image->setLastError("Couldn't create the jpeg2000 image for upload.");
		llinfos << "Couldn't create output file : " << out_filename << llendl;
		return FALSE;
	}
	// Test to see if the encode and save worked
	LLPointer<LLImageJ2C> integrity_test = new LLImageJ2C;
	if (!integrity_test->loadAndValidate( out_filename ))
	{
		image->setLastError("The created jpeg2000 image is corrupt.");
		llinfos << "Image file : " << out_filename << " is corrupt" << llendl;
		return FALSE;
	}
	return TRUE;
}