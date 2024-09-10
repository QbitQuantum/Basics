void wf_Bitmap_Decompress(wfContext* wfc, rdpBitmap* bitmap,
		BYTE* data, int width, int height, int bpp, int length, BOOL compressed, int codec_id)
{
	UINT16 size;

	size = width * height * (bpp / 8);

	if (!bitmap->data)
		bitmap->data = (BYTE*) _aligned_malloc(size, 16);
	else
		bitmap->data = (BYTE*) _aligned_realloc(bitmap->data, size, 16);

	if (compressed)
	{
		BOOL status;

		status = bitmap_decompress(data, bitmap->data, width, height, length, bpp, bpp);

		if (status != TRUE)
		{
			fprintf(stderr, "Bitmap Decompression Failed\n");
		}
	}
	else
	{
		freerdp_image_flip(data, bitmap->data, width, height, bpp);
	}

	bitmap->compressed = FALSE;
	bitmap->length = size;
	bitmap->bpp = bpp;
}