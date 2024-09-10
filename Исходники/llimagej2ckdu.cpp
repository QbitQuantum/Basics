BOOL LLImageJ2CKDU::initDecode(LLImageJ2C &base, LLImageRaw &raw_image, F32 decode_time, ECodeStreamMode mode, S32 first_channel, S32 max_channel_count, int discard_level, int* region)
{
	base.resetLastError();

	// *FIX: kdu calls our callback function if there's an error, and then bombs.
	// To regain control, we throw an exception, and catch it here.
	try
	{
		// Merov : Test!! DO NOT COMMIT!!
		//findDiscardLevelsBoundaries(base);

		base.updateRawDiscardLevel();
		setupCodeStream(base, TRUE, mode);

		mRawImagep = &raw_image;
		mCodeStreamp->change_appearance(false, true, false);

		// Apply loading discard level and cropping if required
		kdu_dims* region_kdu = NULL;
		if (region != NULL)
		{
			region_kdu = new kdu_dims;
			region_kdu->pos.x  = region[0];
			region_kdu->pos.y  = region[1];
			region_kdu->size.x = region[2] - region[0];
			region_kdu->size.y = region[3] - region[1];
		}
		int discard = (discard_level != -1 ? discard_level : base.getRawDiscardLevel());
		//llinfos << "Merov debug : initDecode, discard used = " << discard << ", asked = " << discard_level << llendl;
		// Apply loading restrictions
		mCodeStreamp->apply_input_restrictions( first_channel, max_channel_count, discard, 0, region_kdu);
		
		// Clean-up
		if (region_kdu)
		{
			delete region_kdu;
			region_kdu = NULL;
		}

		// Resize raw_image according to the image to be decoded
		kdu_dims dims; mCodeStreamp->get_dims(0,dims);
		S32 channels = base.getComponents() - first_channel;
		channels = llmin(channels,max_channel_count);
		raw_image.resize(dims.size.x, dims.size.y, channels);

		if (!mTileIndicesp)
		{
			mTileIndicesp = new kdu_dims;
		}
		mCodeStreamp->get_valid_tiles(*mTileIndicesp);
		if (!mTPosp)
		{
			mTPosp = new kdu_coords;
			mTPosp->y = 0;
			mTPosp->x = 0;
		}
	}
	catch (const char* msg)
	{
		base.setLastError(ll_safe_string(msg));
		return FALSE;
	}
	catch (...)
	{
		base.setLastError("Unknown J2C error");
		return FALSE;
	}

	return TRUE;
}