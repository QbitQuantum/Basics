static FIBITMAP * DLL_CALLCONV
Load(FreeImageIO *io, fi_handle handle, int page, int flags, void *data) {
	WebPMux *mux = NULL;
	WebPMuxFrameInfo webp_frame = { 0 };	// raw image
	WebPData color_profile;	// ICC raw data
	WebPData xmp_metadata;	// XMP raw data
	WebPData exif_metadata;	// EXIF raw data
	FIBITMAP *dib = NULL;
	WebPMuxError error_status;

	if(!handle) {
		return NULL;
	}

	try {
		// get the MUX object
		mux = (WebPMux*)data;
		if(!mux) {
			throw (1);
		}
		
		// gets the feature flags from the mux object
		uint32_t webp_flags = 0;
		error_status = WebPMuxGetFeatures(mux, &webp_flags);
		if(error_status != WEBP_MUX_OK) {
			throw (1);
		}

		// get image data
		error_status = WebPMuxGetFrame(mux, 1, &webp_frame);

		if(error_status == WEBP_MUX_OK) {
			// decode the data (can be limited to the header if flags uses FIF_LOAD_NOPIXELS)
			dib = DecodeImage(&webp_frame.bitstream, flags);
			if(!dib) {
				throw (1);
			}
			
			// get ICC profile
			if(webp_flags & ICCP_FLAG) {
				error_status = WebPMuxGetChunk(mux, "ICCP", &color_profile);
				if(error_status == WEBP_MUX_OK) {
					FreeImage_CreateICCProfile(dib, (void*)color_profile.bytes, (long)color_profile.size);
				}
			}

			// get XMP metadata
			if(webp_flags & XMP_FLAG) {
				error_status = WebPMuxGetChunk(mux, "XMP ", &xmp_metadata);
				if(error_status == WEBP_MUX_OK) {
					// create a tag
					FITAG *tag = FreeImage_CreateTag();
					if(tag) {
						FreeImage_SetTagKey(tag, g_TagLib_XMPFieldName);
						FreeImage_SetTagLength(tag, (DWORD)xmp_metadata.size);
						FreeImage_SetTagCount(tag, (DWORD)xmp_metadata.size);
						FreeImage_SetTagType(tag, FIDT_ASCII);
						FreeImage_SetTagValue(tag, xmp_metadata.bytes);
						
						// store the tag
						FreeImage_SetMetadata(FIMD_XMP, dib, FreeImage_GetTagKey(tag), tag);

						// destroy the tag
						FreeImage_DeleteTag(tag);
					}
				}
			}

			// get Exif metadata
			if(webp_flags & EXIF_FLAG) {
				error_status = WebPMuxGetChunk(mux, "EXIF", &exif_metadata);
				if(error_status == WEBP_MUX_OK) {
					// read the Exif raw data as a blob
					jpeg_read_exif_profile_raw(dib, exif_metadata.bytes, (unsigned)exif_metadata.size);
					// read and decode the Exif data
					jpeg_read_exif_profile(dib, exif_metadata.bytes, (unsigned)exif_metadata.size);
				}
			}
		}

		WebPDataClear(&webp_frame.bitstream);

		return dib;

	} catch(int) {
		WebPDataClear(&webp_frame.bitstream);
		return NULL;
	}
}