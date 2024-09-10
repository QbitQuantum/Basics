void Bitmap::getColour( float x, float y, unsigned char &r, unsigned char &g, unsigned char &b ) {
	using std::floor;

	float fX = x - floor(x), fY = y - floor(y);
	float f00 = (1 - fX) * (1 - fY),
		f10 = fX * (1 - fY),
		f01 = (1 - fX) * fY,
		f11 = fX * fY;

	unsigned char *dataPtr = file->data + (((unsigned int)floor(y) * file->w + (unsigned int)floor(x)) * 4);
	r = floor((float)(*(dataPtr)) * f00 + 
		(float)(*(dataPtr + 4)) * f10 +
		(float)(*(dataPtr + file->w * 4)) * f01 +
		(float)(*(dataPtr + file->w * 4 + 4)) * f11);

	dataPtr++;
	g = floor((float)(*(dataPtr)) * f00 + 
		(float)(*(dataPtr + 4)) * f10 +
		(float)(*(dataPtr + file->w * 4)) * f01 +
		(float)(*(dataPtr + file->w * 4 + 4)) * f11);

	dataPtr++;
	b = floor((float)(*(dataPtr)) * f00 + 
		(float)(*(dataPtr + 4)) * f10 +
		(float)(*(dataPtr + file->w * 4)) * f01 +
		(float)(*(dataPtr + file->w * 4 + 4)) * f11);
}