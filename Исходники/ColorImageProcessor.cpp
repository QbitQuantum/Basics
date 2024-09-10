void ColorImageProcessor::done()
{
	if(processedImage)
		delete processedImage;
	destroyWindow("Settings");
}