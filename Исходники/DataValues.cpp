// Get image from an another image
Color GetColorFromImage(UINT x, UINT y, Image * image)
{
	UINT width = image->Width();
	UINT height = image->Height();
	x *= width >> 4;
	y *= height >> 4;
	Image temp = Image();
	for (UINT Y = 0; Y < 16; ++Y)
		for (UINT X = 0; X < 16; ++X)
			temp.SetPixel(X, Y, image->GetPixel(X + x, Y + y));

	return temp.Average();
}