/**
 * Load a GIF image.
 * This will replace the currently-loaded image.
 * Animated GIFs are not yet supported -- only the first frame of an
 * animated GIF will be loaded.
 * @param pGifStream The GIF data buffer (may not be NULL).
 * @param pStreamLen The length of the buffer.
 * @return @c true if the load succeeded, @c false otherwise (current
 *         image will still be cleared).
 */
bool GifDecoder::Decode(const unsigned char *pGifStream, int pStreamLen)
{
	// Delete current image.
	Clean();

	bool retv = false;
	HGLOBAL buf = GlobalAlloc(GPTR, pStreamLen);
	memcpy((void*)buf, pGifStream, pStreamLen);

	IStream *stream = NULL;
	IPicture *pic = NULL;

	// We currently don't support animated GIFs, so set big delay for
	// the first frame.
	mDelay[0] = 3600000;

	// Use OleLoadPicture() to convert the GIF stream to an HBITMAP.
	if (SUCCEEDED(CreateStreamOnHGlobal(buf, false, &stream))) {
		if (SUCCEEDED(OleLoadPicture(stream, 0, false, IID_IPicture, (void**)&pic))) {
			HBITMAP hb = NULL;
			pic->get_Handle((OLE_HANDLE*)&hb);
			mBitmap[0] = (HBITMAP)CopyImage(hb, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG);
			retv = true;
		}
	}

	if (pic != NULL) pic->Release();
	if (stream != NULL) stream->Release();
	GlobalFree(buf);

	return retv;
}