static BOOL DLL_CALLCONV
Save(FreeImageIO *io, FIBITMAP *dib, fi_handle handle, int page, int flags, void *data) {
	BOOL bIsFlipped = FALSE;		// FreeImage DIB are upside-down relative to usual graphic conventions
	PKPixelFormatGUID guid_format;	// image format
	PKPixelInfo pixelInfo;			// image specifications
	BOOL bHasAlpha = FALSE;			// is alpha layer present ?

	PKImageEncode *pEncoder = NULL;		// encoder interface
	ERR error_code = 0;					// error code as returned by the interface

	// get the I/O stream wrapper
	WMPStream *pEncodeStream = (WMPStream*)data;

	if(!dib || !handle || !pEncodeStream) {
		return FALSE;
	}

	try {
		// get image dimensions
		unsigned width = FreeImage_GetWidth(dib);
		unsigned height = FreeImage_GetHeight(dib);

		// check JPEG-XR limits
		if((width < MB_WIDTH_PIXEL) || (height < MB_HEIGHT_PIXEL)) {
			FreeImage_OutputMessageProc(s_format_id, "Unsupported image size: width x height = %d x %d", width, height);
			throw (const char*)NULL;
		}

		// get output pixel format
		error_code = GetOutputPixelFormat(dib, &guid_format, &bHasAlpha);
		JXR_CHECK(error_code);
		pixelInfo.pGUIDPixFmt = &guid_format;
		error_code = PixelFormatLookup(&pixelInfo, LOOKUP_FORWARD);
		JXR_CHECK(error_code);

		// create a JXR encoder interface and initialize function pointers with *_WMP functions
		error_code = PKImageEncode_Create_WMP(&pEncoder);
		JXR_CHECK(error_code);

		// attach the stream to the encoder and set all encoder parameters to zero ...
		error_code = pEncoder->Initialize(pEncoder, pEncodeStream, &pEncoder->WMP.wmiSCP, sizeof(CWMIStrCodecParam));
		JXR_CHECK(error_code);

		// ... then configure the encoder
		SetEncoderParameters(&pEncoder->WMP.wmiSCP, &pixelInfo, flags, bHasAlpha);

		// set pixel format
		pEncoder->SetPixelFormat(pEncoder, guid_format);

		// set image size
		pEncoder->SetSize(pEncoder, width, height);
		
		// set resolution (convert from universal units to English units)
		float resX = (float)(unsigned)(0.5F + 0.0254F * FreeImage_GetDotsPerMeterX(dib));
		float resY = (float)(unsigned)(0.5F + 0.0254F * FreeImage_GetDotsPerMeterY(dib));
		pEncoder->SetResolution(pEncoder, resX, resY);

		// set metadata
		WriteMetadata(pEncoder, dib);

		// write metadata & pixels
		// -----------------------

		// dib coordinates are upside-down relative to usual conventions
		bIsFlipped = FreeImage_FlipVertical(dib);

		// get a pointer to dst pixel data
		BYTE *dib_bits = FreeImage_GetBits(dib);

		// get dst pitch (count of BYTE for stride)
		const unsigned cbStride = FreeImage_GetPitch(dib);

		// write metadata + pixels on output
		error_code = pEncoder->WritePixels(pEncoder, height, dib_bits, cbStride);
		JXR_CHECK(error_code);

		// recover dib coordinates
		FreeImage_FlipVertical(dib);

		// free the encoder
		pEncoder->Release(&pEncoder);
		assert(pEncoder == NULL);
		
		return TRUE;

	} catch (const char *message) {
		if(bIsFlipped) {
			// recover dib coordinates
			FreeImage_FlipVertical(dib);
		}
		if(pEncoder) {
			// free the encoder
			pEncoder->Release(&pEncoder);
			assert(pEncoder == NULL);
		}
		if(NULL != message) {
			FreeImage_OutputMessageProc(s_format_id, message);
		}
	}

	return FALSE;
}