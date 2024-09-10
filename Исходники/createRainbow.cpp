IImage* createRainbowImage( u32 w, u32 h, u8 transparency, f64 gamma)
{
	// create image
	core::dimension2du size(w,h);

	IImage* img = (IImage*)new CImage(ECF_A8R8G8B8, size);

	if (!img) return 0;

	size = img->getDimension();

	// loop pixels per col
	for (u32 y=0; y<size.Height; y++)
	{
		// calculate rainbow-color
		SColor c = createRainbowColor( y, size.Height, gamma);

		// set transparency
		c.setAlpha(transparency);

		// write one row with same color
		for (u32 x=0; x<size.Width; x++)
		{
			// write rainbow-color
			img->setPixel(x,y,c,false);
		}
	}

	return img;
}