/* coverity[+alloc : arg-*6] */
GpStatus WINGDIPAPI
GdipCreateTexture2I (GpImage *image, GpWrapMode wrapmode, INT x, INT y, INT width, INT height, GpTexture **texture)
{
	GpImage *textureImage;
	GpStatus status;

	if (!gdiplusInitialized)
		return GdiplusNotInitialized;

	if (!image || !texture)
		return InvalidParameter;

	if (wrapmode > WrapModeClamp) {
		*texture = NULL;
		return OutOfMemory;
	}

	switch (image->type) {
	case ImageTypeBitmap: {
		INT bmpWidth = image->active_bitmap->width;
		INT bmpHeight = image->active_bitmap->height;
		if ((x < 0) || (y < 0) || (width <= 0) || (height <= 0) || (bmpWidth < (x + width)) || (bmpHeight < (y + height))) {
			*texture = NULL;
			return OutOfMemory;
		}

		status = GdipCloneBitmapAreaI (x, y, width, height, image->active_bitmap->pixel_format, image, &textureImage);
		if (status != Ok)
			return status;
		break;
	}
	case ImageTypeMetafile:
		status = gdip_get_bitmap_from_metafile ((GpMetafile *) image, width, height, &textureImage);
		if (status != Ok)
			return status;
		break;
	default:
		return GenericError;
	}
	
	return gdip_texture_create_from_cloned_image (textureImage, wrapmode, texture);
}