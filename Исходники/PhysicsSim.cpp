void RenderTarget::getImageData(floatv &data)
{
	IImage* img = driver->createImage(target, position2d<s32>(0,0), target->getSize());

	uint y = img->getDimension().Height;
	uint x = img->getDimension().Width;

	for(uint i = 0; i < y; i++)
	{
		for(uint j = 0; j < x; j++)
		{
			SColor color = img->getPixel(j,i);
			data.push_back((float)(color.getRed()/255.0));
			data.push_back((float)(color.getGreen()/255.0));
			data.push_back((float)(color.getBlue()/255.0));
		}
	}

	img->drop();
	//delete img;
}