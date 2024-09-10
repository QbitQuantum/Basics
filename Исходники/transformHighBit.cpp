ptr<image> transformHighBit::allocateOutputImage(ptr<image> pInputImage, imbxUint32 width, imbxUint32 height)
{
	ptr<image> newImage(new image);
	newImage->create(width, height, pInputImage->getDepth(), pInputImage->getColorSpace(), pInputImage->getHighBit());
	return newImage;
}