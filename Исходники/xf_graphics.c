BOOL xf_Bitmap_Decompress(rdpContext* context, rdpBitmap* bitmap,
		BYTE* data, int width, int height, int bpp, int length,
		BOOL compressed, int codecId)
{
	int status;
	UINT16 size;
	BYTE* pSrcData;
	BYTE* pDstData;
	UINT32 SrcSize;
	UINT32 SrcFormat;
	UINT32 bytesPerPixel;
	xfContext* xfc = (xfContext*) context;

	bytesPerPixel = (bpp + 7) / 8;
	size = width * height * 4;

	bitmap->data = (BYTE*) _aligned_malloc(size, 16);
	if (!bitmap->data)
		return FALSE;

	pSrcData = data;
	SrcSize = (UINT32) length;
	pDstData = bitmap->data;

	if (compressed)
	{
		if (bpp < 32)
		{
			if (!freerdp_client_codecs_prepare(xfc->codecs, FREERDP_CODEC_INTERLEAVED))
				return FALSE;

			status = interleaved_decompress(xfc->codecs->interleaved, pSrcData, SrcSize, bpp,
					&pDstData, xfc->format, -1, 0, 0, width, height, xfc->palette);
		}
		else
		{
			if (!freerdp_client_codecs_prepare(xfc->codecs, FREERDP_CODEC_PLANAR))
				return FALSE;

			status = planar_decompress(xfc->codecs->planar, pSrcData, SrcSize,
					&pDstData, xfc->format, -1, 0, 0, width, height, TRUE);
		}

		if (status < 0)
		{
			WLog_ERR(TAG, "Bitmap Decompression Failed");
			return FALSE;
		}
	}
	else
	{
		SrcFormat = gdi_get_pixel_format(bpp, TRUE);

		status = freerdp_image_copy(pDstData, xfc->format, -1, 0, 0,
				width, height, pSrcData, SrcFormat, -1, 0, 0, xfc->palette);
	}

	bitmap->compressed = FALSE;
	bitmap->length = size;
	bitmap->bpp = (xfc->depth >= 24) ? 32 : xfc->depth;
	return TRUE;
}