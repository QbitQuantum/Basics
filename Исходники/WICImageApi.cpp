Image::Buffer * WIC::Api::CreateImage(char * data, unsigned dataSize, unsigned w, unsigned h, Image::Format format)
{
	IWICBitmap * bitmap = 0;

	factory->CreateBitmap(w, h, IMAGE_FORMAT_TO_WIC_GUID[format], WICBitmapCacheOnLoad, &bitmap);
	if(!bitmap) return 0;

	WICRect lockRect = { 0, 0, w, h };

	IWICBitmapLock * lock = 0;
	bitmap->Lock(&lockRect, WICBitmapLockWrite, &lock);
	if(!lock)
	{
		bitmap->Release();
		return 0;
	}
	
	unsigned bufferSize = 0;
	WICInProcPointer dataPointer = 0;
	lock->GetDataPointer(&bufferSize, &dataPointer);

	memcpy(dataPointer, data, dataSize);

	lock->Release();
	lock = 0;

	if(format != Image::Format_4x8intRGBA)
	{
		IWICBitmapSource * convertedSource = 0;
		WICConvertBitmapSource(GUID_WICPixelFormat32bppRGBA, bitmap, &convertedSource);
		bitmap->Release();
		bitmap = 0;
		if(!convertedSource) return 0;

		// Create the bitmap from the image frame.
		factory->CreateBitmapFromSource(
			convertedSource,         // Create a bitmap from the image frame
			WICBitmapCacheOnDemand,  // Cache metadata when needed
			&bitmap);                // Pointer to the bitmap
		convertedSource->Release();
		if(!bitmap) return 0;
	}

	bitmap->Lock(&lockRect, WICBitmapLockWrite, &lock);
	if(!lock)
	{
		bitmap->Release();
		return 0;
	}

	return new WIC::Buffer(bitmap, lock, w, h);
}