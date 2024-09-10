CzTexture CzPlatformImaging::CreateTexture(void* memory_file, int memory_file_size)
{
	CzFile file;
	if (file.Open(memory_file, memory_file_size))
	{
		// Load the image
		CIwImage* image = new CIwImage();
		image->ReadFile((s3eFile*)file.getFileHandle());

		CIwTexture* texture = new CIwTexture();
		texture->_SetFlags( CIwTexture::NO_CHROMA_KEY_F );
		texture->CopyFromImage(image);

		delete image;

		return (CzTexture)texture;
	}

	return NULL;
}