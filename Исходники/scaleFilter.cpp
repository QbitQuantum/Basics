RawImage* ScaleFilter::scaleDown(double scale, RawImage* image)
{
	ImageSize size = image->GetSize();

	int newHeight = (int)round((double)size.Height * scale);
	int newWidth = (int)round((double)size.Width * scale);
	RawImage* returnValue = new RawImage(newWidth, newHeight);
	Rectangle roi = fromSize(size);
	double scaleUp = 1.0 / scale;
	int scaleWindow = max((int)floor(scaleUp), 1);

	if (scaleWindow % 2 == 0) scaleWindow++;

	for (int y = 0; y < newHeight; y++)
		for (int x = 0; x < newWidth; x++)
		{
			int sourceX = (int)round((double)x * scaleUp);
			int sourceY = (int)round((double)y * scaleUp);

			returnValue->SetPixel(x, y, image->GetAverage(sourceX, sourceY, scaleWindow, scaleWindow, roi));
		}

	return returnValue;
}