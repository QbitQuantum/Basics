// ***************************************************************************
void dividSize (CBitmap &bitmap)
{
	// Must be RGBA
	nlassert (bitmap.getPixelFormat () == CBitmap::RGBA);

	// Copy the bitmap
	CBitmap temp = bitmap;

	// Resize the destination
	const uint width = temp.getWidth ();
	const uint height = temp.getHeight ();
	const uint newWidth = temp.getWidth ()/2;
	const uint newHeight = temp.getHeight ()/2;
	bitmap.resize (newWidth, newHeight, CBitmap::RGBA);

	// Pointers
	uint8 *pixelSrc = &(temp.getPixels ()[0]);
	uint8 *pixelDest = &(bitmap.getPixels ()[0]);

	// Resample
	uint x, y;
	for (y=0; y<newHeight; y++)
	for (x=0; x<newWidth; x++)
	{
		const uint offsetSrc = ((y*2)*width+x*2)*4;
		const uint offsetDest = (y*newWidth+x)*4;
		uint i;
		for (i=0; i<4; i++)
		{
			pixelDest[offsetDest+i] = ((uint)pixelSrc[offsetSrc+i] + (uint)pixelSrc[offsetSrc+4+i] + 
				(uint)pixelSrc[offsetSrc+4*width+i] + (uint)pixelSrc[offsetSrc+4*width+4+i])>>2;
		}
	}
}