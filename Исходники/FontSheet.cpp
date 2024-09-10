int FontSheet::GetCharMaxX(Bitmap& charBitmap)
{
	int width  = charBitmap.GetWidth();
	int height = charBitmap.GetHeight();

	for(int x = width-1; x >= 0; --x)
	{
		for(int y = 0; y < height; ++y)
		{
			Color color;
			charBitmap.GetPixel(x, y, &color);
			if(color.GetAlpha() > 0)
			{
				 return x;
			}
		}
	}

	return width-1;
}