// ***************************************************************************
bool				CMovieShooter::addFrame(double time, UDriver	*pDriver)
{
	if(!enabled())
		return false;

	// Get the buffer from driver. static to avoid reallocation
	static	CBitmap		bitmap;
	pDriver->getBuffer(bitmap);
	nlassert(bitmap.getPixelFormat()==CBitmap::RGBA);

	// add the frame.
	if(bitmap.getPixels().size()==0)
		return false;
	return addFrame(time, (CRGBA*)(&bitmap.getPixels()[0]), bitmap.getWidth(), bitmap.getHeight());
}