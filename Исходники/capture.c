LRESULT CALLBACK cap_stream_cb(HWND hwnd, VIDEOHDR *pframe)
{
	cap_cx *cx;
	void *temp = NULL;
	int iskeyframe;
	size_t datalen;
	void *pdata;
	size_t outdatalen;
	void *poutdata;
	int width;
	int height;
	size_t rgblen;
	void *prgb;
	int quein;
	char message[256];
	DWORD decodetime;

	if(!(cx = cap_assoc_get(hwnd)))
		return TRUE;

	if(cx->started)
	{
		/*
		 * Get captured frame
		 */
		pdata = pframe->lpData;
		datalen = (size_t)(pframe->dwBytesUsed);
		iskeyframe = pframe->dwFlags & VHDR_KEYFRAME;
	
		width = cx->pfmt->bmiHeader.biWidth;
		height = cx->pfmt->bmiHeader.biHeight;

		//start decoding frame time
		decodetime = GetTickCount();

		/*
		 * Use VCM decompressor
		 */
		if(cx->mode == CAP_USE_IC)
		{
			// alloc buffer for decompressed frame
			outdatalen = cx->poutfmt->bmiHeader.biSizeImage;
			if(!(poutdata = malloc(outdatalen)))
			{
				return TRUE;
			}
		
			// decompress frame
			if(ICDecompress(
				cx->ic,
				iskeyframe ? 0 : ICDECOMPRESS_NOTKEYFRAME,
				&(cx->pfmt->bmiHeader),
				pdata,
				&(cx->poutfmt->bmiHeader),
				poutdata) != ICERR_OK)
			{
				free(poutdata);
				return TRUE;
			}

			// to dealloc
			temp = poutdata;

			// get decompressed frame
			pdata = poutdata;
			datalen = outdatalen;
			width = cx->poutfmt->bmiHeader.biWidth;
			height = cx->poutfmt->bmiHeader.biHeight;
		}

		/*
		 * Use pixel decoder
		 */
		if( (cx->mode == CAP_USE_PIXDEC) ||
			(cx->mode == CAP_USE_IC) )
		{
			// alloc buffer
			rgblen = width*height*3;
			if(!(prgb = malloc(rgblen)))
			{
				free(temp);
				return TRUE;
			}

			// decode frame
			if(!cx->pix_func(prgb, pdata, width, height))
			{
				free(prgb);
				free(temp);
				return TRUE;
			}

			// dealloc encoded frame buffer
			free(temp);
		}

		/*
		 * Use JPEG decompressor
		 */
		if(cx->mode == CAP_USE_JPEG)
		{
			if(!(prgb = jpeg_decompress(pdata, datalen, &width, &height)))
			{
				return TRUE;
			}
		}

		//output statistics
		decodetime = GetTickCount() - decodetime;
		sprintf(message, "Frame decode time = %d ms, input length = %d, output length = %d\n",
			decodetime, pframe->dwBytesUsed, rgblen);
		OutputDebugString(message);

		/*
		 * Put frame in buffer
		 */

		// check buffer have free slot
		if((quein = (cx->que_in + 1) % CAP_QUE) == cx->que_out)
		{
			OutputDebugString("Capture buffer overflow\n");
			free(prgb);
			return TRUE;
		}

		// put frame to free slot
		cx->que[cx->que_in].rgb = prgb;
		cx->que[cx->que_in].width = width;
		cx->que[cx->que_in].height = height;
		cx->que[cx->que_in].length = rgblen;
		cx->que_in = quein;
	}

	return TRUE;
}