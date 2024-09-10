BOOL LLImageJ2COJ::decodeImpl(LLImageJ2C &base, LLImageRaw &raw_image, F32 decode_time, S32 first_channel, S32 max_channel_count)
{
	LLTimer decode_timer;

	/* Extract metadata */
	/* ---------------- */
	U8* c_data = base.getData();
	size_t c_size =  base.getDataSize();
	size_t position = 0;
	
	while (position < 1024 && position < (c_size - 7)) // the comment field should be in the first 1024 bytes.
	{
		if (c_data[position] == 0xff && c_data[position + 1] == 0x64)
		{
			U8 high_byte = c_data[position + 2];
			U8 low_byte = c_data[position + 3];
			S32 c_length = (high_byte * 256) + low_byte; // This size also counts the markers, 00 01 and itself
			if (c_length > 200) // sanity check
			{
				// While comments can be very long, anything longer then 200 is suspect.
				break;
			}
			
			if (position + 2 + c_length > c_size)
			{
				// comment extends past end of data, corruption, or all data not retrived yet.
				break;
			}
			
			// if the comment block does not end at the end of data, check to see if the next
			// block starts with 0xFF
			if (position + 2 + c_length < c_size && c_data[position + 2 + c_length] != 0xff)
			{
				// invalied comment block
				break;
			}
			
			// extract the comment minus the markers, 00 01
			raw_image.mComment.assign((char*)c_data + position + 6, c_length - 4);
			break;
		}
		++position;
	}
	
	opj_dparameters_t parameters;	/* decompression parameters */
	opj_event_mgr_t event_mgr = { };		/* event manager */
	opj_image_t *image = nullptr;

	opj_dinfo_t* dinfo = nullptr;	/* handle to a decompressor */
	opj_cio_t *cio = nullptr;


	/* configure the event callbacks (not required) */
	event_mgr.error_handler = error_callback;
	event_mgr.warning_handler = warning_callback;
	event_mgr.info_handler = info_callback;

	/* set decoding parameters to default values */
	opj_set_default_decoder_parameters(&parameters);

	parameters.cp_reduce = base.getRawDiscardLevel();

	if(parameters.cp_reduce == 0 && *(U16*)(base.getData() + base.getDataSize() - 2) != 0xD9FF)
	{
		bool failed = true;
		for(S32 i = base.getDataSize()-1; i > 42; --i)
		{
			if(base.getData()[i] != 0x00)
			{
				failed = *(U16*)(base.getData()+i-1) != 0xD9FF;
				break;
			}
		}
		if(failed)
		{
			opj_image_destroy(image);
			base.decodeFailed();
			return TRUE;
		}
	}


	/* decode the code-stream */
	/* ---------------------- */

	/* JPEG-2000 codestream */

	/* get a decoder handle */
	dinfo = opj_create_decompress(CODEC_J2K);

	/* catch events using our callbacks and give a local context */
	opj_set_event_mgr((opj_common_ptr)dinfo, &event_mgr, stderr);			

	/* setup the decoder decoding parameters using user parameters */
	opj_setup_decoder(dinfo, &parameters);

	/* open a byte stream */
	cio = opj_cio_open((opj_common_ptr)dinfo, base.getData(), base.getDataSize());

	/* decode the stream and fill the image structure */
	image = opj_decode(dinfo, cio);

	/* close the byte stream */
	opj_cio_close(cio);

	/* free remaining structures */
	if(dinfo)
	{
		opj_destroy_decompress(dinfo);
	}

	// The image decode failed if the return was NULL or the component
	// count was zero.  The latter is just a sanity check before we
	// dereference the array.
	if(!image || !image->numcomps)
	{
		LL_DEBUGS("Texture") << "ERROR -> decodeImpl: failed to decode image!" << LL_ENDL;
		if (image)
		{
			opj_image_destroy(image);
		}
		base.decodeFailed();
		return TRUE; // done
	}

	// sometimes we get bad data out of the cache - check to see if the decode succeeded
	for (S32 i = 0; i < image->numcomps; i++)
	{
		if (image->comps[i].factor != base.getRawDiscardLevel())
		{
			// if we didn't get the discard level we're expecting, fail
			opj_image_destroy(image);
			base.decodeFailed();
			return TRUE;
		}
	}
	
	if(image->numcomps <= first_channel)
	{
		LL_WARNS("Texture") << "trying to decode more channels than are present in image: numcomps: " << image->numcomps << " first_channel: " << first_channel << LL_ENDL;
		if (image)
		{
			opj_image_destroy(image);
		}

		base.decodeFailed();
		return TRUE;
	}

	// Copy image data into our raw image format (instead of the separate channel format

	S32 img_components = image->numcomps;
	S32 channels = img_components - first_channel;
	if( channels > max_channel_count )
		channels = max_channel_count;

	// Component buffers are allocated in an image width by height buffer.
	// The image placed in that buffer is ceil(width/2^factor) by
	// ceil(height/2^factor) and if the factor isn't zero it will be at the
	// top left of the buffer with black filled in the rest of the pixels.
	// It is integer math so the formula is written in ceildivpo2.
	// (Assuming all the components have the same width, height and
	// factor.)
	S32 comp_width = image->comps[0].w;
	S32 f=image->comps[0].factor;
	S32 width = ceildivpow2(image->x1 - image->x0, f);
	S32 height = ceildivpow2(image->y1 - image->y0, f);
	raw_image.resize(width, height, channels);
	U8 *rawp = raw_image.getData();
	if (!rawp)
	{
		opj_image_destroy(image);
		base.setLastError("Memory error");
		base.decodeFailed();
		return true; // done
	}

	// first_channel is what channel to start copying from
	// dest is what channel to copy to.  first_channel comes from the
	// argument, dest always starts writing at channel zero.
	for (S32 comp = first_channel, dest=0; comp < first_channel + channels;
		comp++, dest++)
	{
		if (image->comps[comp].data)
		{
			S32 offset = dest;
			for (S32 y = (height - 1); y >= 0; y--)
			{
				for (S32 x = 0; x < width; x++)
				{
					rawp[offset] = image->comps[comp].data[y*comp_width + x];
					offset += channels;
				}
			}
		}
		else // Some rare OpenJPEG versions have this bug.
		{
			LL_DEBUGS("Texture") << "ERROR -> decodeImpl: failed to decode image! (NULL comp data - OpenJPEG bug)" << LL_ENDL;
			if (image)
			{
				opj_image_destroy(image);
			}
			base.decodeFailed();
			return TRUE; // done
		}
	}

	/* free image data structure */
	opj_image_destroy(image);

	return TRUE; // done
}