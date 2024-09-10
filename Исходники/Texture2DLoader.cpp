	bool Texture2DLoader::loadFromMemory(IResource * outResource, uint64 size, const void* data)
	{
		Texture2D * texPtr = (Texture2D*)outResource;
		assert(texPtr != nullptr);

		CIwImage image;
		s3eFile * f = s3eFileOpenFromMemory((void*)data, (size_t)size);
		image.ReadFile(f);
		s3eFileClose(f);

		return texPtr->uploadToGPU(image);
	}