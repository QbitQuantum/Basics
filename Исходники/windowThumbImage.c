static int getImage(const char *fileName, image *imageData, unsigned maxWidth,
	unsigned maxHeight, int stretch, color *background)
{
	int status = 0;
	image loadImage;
	float scale = 0;
	unsigned thumbWidth = 0;
	unsigned thumbHeight = 0;

	memset(&loadImage, 0, sizeof(image));

	status = imageNew(imageData, maxWidth, maxHeight);
	if (status < 0)
		return (status);

	if (!stretch && background)
	{
		status = imageFill(imageData, background);
		if (status < 0)
			goto out;
	}

	if (fileName)
	{
		status = imageLoad(fileName, 0, 0, &loadImage);
		if (status < 0)
			goto out;

		// Scale the image
		thumbWidth = loadImage.width;
		thumbHeight = loadImage.height;

		// Presumably we need to shrink it?
		if (stretch)
		{
			thumbWidth = maxWidth;
			thumbHeight = maxHeight;
		}
		else
		{
			if (thumbWidth > maxWidth)
			{
				scale = ((float) maxWidth / (float) thumbWidth);
				thumbWidth = (unsigned)((float) thumbWidth * scale);
				thumbHeight = (unsigned)((float) thumbHeight * scale);
			}

			if (thumbHeight > maxHeight)
			{
				scale = ((float) maxHeight / (float) thumbHeight);
				thumbWidth = (unsigned)((float) thumbWidth * scale);
				thumbHeight = (unsigned)((float) thumbHeight * scale);
			}
		}

		if ((thumbWidth != loadImage.width) ||
			(thumbHeight != loadImage.height))
		{
			status = imageResize(&loadImage, thumbWidth, thumbHeight);
			if (status < 0)
				goto out;
		}

		status = imagePaste(&loadImage, imageData,
			((maxWidth - loadImage.width) / 2),
			((maxHeight - loadImage.height) / 2));
		if (status < 0)
			goto out;
	}

	status = 0;

out:
	if (loadImage.data)
		imageFree(&loadImage);

	if ((status < 0) && imageData->data)
		imageFree(imageData);

	return (status);
}